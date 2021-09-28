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

#include <hoo/emitter/EmitterContext.hh>
#include <hoo/emitter/BlockContext.hh>

#include <stack>
#include <algorithm>

namespace hoo
{
    namespace emitter
    {
        EmitterContext::EmitterContext(const std::string &unit_name)
            : _unit_name(unit_name),
              _context(std::make_shared<llvm::LLVMContext>()),
              _module(std::make_shared<llvm::Module>(unit_name, *_context)),
              _builder(std::make_shared<llvm::IRBuilder<>>(*_context)),
              _function(nullptr),
              _block_stack(std::make_shared<std::stack<BlockContext*>>())
        {
        }

        BlockContext* EmitterContext::BeginBlock(const std::string &name)
        {
            auto context = GetContext();
            BlockContext *parent_block = nullptr;
            if (!_block_stack->empty())
            {
                parent_block = _block_stack->top();
            }

            auto block_context = new BlockContext(*context, _function, name, parent_block);
            _block_stack->push(block_context);
            _builder->SetInsertPoint(block_context->GetBlock());
            return block_context;
        }

        BlockContext *EmitterContext::GetCurrentBlockContext()
        {
            if (!_block_stack->empty())
            {
                auto current_context = _block_stack->top();
                return current_context;
            }
            else
            {
                return nullptr;
            }
        }

        void EmitterContext::EndBlock()
        {
            auto top_block = _block_stack->top();
            if (nullptr != top_block)
            {
                _block_stack->pop();
                delete top_block;
            }
        }
    }
}