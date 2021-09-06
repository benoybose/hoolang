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

#ifndef EMITTER_BASE_HH
#define EMITTER_BASE_HH

#include <memory.h>
#include <string>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

namespace hoo
{
    namespace emitter
    {
        class EmitterBase {
            private:
            std::shared_ptr<llvm::LLVMContext> _context;
            std::shared_ptr<llvm::Module> _module;
            std::shared_ptr<llvm::IRBuilder<>> _builder;
            std::string _unit_name;

            public:
            EmitterBase(const std::string& unit_name);
            EmitterBase(const EmitterBase& emitter_base);

            public:
            std::shared_ptr<llvm::LLVMContext> GetContext();
            std::shared_ptr<llvm::Module> GetModule();
            std::shared_ptr<llvm::IRBuilder<>> GetBuilder();
            const std::string& GetUnitName();

            public:
            virtual void Emit() = 0;
        };
    }
}
#endif