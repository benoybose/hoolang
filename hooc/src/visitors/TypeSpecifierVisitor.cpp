/*
 * Copyright 2018 Benoy Bose
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

#include "TypeSpecifierVisitor.hh"
#include "HooTypes.hh"
#include <ast/TypeSpecification.hh>

#include <boost/lexical_cast.hpp>

namespace hooc {
    using namespace ast;
    namespace visitors {

        antlrcpp::Any TypeSpecifierVisitor::visitTypeSepecifier(HooParser::TypeSepecifierContext *ctx) {

            TypeSpecification typeSpecification;
            auto typeSpecifier = ctx->typeSepecifier();
            if(nullptr != typeSpecifier) {
                TypeSpecifierVisitor selfVisitor;
                TypeSpecification leftSpecification = typeSpecifier->accept(&selfVisitor);
                typeSpecification.AddPath(leftSpecification.GetTypePath());
            }

            if(nullptr != ctx->Identifier()) {
                typeSpecification.AddPath(ctx->Identifier()->getText());
            }

            if(nullptr != ctx->Constant()) {
                auto symbol = ctx->Constant()->getSymbol();
                try {
                    auto array_size = boost::lexical_cast<hoo::Integer>(symbol->getText());
                    typeSpecification.SetArraySize(array_size);
                } catch (const boost::bad_lexical_cast& ex) {
                    // todo: Error handling
                }
            }

            if((nullptr == ctx->Identifier()) && (nullptr != typeSpecifier)) {
                typeSpecification.SetAsArray();
            }

            return typeSpecification;
        }
    }
}
