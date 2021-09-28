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

#ifndef UNIT_EMITTER_HH
#define UNIT_EMITTER_HH

#include <hoo/ast/Unit.hh>
#include <hoo/ast/UnitItem.hh>
#include <hoo/ast/Definition.hh>
#include <hoo/ast/ClassDefinition.hh>
#include <hoo/ast/FunctionDefinition.hh>
#include <hoo/emitter/EmitterBase.hh>

#include <llvm/IR/LLVMContext.h>

#include <memory>
#include <string>

using namespace hoo::ast;

namespace hoo
{
    namespace emitter
    {
        class UnitEmitter : public EmitterBase
        {
            private:
            std::shared_ptr<Unit> _unit;
            llvm::LLVMContext _context;

            public:
            UnitEmitter(std::shared_ptr<Unit> unit);

            public:
            void Emit();
            std::string GetCode();
            llvm::Module *GetModule() { return _emitter_context.GetModule(); }
            std::string GetUnitName() { return _emitter_context.GetUnitName(); }

            private:
            void Emit(const std::shared_ptr<UnitItem>& unitItem);
        };
    }
}

#endif