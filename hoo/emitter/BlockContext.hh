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

#ifndef BLOCK_CONTEXT_HH
#define BLOCK_CONTEXT_HH

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Function.h>

#include <map>
#include <string>
#include <memory>

using namespace llvm;

namespace hoo
{
    namespace emitter
    {
        class BlockContext
        {
            private:
            std::shared_ptr<std::map<std::string, Value*>> _symbols;
            BasicBlock  *_block;
            BlockContext *_parent;

            public:
            BlockContext(LLVMContext &context,
            Function* parent_function = nullptr,
            const std::string& name = "",
            BlockContext *parent = nullptr);

            public:
            BasicBlock *GetBlock() { return _block; }
            BlockContext* GetParent() { return _parent; }
            void AddSymbol(const std::string& name, Value* symbol);
            Value* Lookup(const std::string& name);
        };
    }
}

#endif //BLOCK_CONTEXT_HH