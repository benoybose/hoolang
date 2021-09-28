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

#include <hoo/emitter/BlockContext.hh>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>

using namespace llvm;

namespace hoo
{
    namespace emitter
    {
        BlockContext::BlockContext(LLVMContext &context,
        Function* parent_function,
        const std::string& name,
        BlockContext *parent) :
        _symbols(std::make_shared<std::map<std::string, Value*>>()),
        _block(BasicBlock::Create(context, name, parent_function)),
        _parent(parent)
        {
        }

        void BlockContext::AddSymbol(const std::string& name, Value* symbol)
        {
            _symbols->insert(_symbols->begin(),
            std::pair<std::string,
            Value*>(name, symbol));
        }

        Value *BlockContext::Lookup(const std::string& name)
        {
            auto iterator = _symbols->find(name);
            if (iterator != _symbols->end())
            {
                auto &symbol = *(iterator);
                return symbol.second;
            }
            return nullptr;
        }
    }
}