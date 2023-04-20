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
// #include "llvm/ADT/StringRef.h"
// #include "llvm/ExecutionEngine/JITSymbol.h"
// #include "llvm/ExecutionEngine/Orc/CompileUtils.h"
// #include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
// #include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
// #include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
// #include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
// #include "llvm/ExecutionEngine/SectionMemoryManager.h"
// #include "llvm/IR/DataLayout.h"
// #include "llvm/IR/LLVMContext.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/TargetSelect.h"
#include <llvm/ExecutionEngine/Orc/CompileUtils.h>
#include <llvm/ExecutionEngine/Orc/ExecutorProcessControl.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>

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
        HooJIT::HooJIT(std::unique_ptr<ExecutionSession> session,
            JITTargetMachineBuilder builder,
            DataLayout layout):
        _session(std::move(session)),
        _mangler(*_session, _layout),
        _object_layer(*_session, []() { return std::unique_ptr<SectionMemoryManager>(); }),
        _compiler_layer(*_session, _object_layer, std::make_unique<ConcurrentIRCompiler>(builder)),
        _layout(std::move(layout)),
        _main_lib(_session->createBareJITDylib("<main>")) {
            _main_lib.addGenerator(
                cantFail(DynamicLibrarySearchGenerator::GetForCurrentProcess(
                    _layout.getGlobalPrefix())));
        }
        // HooJIT::HooJIT(std::unique_ptr<TargetProcessControl> target_process_control,
        //                std::unique_ptr<ExecutionSession> execution_session,
        //                JITTargetMachineBuilder target_machine_builder, DataLayout data_layout)
        //     : _taregt_process_control(std::move(target_process_control)),
        //       _execution_session(std::move(execution_session)),
        //       _data_layout(std::move(data_layout)),
        //       _mangle(*this->_execution_session, this->_data_layout),
        //       _object_layer(*this->_execution_session,
        //                     []()
        //                     { return std::make_unique<SectionMemoryManager>(); }),
        //       _ir_compile_layer(*this->_execution_session, _object_layer,
        //                         std::make_unique<ConcurrentIRCompiler>(std::move(target_machine_builder))),
        //       _main_lib(this->_execution_session->createBareJITDylib("<main>"))
        // {
        //     _main_lib.addGenerator(
        //         cantFail(DynamicLibrarySearchGenerator::GetForCurrentProcess(
        //             _data_layout.getGlobalPrefix())));
        // }

        JITDylib &HooJIT::GetMainLib()
        {
            return this->_main_lib;
        }

        Expected<std::unique_ptr<HooJIT>> HooJIT::Create()
        {
            InitializeNativeTarget();
            InitializeAllAsmPrinters();

            auto process_control = SelfExecutorProcessControl::Create();
            if (!process_control) {
                return process_control.takeError();
            }
            auto session = std::make_unique<ExecutionSession>(std::move(*process_control));
            JITTargetMachineBuilder builder(session->getExecutorProcessControl().getTargetTriple());
            auto layout = builder.getDefaultDataLayoutForTarget();
            if (!layout) {
                return layout.takeError();
            }
            return std::make_unique<HooJIT>(std::move(session), std::move(builder),
                                                     std::move(*layout));
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
            return _session->lookup({&_main_lib}, _mangler(name));
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
            if (!resource_tracker) {
                resource_tracker = _main_lib.getDefaultResourceTracker();
            }
            return _compiler_layer.add(resource_tracker, std::move(thread_safe_module));
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
            if (auto error = _session->endSession())
            {
                _session->reportError(std::move(error));
            }
        }
    }
}