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

#include <hoo/parser/visitors/TypeSpecificationVisitor.hh>
#include <hoo/ast/AST.hh>

using namespace hoo::ast;
using namespace antlr4;
using namespace antlrcpp;

namespace hoo
{
    namespace parser
    {
        TypeSpecificationVisitor::TypeSpecificationVisitor(ErrorListener *error_listener)
            : _error_listener(error_listener)
        {
        }

        Any TypeSpecificationVisitor::visitBasicDataTypeSpecifier(HooParser::BasicDataTypeSpecifierContext *ctx)
        {
            TypeSpecification *type = nullptr;
            auto basic_data_type = GetBasicDataType(ctx->BasicDataType()->getText());
            if (BASIC_DATA_TYPE_INVALID != basic_data_type)
            {
                type = new BasicDataTypeSpecification(basic_data_type);
            }
            else
            {
                this->_error_listener->Add(ctx, "Invalid basic data type.");
            }

            return Any(type);
        }

        Any TypeSpecificationVisitor::visitNestedTypeSpecifier(HooParser::NestedTypeSpecifierContext *ctx)
        {
            TypeSpecificationType *type = nullptr;
            auto parent = this->visit(ctx->typeSpecifier())
                              .as<TypeSpecification *>();
            if (TYPE_SPEC_REFERENCE == parent->GetType())
            {
                auto name = ctx->Identifier()->getText();
                TypeSpecification *type = new ReferenceDataTypeSpecification(name,
                                                                             (ReferenceDataTypeSpecification *)parent);
            }
            else 
            {
                auto token = ctx->Identifier()->getSymbol();
                this->_error_listener->Add(ctx, "Invalid type specification found.");
            }

            return Any(type);
        }

        Any TypeSpecificationVisitor::visitIdentifierTypeSpecifier(HooParser::IdentifierTypeSpecifierContext *ctx)
        {
            auto name = ctx->Identifier()->getText();
            TypeSpecification *type = new ReferenceDataTypeSpecification(name, nullptr);
            return Any(type);
        }

        Any TypeSpecificationVisitor::visitArrayTypeSpecifier(HooParser::ArrayTypeSpecifierContext *ctx)
        {
            auto parent = this->visit(ctx->typeSpecifier())
                              .as<TypeSpecification *>();
            TypeSpecification *type = new ArrayDataTypeSpecification(parent);
            return Any(type);
        }

    } // namespace parser
} // namespace hoo