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

#include <hoo/ast/CastExpression.hh>
#include <hoo/emitter/EmitterBase.hh>
#include <hoo/emitter/EmitterContext.hh>
#include <hoo/ast/BasicDataTypes.hh>
#include <llvm/IR/Value.h>

#include <memory>

using namespace hoo::ast;
using namespace llvm;

namespace hoo
{
    namespace emitter
    {
        class CastEmitter : public EmitterBase
        {
            private:
            std::shared_ptr<CastExpression> _expression;
            std::shared_ptr<Expression> _source_expression;
            Value* _source_value;
            BasicDataTypeType _source_basic_type;

            public:
            CastEmitter(const std::shared_ptr<CastExpression> &cast_expression,
            const EmitterContext& emittter_context);

            public:
            bool    IsBasicType();
            Value   *Emit();
            Value   *EmitCastBasicDataTypes();
            Value   *EmitCastReferenceTypes();
            Value   *CastToByte();
            Value   *CastToInt();
        };
    }
}