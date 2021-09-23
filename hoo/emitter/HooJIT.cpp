/*
 * Copyright 2021 Benoy Bose
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <hoo/emitter/UnitEmitter.hh>
#include <hoo/emitter/HooJIT.hh>
#include <hoo/parser/ParserDriver.hh>
#include "llvm/ADT/StringRef.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/Orc/TargetProcessControl.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/TargetSelect.h"

#include <exception>
#include <string>
#include <memory>
#include <utility>
#include <iostream>

using namespace llvm;
using namespace llvm::orc;
using namespace hoo::parser;

namespace hoo
{
    namespace emitter
    {
        HooJIT::HooJIT(std::unique_ptr<TargetProcessControl> target_process_control,
                       std::unique_ptr<ExecutionSession> execution_session,
                       JITTargetMachineBuilder target_machine_builder, DataLayout data_layout)
            : _taregt_process_control(std::move(target_process_control)),
              _execution_session(std::move(execution_session)),
              _data_layout(std::move(data_layout)),
              _mangle(*this->_execution_session, this->_data_layout),
              _object_layer(*this->_execution_session,
                            []()
                            { return std::make_unique<SectionMemoryManager>(); }),
              _ir_compile_layer(*this->_execution_session, _object_layer,
                                std::make_unique<ConcurrentIRCompiler>(std::move(target_machine_builder))),
              _main_lib(this->_execution_session->createBareJITDylib("<main>"))
        {
            _main_lib.addGenerator(
                cantFail(DynamicLibrarySearchGenerator::GetForCurrentProcess(
                    _data_layout.getGlobalPrefix())));
        }

        JITDylib &HooJIT::GetMainLib()
        {
            return this->_main_lib;
        }

        Expected<std::unique_ptr<HooJIT>> HooJIT::Create()
        {
            InitializeNativeTarget();
            InitializeAllAsmPrinters();

            auto ssp = std::make_shared<SymbolStringPool>();
            auto tpc = SelfTargetProcessControl::Create(ssp);
            if (!tpc)
            {
                return tpc.takeError();
            }

            auto execution_session = std::make_unique<ExecutionSession>(ssp);
            JITTargetMachineBuilder tmb((*tpc)->getTargetTriple());

            auto data_layout = tmb.getDefaultDataLayoutForTarget();
            if (!data_layout)
            {
                return data_layout.takeError();
            }

            return std::make_unique<HooJIT>(std::move(*tpc),
                                            std::move(execution_session),
                                            std::move(tmb),
                                            std::move(*data_layout));
        }

        void HooJIT::Evaluate(const std::string &source, const std::string &name, bool dump)
        {
            ParserDriver driver(source, name, true);
            const auto unit = driver.Build();
            UnitEmitter emitter(unit);
            emitter.Emit();

            auto ir_module = emitter.GetModule();
            auto unit_name = emitter.GetUnitName();
            auto ir = emitter.GetCode();
            if (dump)
            {
                std::cout << ir;
            }
            this->Add(ir, unit_name);
        }

        Expected<JITEvaluatedSymbol> HooJIT::Lookup(const std::string &name)
        {
            return _execution_session->lookup({&_main_lib}, _mangle(name));
        }

        void HooJIT::Add(const std::string &ir, const std::string &name)
        {
            SMDiagnostic diagnostic;
            MemoryBufferRef memory_buffer(ir, name);
            auto context = std::make_unique<LLVMContext>();
            auto ir_module = llvm::parseIR(memory_buffer, diagnostic, *context);
            if (!ir_module)
            {
                throw std::runtime_error("failed to parse IR code " + name);
            }
            auto error = Add(std::move(ir_module),
            std::move(context));
            if (error)
            {
                throw std::runtime_error("failed to add module " + name);
            }
        }

        Error HooJIT::Add(ThreadSafeModule thread_safe_module, ResourceTrackerSP resource_tracker)
        {
            if (!resource_tracker)
            {
                resource_tracker = _main_lib.getDefaultResourceTracker();
            }
            return _ir_compile_layer.add(resource_tracker, std::move(thread_safe_module));
        }

        Error HooJIT::Add(std::unique_ptr<llvm::Module> module,
        std::unique_ptr<LLVMContext> context,
        ResourceTrackerSP resource_tracker)
        {
            ThreadSafeModule thread_safe_module(std::move(module),
            std::move(context));
            return Add(std::move(thread_safe_module), resource_tracker);
        }

        HooJIT::~HooJIT()
        {
            if (auto error = _execution_session->endSession())
            {
                _execution_session->reportError(std::move(error));
            }
        }
    }
}