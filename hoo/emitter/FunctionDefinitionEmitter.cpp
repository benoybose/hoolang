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

#include <hoo/emitter/FunctionDefinitionEmitter.hh>
#include <hoo/emitter/EmitterUtils.hh>
#include <hoo/emitter/EmitterException.hh>

#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/BasicBlock.h>

#include <exception>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace hoo::ast;
using namespace llvm;

namespace hoo
{
    namespace emitter
    {
        FunctionDefinitionEmitter::FunctionDefinitionEmitter(std::shared_ptr<FunctionDefinition> function_definition,
                                                             const EmitterBase &parent_emitter,
                                                             std::shared_ptr<ClassDefinition> parent_class_definition) : DefinitionEmitterExtended(function_definition, parent_emitter, parent_class_definition),
                                                                                                                         _function(nullptr)
        {
        }

        void FunctionDefinitionEmitter::Emit()
        {
            auto const &function_definition = this->GetDefinition();
            auto const &parent_class = this->GetParentClass();
            if (!function_definition)
            {
                throw std::runtime_error("valid function definition not found.");
            }

            auto const &function_declaration = function_definition->GetDeclaration();
            std::string function_name = function_declaration->GetName();

            if (parent_class)
            {
                auto parent_class_name = parent_class->GetClassName();
                function_name = parent_class_name + "$" + function_name;
            }

            auto return_type = function_declaration->GetReturnType();
            auto &context = *(this->GetContext());

            Type *function_return_type = nullptr;
            if (!return_type)
            {
                function_return_type = Type::getVoidTy(context);
            }
            else
            {
                function_return_type = EmitterUtils::ResolveType(return_type, context);
            }

            auto param_list = function_declaration->GetParamList();
            param_list.reverse();

            std::vector<Type *> params;
            for (auto const &param : param_list)
            {
                auto param_type_spec = param->GetType();
                auto param_type = EmitterUtils::ResolveType(param_type_spec, context);
                params.push_back(param_type);
            }

            FunctionType *function_type = nullptr;
            if (!params.empty())
            {
                function_type = FunctionType::get(function_return_type, params, false);
            }
            else
            {
                function_type = FunctionType::get(function_return_type, false);
            }

            auto &current_module = *(this->GetModule());
            _function = Function::Create(function_type,
                                         Function::ExternalLinkage,
                                         function_name, current_module);

            unsigned int arg_index = 0;
            for (auto const &param : param_list)
            {
                auto arg = this->_function->getArg(arg_index);
                auto const &arg_name = param->GetName();
                arg->setName(arg_name);
                _symbols[arg_name] = arg;
                arg_index += 1;
            }

            auto const &body = function_definition->GetBody();
            Emit(body);
        }

        void FunctionDefinitionEmitter::Emit(const std::shared_ptr<CompoundStatement> &statement)
        {
            BasicBlock *block = nullptr;
            auto &context = *(this->GetContext());
            std::string block_name = "entry";

            if (!_blocks.empty())
            {
                block_name = _function->getName().str();
                block_name += "_";
                block_name += _blocks.size();
            }

            block = BasicBlock::Create(context, block_name, _function);
            _blocks.push(block);
            auto &builder = *(this->GetBuilder());
            builder.SetInsertPoint(block);
            auto const &statements = statement->GetStatements();
            for (auto const &stmt : statements)
            {
                Emit(stmt);
            }
            _blocks.pop();
        }

        void FunctionDefinitionEmitter::Emit(const std::shared_ptr<DeclarationStatement> &statement)
        {
        }

        Value *FunctionDefinitionEmitter::Emit(const std::shared_ptr<Expression> &expression)
        {
            auto expr_type = expression->GetExpressionType();
            switch (expr_type)
            {
                case EXPRESSION_LITERAL:
                break;
                case EXPRESSION_BINARY:
                {
                    auto const& binary_expression = dynamic_pointer_cast<BinaryExpression>(expression);
                    return Emit(binary_expression);
                }
                case EXPRESSION_REFERENCE:
                {
                    auto const& ref_expression = dynamic_pointer_cast<ReferenceExpression>(expression);
                    return Emit(ref_expression);
                }
                break;
                case EXPRESSION_ARRAY:
                break;
                case EXPRESSION_INVOKE:
                break;
            }
            return nullptr;
        }

        Value* FunctionDefinitionEmitter::Emit(const std::shared_ptr<BinaryExpression> &expression)
        {
            auto const &left_expr = expression->GetLeftExpression();
            auto const &right_expr = expression->GetRightExpression();
            auto const &opr = expression->GetOperator();

            auto left_value = Emit(left_expr);
            if (!left_value)
            {
                throw EmitterException(ERR_EMITTER_FAILED_LEFT_EXPRESSION);
            }
            auto right_value = Emit(right_expr);
            if (!right_value)
            {
                throw EmitterException(ERR_EMITTER_FAILED_RIGHT_EXPRESSION);
            }

            auto const operator_type = opr->GetOperatorType();
            auto value = Emit(operator_type, left_value, right_value);
            return value;
        }

