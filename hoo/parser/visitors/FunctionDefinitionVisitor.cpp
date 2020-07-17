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

#include <hoo/parser/visitors/FunctionDefinitionVisitor.hh>
#include <hoo/parser/ErrorListener.hh>
#include <hoo/ast/AST.hh>
#include <hoo/parser/visitors/StatementVisitor.hh>
#include <hoo/parser/visitors/VisitorHelper.hh>
#include <hoo/parser/visitors/TypeSpecificationVisitor.hh>
#include <hoo/parser/visitors/VariableDeclarationVisitor.hh>

#include <memory>

using namespace antlr4;
using namespace antlrcpp;
using namespace hoo::ast;

namespace hoo
{
    namespace parser
    {
        FunctionDefinitionVisitor::FunctionDefinitionVisitor(ErrorListener *error_listener)
            : _error_listener(error_listener)
        {
        }

        Any FunctionDefinitionVisitor::visitFunctionDefinition(HooParser::FunctionDefinitionContext *ctx)
        {
            auto declaration_context = ctx->functionDeclaration();
            auto declaration = this->visit(declaration_context).as<FunctionDeclaration *>();
            auto stmt_context = ctx->operativeStatement();

            StatementVisitor visitor(_error_listener);
            auto body = visitor.visit(stmt_context).as<Statement *>();
            auto definition = (Definition *)new FunctionDefinition(declaration, body);
            return Any(definition);
        }

        Any FunctionDefinitionVisitor::visitFunctionDeclaration(HooParser::FunctionDeclarationContext *ctx)
        {
            DeclaratorType declarator_type = DECLARATOR_NONE;
            auto declarator = ctx->Declarator();
            if (nullptr != declarator)
            {
                auto declarator_name = declarator->getText();
                declarator_type = VistorHelper::GetDeclarator(declarator_name);
            }

            std::shared_ptr<TypeSpecification> return_type = nullptr;
            if (nullptr != ctx->returnType)
            {
                TypeSpecificationVisitor type_specification_visitor(_error_listener);
                auto type_spec = type_specification_visitor
                                  .visit(ctx->returnType)
                                  .as<TypeSpecification *>();
                return_type = std::shared_ptr<TypeSpecification>(type_spec);
            }

            std::string name = ctx->name->getText();
            auto parameterList = ctx->paramList();
            std::list<std::shared_ptr<VariableDeclaration>> param_list;
            if (nullptr != parameterList)
            {
                VariableDeclarationVisitor var_decl_visitor(_error_listener);
                param_list = var_decl_visitor.visit(parameterList)
                                 .as<std::list<std::shared_ptr<VariableDeclaration>>>();
            }

            auto declaration = new FunctionDeclaration(declarator_type,
                                                       return_type, name, param_list);
            return Any(declaration);
        }
    } // namespace parser
} // namespace hoo