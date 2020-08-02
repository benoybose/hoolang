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

#include "HooBaseVisitor.h"

#include <hoo/ast/AST.hh>
#include <hoo/parser/visitors/FunctionDefinitionVisitor.hh>
#include <hoo/parser/ErrorListener.hh>
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
            Definition *definition = nullptr;
            std::shared_ptr<FunctionDeclaration> func_declaration;
            try
            {
                auto func_decl_ctx = ctx->functionDeclaration();
                auto declaration = this->visit(func_decl_ctx)
                                       .as<Declaration *>();
                if (DECLARATION_FUNCTION == declaration->GetDeclarationType())
                {
                    auto func_decl = (FunctionDeclaration *)declaration;
                    func_declaration = std::shared_ptr<FunctionDeclaration>(func_decl);
                }
            }
            catch (...)
            {
                _error_listener->Add(ctx,
                                     "Invalid function declaration on function definition.");
            }

            std::shared_ptr<Statement> statement;
            try
            {
                StatementVisitor visitor(_error_listener);
                auto stmt_context = ctx->function_body;
                auto stmt = visitor.visit(stmt_context)
                                .as<Statement *>();
                statement = std::shared_ptr<Statement>(stmt);
            }
            catch (...)
            {
                _error_listener->Add(ctx,
                                     "Invalid function body on function definition.");
            }

            if ((func_declaration) && (statement))
            {
                definition = new FunctionDefinition(func_declaration, statement);
            }

            return Any(definition);
        }

        Any FunctionDefinitionVisitor::visitFunctionDeclaration(HooParser::FunctionDeclarationContext *ctx)
        {
            DeclaratorType declarator_type = DECLARATOR_NONE;
            auto declarator = ctx->Declarator();
            if (nullptr != declarator)
            {
                auto declarator_name = declarator->getText();
                declarator_type = VisitorHelper::GetDeclarator(declarator_name);
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
            auto param_list_context = ctx->paramList();
            std::list<std::shared_ptr<VariableDeclaration>> param_list;
            if (nullptr != param_list_context)
            {
                auto var_decl_list = this->visit(param_list_context)
                                         .as<std::list<std::shared_ptr<VariableDeclaration>> *>();
                if (nullptr != var_decl_list)
                {
                    std::copy(var_decl_list->begin(), var_decl_list->end(),
                              std::front_inserter(param_list));
                    delete var_decl_list;
                }
                else
                {
                    _error_listener->Add(param_list_context, "Invalid parameter list.");
                }
            }

            Declaration *declaration = new FunctionDeclaration(declarator_type,
                                                               return_type, name,
                                                               param_list);
            return Any(declaration);
        }

        Any FunctionDefinitionVisitor::visitParamList(HooParser::ParamListContext *ctx)
        {
            auto param_contexts = ctx->variableDeclaration();
            auto param_list = new std::list<std::shared_ptr<VariableDeclaration>>();
            VariableDeclarationVisitor var_decl_visitor(_error_listener);
            for (auto param_context : param_contexts)
            {
                auto declaration = var_decl_visitor.visit(param_context)
                                       .as<Declaration *>();
                if ((nullptr != declaration) &&
                    (DECLARATION_VARIABLE == declaration->GetDeclarationType()))
                {
                    auto variable_declaration = (VariableDeclaration *)declaration;
                    param_list->push_back(std::shared_ptr<VariableDeclaration>(variable_declaration));
                }
                else
                {
                    _error_listener->Add(ctx, "Invalid variabled declaration.");
                }
            }
            return Any(param_list);
        }
    } // namespace parser
} // namespace hoo