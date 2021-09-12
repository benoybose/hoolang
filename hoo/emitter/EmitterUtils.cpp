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

#include <memory>

#include <hoo/emitter/EmitterUtils.hh>
#include <hoo/ast/BasicTypeSpec.hh>

#include <exception>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

using namespace hoo::ast;

using namespace hoo::ast;
using namespace llvm;

namespace hoo
{
    namespace emitter
    {
        Type* EmitterUtils::ResolveType(std::shared_ptr<TypeSpecification> type_spec, LLVMContext& context)
        {
            auto type_spec_type = type_spec->GetType();
            switch (type_spec_type)
            {
                case TYPE_SPEC_BASIC:
                {
                    auto basic_type_spec = std::dynamic_pointer_cast<BasicTypeSpec>(type_spec);
                    auto  basic_type = ResolveType(basic_type_spec, context);
                    return basic_type;
                }
                case TYPE_SPEC_ARRAY:
                case TYPE_SPEC_REFERENCE:
                throw std::runtime_error("type translation is not implemented");
            }
            return nullptr;
        }

        Type* EmitterUtils::ResolveType(std::shared_ptr<BasicTypeSpec> basic_type_spec, LLVMContext& context)
        {
            auto type = basic_type_spec->GetDataType();
            switch (type)
            {
                case BASIC_DATA_TYPE_BYTE:
                return Type::getInt8Ty(context);

                case BASIC_DATA_TYPE_INT:
                return Type::getInt64Ty(context);

                case BASIC_DATA_TYPE_DOUBLE:
                return Type::getDoubleTy(context);

                case BASIC_DATA_TYPE_BOOL:
                return Type::getInt1Ty(context);

                case BASIC_DATA_TYPE_STRING:
                return Type::getInt8PtrTy(context);

                default: throw std::runtime_error("bsaic type does not implemented");
            }
            return nullptr;
        }

        bool EmitterUtils::IsSameType(Value* v1, Value* v2)
        {
            auto t1 = v1->getType()->getTypeID();
            auto t2 = v2->getType()->getTypeID();
            return t1 == t2;
        }
    }
}