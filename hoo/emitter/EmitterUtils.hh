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

#ifndef EMITTER_UTILS_HH
#define EMITTER_UTILS_HH

#include <hoo/ast/TypeSpecification.hh>
#include <hoo/ast/BasicDataTypes.hh>
#include <hoo/ast/BasicTypeSpec.hh>

#include <memory>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>

using namespace hoo::ast;
using namespace llvm;

namespace hoo
{
    namespace emitter
    {
        class EmitterUtils
        {
            public:
            static llvm::Type* ResolveType(std::shared_ptr<TypeSpecification> type_spec,
            LLVMContext& context);
            static llvm::Type* ResolveType(std::shared_ptr<BasicTypeSpec> basic_type_spec,
            LLVMContext& context);
            static BasicDataTypeType GetBasicDataType(Value *value);
            static BasicDataTypeType GetBasicDataType(Type *type);
        };
    }
}
#endif