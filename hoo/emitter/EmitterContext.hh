/*
 * Copyright 2020 Benoy Bose
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

#ifndef EMITTER_CONTEXT_HH
#define EMITTER_CONTEXT_HH

#include <hoo/emitter/BlockContext.hh>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>

#include <string>
#include <memory>
#include <stack>

namespace hoo
{
    namespace emitter
    {
        class EmitterContext
        {
            private:
            std::shared_ptr<llvm::LLVMContext> _context;
            std::shared_ptr<llvm::Module> _module;
            std::shared_ptr<llvm::IRBuilder<>> _builder;
            std::string _unit_name;
            Function* _function;
            std::shared_ptr<std::stack<BlockContext*>> _block_stack;

            public:
            EmitterContext(const std::string &unit_name);

            public:
            llvm::LLVMContext *GetContext() { return _context.get(); }
            llvm::Module *GetModule() { return _module.get(); }
            llvm::IRBuilder<> *GetBuilder() { return _builder.get(); };
            std::string &GetUnitName() { return _unit_name; }
            BlockContext *BeginBlock(const std::string &name = "");
            void EndBlock();
            BlockContext *GetCurrentBlockContext();

            void SetFunction(Function* function) { _function = function; }
            Function* GetFunction() { return _function; }
        };
    }
}

#endif // EMITTER_CONTEXT_HH