        Value* FunctionDefinitionEmitter::Emit(const std::shared_ptr<ReferenceExpression> &expression)
        {
            std::string name = expression->GetName();
            auto iterator = _symbols.find(name);
            if (iterator != _symbols.end())
            {
                auto &symbol = *(iterator);
                return symbol.second;
            }

            return nullptr;
        }

        Value* FunctionDefinitionEmitter::Emit(const OperatorType operator_type,
        Value* left_value,
        Value* right_value)
        {
            switch (operator_type)
            {
                case OPERATOR_ADD: return EmitAdd(left_value, right_value);
                case OPERATOR_SUB: return EmitSub(left_value, right_value);
                default: throw EmitterException(ERR_EMITTER_BINARY_FAILED_EXPRESSION);
            }
        }

        Value* FunctionDefinitionEmitter::EmitSub(Value* left_value, Value* right_value)
        {
            auto builder = this->GetBuilder();
            auto &context = *(this->GetContext());

            auto const left_type = left_value->getType();
            auto const right_type = right_value->getType();            
            if ((left_type->isIntegerTy()) && (right_type->isIntegerTy()))
            {
                auto value = builder->CreateSub(left_value, right_value);
                return value;
            }
            else if ((left_type->isIntegerTy()) && (right_type->isDoubleTy()))
            {
                left_value = builder->CreateSIToFP(left_value, Type::getDoubleTy(context));
                auto value = builder->CreateFSub(left_value, right_value, "");
                return value;
            }
            else if ((left_type->isDoubleTy()) && (right_type->isIntegerTy()))
            {
                right_value = builder->CreateSIToFP(right_value, Type::getDoubleTy(context));
                auto value = builder->CreateFSub(left_value, right_value, "");
                return value;
            }
            else if ((left_type->isDoubleTy()) && (right_type->isDoubleTy()))
            {
                auto value = builder->CreateFSub(left_value, right_value, "");
                return value;
            }

            throw std::runtime_error("subtraction operation not supproted now.");
        }
        
        Value* FunctionDefinitionEmitter::EmitAdd(Value* left_value,
        Value* right_value)
        {
            auto builder = this->GetBuilder();
            auto &context = *(this->GetContext());

            auto const left_type = left_value->getType();
            auto const right_type = right_value->getType();            
            if ((left_type->isIntegerTy()) && (right_type->isIntegerTy()))
            {
                auto value = builder->CreateAdd(left_value, right_value, "");
                return value;                
            }
            else if ((left_type->isIntegerTy()) && (right_type->isDoubleTy()))
            {
                left_value = builder->CreateSIToFP(left_value, Type::getDoubleTy(context));
                auto value = builder->CreateFAdd(left_value, right_value, "");
                return value;
            }
            else if ((left_type->isDoubleTy()) && (right_type->isIntegerTy()))
            {
                right_value = builder->CreateSIToFP(right_value, Type::getDoubleTy(context));
                auto value = builder->CreateFAdd(left_value, right_value, "");
                return value;
            }
            else if ((left_type->isDoubleTy()) && (right_type->isDoubleTy()))
            {
                auto value = builder->CreateFAdd(left_value, right_value, "");
                return value;
            }

            throw std::runtime_error("addidtion operation not supproted now.");
        }

        void FunctionDefinitionEmitter::Emit(const std::shared_ptr<ReturnStatement> &statement)
        {
            auto const &expr = statement->GetExpression();
            auto builder = this->GetBuilder();

            if (expr)
            {
                auto value = Emit(expr);
                if (value)
                {
                    builder->CreateRet(value);
                }
                else
                {
                    throw EmitterException(ERR_EMITTER_EVAL_FAILED_EXPRESSION);
                }
            }
            else
            {
                builder->CreateRetVoid();
            }
        }

        void FunctionDefinitionEmitter::Emit(const std::shared_ptr<Statement> &statement)
        {
            auto const statement_type = statement->GetStatementType();
            switch (statement_type)
            {
            case STMT_COMPOUND:
            {
                auto const &compound_statement = dynamic_pointer_cast<CompoundStatement>(statement);
                Emit(compound_statement);
                break;
            }
            case STMT_DECLARATION:
            {
                auto const &delc_statement = dynamic_pointer_cast<DeclarationStatement>(statement);
                Emit(delc_statement);
                break;
            }
            case STMT_EXPRESSION:
            {
                auto const &expr_statement = dynamic_pointer_cast<ExpressionStatement>(statement);
                Emit(expr_statement);
                break;
            }
            case STMT_RETURN:
            {
                auto const &ret_statement = dynamic_pointer_cast<ReturnStatement>(statement);
                Emit(ret_statement);
                break;
            }
            case STMT_NOOP:
                break;
            default:
                throw EmitterException(ERR_EMITTER_UNSUPPORTED_STATEMENT);
            }
        }
    }
}