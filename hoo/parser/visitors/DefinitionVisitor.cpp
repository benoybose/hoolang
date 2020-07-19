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

#include <hoo/ast/AST.hh>
#include <hoo/parser/visitors/DefinitionVisitor.hh>
#include <hoo/parser/visitors/ClassDefinitionVisitor.hh>
#include <hoo/parser/visitors/FunctionDefinitionVisitor.hh>

using namespace antlr4;
using namespace antlrcpp;
using namespace hoo::ast;

namespace hoo
{
    namespace parser
    {
        DefinitionVisitor::DefinitionVisitor(ErrorListener *error_listener)
            : _error_listener(error_listener)
        {
        }

        Any DefinitionVisitor::visitDefenition(HooParser::DefenitionContext *ctx)
        {
            auto class_definition_ctx = ctx->classDefinition();
            Definition *definition = nullptr;

            if (nullptr != class_definition_ctx)
            {
                try
                {
                    ClassDefinitionVisitor visitor(_error_listener);
                    definition = visitor.visit(class_definition_ctx).as<Definition *>();
                }
                catch (...)
                {
                    _error_listener->Add(class_definition_ctx,
                                         "Invalid definition. Invalid class definition.");
                }
            }
            else
            {
                auto function_definition_context = ctx->functionDefinition();
                if (nullptr != function_definition_context)
                {
                    try
                    {
                        FunctionDefinitionVisitor visitor(_error_listener);
                        definition = visitor.visit(function_definition_context).as<Definition *>();
                    }
                    catch (...)
                    {
                        _error_listener->Add(function_definition_context, "Invalid definition. Invalid class definition.");
                    }
                }
                else
                {
                    _error_listener->Add(ctx, "Invalid definition.");
                }
            }
            return Any(definition);
        }
    } // namespace parser
} // namespace hoo