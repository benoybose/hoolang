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
#include <llvm/IR/LLVMContext.h>
#include <llvm/ExecutionEngine/Orc/Core.h>
#include <llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/ExecutionEngine/Orc/CompileUtils.h>
#include <llvm/ExecutionEngine/Orc/ExecutionUtils.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/IRReader/IRReader.h>

#include <exception>
#include <string>
#include <memory>
#include <utility>

using namespace llvm;
using namespace llvm::orc;
using namespace hoo::parser;

namespace hoo
{
    namespace emitter
    {
        HooJIT::HooJIT(JITTargetMachineBuilder target_machine_builder,
                       DataLayout data_layer) : _object_layer(_exe_session, []()
                                                              { return std::make_unique<SectionMemoryManager>(); }),
                                                _ir_compiler_layer(_exe_session, _object_layer, std::make_unique<ConcurrentIRCompiler>(std::move(target_machine_builder))),
                                                _data_layout(std::move(data_layer)),
                                                _mangler(_exe_session, data_layer),
                                                _context(std::make_unique<LLVMContext>()),
                                                _main_lib(_exe_session.createJITDylib("<main>"))
        {
            auto generator = cantFail(DynamicLibrarySearchGenerator::GetForCurrentProcess(_data_layout.getGlobalPrefix()));
            _main_lib.addGenerator(std::move(generator));
        }

        JITDylib &HooJIT::GetMainLib()
        {
            return this->_main_lib;
        }

        Expected<std::unique_ptr<HooJIT>> HooJIT::Create()
        {
            InitializeNativeTarget();
            InitializeAllAsmPrinters();

            auto target_machine_builder = JITTargetMachineBuilder::detectHost();
            if (!target_machine_builder)
            {
                return target_machine_builder.takeError();
            }

            auto data_layer = target_machine_builder->getDefaultDataLayoutForTarget();
            if (!data_layer)
            {
                return data_layer.takeError();
            }

            return std::make_unique<HooJIT>(std::move(*target_machine_builder),
                                            std::move(*data_layer));
        }

        void HooJIT::Evaluate(const std::string &source, const std::string &name)
        {
            ParserDriver driver(source, name, true);
            const auto unit = driver.Build();
            UnitEmitter emitter(unit);
            emitter.Emit();

            auto ir_module = emitter.GetModule();
            auto unit_name = emitter.GetUnitName();
            auto ir = emitter.GetCode();
            this->Add(ir, unit_name);
        }

        Expected<JITEvaluatedSymbol> HooJIT::Lookup(const std::string &name)
        {
            auto symbol_names = _mangler(name);
            auto symbol = _exe_session.lookup({&_main_lib}, symbol_names);
            if (!symbol)
            {
                return symbol.takeError();
            }
            return symbol;
        }

        void HooJIT::Add(const std::string &ir, const std::string &name)
        {
            SMDiagnostic diagnostic;
            MemoryBufferRef memory_buffer(ir, name);
            auto ir_module = llvm::parseIR(memory_buffer, diagnostic, *_context.getContext());
            auto module_add_error = _ir_compiler_layer.add(_main_lib, ThreadSafeModule(std::move(ir_module), _context));
            if (module_add_error)
            {
                throw std::runtime_error("failed to add module " + name);
            }
        }
    }
}