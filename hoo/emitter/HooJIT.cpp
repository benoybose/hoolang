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
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/IRReader/IRReader.h>
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
        HooJIT::HooJIT() {
            _jit = ExitOnErr(LLJITBuilder().create());
        }

        JITDylib &HooJIT::GetMainLib()
        {
            return this->_jit->getMainJITDylib();
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

        Expected<ExecutorAddr> HooJIT::Lookup(const std::string &name)
        {
            auto symbol_address = this->_jit->lookup(name);
            return symbol_address;
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

            auto error = Add(std::move(ir_module), std::move(context));
            if (error)
            {
                throw std::runtime_error("failed to add module " + name);
            }
        }

        Error HooJIT::Add(ThreadSafeModule thread_safe_module)
        {
            auto error = this->_jit->addIRModule(std::move(thread_safe_module));
            return error;
        }

        Error HooJIT::Add(std::unique_ptr<llvm::Module> module,
        std::unique_ptr<LLVMContext> context)
        {
            ThreadSafeModule thread_safe_module(std::move(module), std::move(context));
            return Add(std::move(thread_safe_module));
        }

        HooJIT::~HooJIT()
        {
        }
    }
}