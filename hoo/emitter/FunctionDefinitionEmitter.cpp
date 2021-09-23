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
        std::shared_ptr<ClassDefinition> parent_class_definition) :
        DefinitionEmitterExtended(function_definition, parent_emitter, parent_class_definition),
        _function(nullptr)
        {
        }

        void FunctionDefinitionEmitter::Emit()
        {
            auto const &function_definition = this->GetDefinition();
            auto const &parent_class = this->GetParentClass();
            if (!function_definition)
            {
                throw EmitterException(ERR_EMITTER_INVALID_CLASS_DEFINITION);
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

            if (function_return_type->isIntegerTy(8))
            {
                _function->addAttribute(0, Attribute::ZExt);
            }

            unsigned int arg_index = 0;
            for (auto const &param : param_list)
            {
                auto arg = this->_function->getArg(arg_index);
                auto const &arg_name = param->GetName();
                arg->setName(arg_name);
                if (arg->getType()->isIntegerTy(8))
                {
                    arg->addAttr(Attribute::ZExt);
                }
                _symbols[arg_name] = arg;
                arg_index += 1;
            }

            auto const &body = function_definition->GetBody();
            EmitStatement(body);
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
            for (auto const &statement : statements)
            {
                EmitStatement(statement);
            }
            _blocks.pop();
        }

        void FunctionDefinitionEmitter::Emit(const std::shared_ptr<DeclarationStatement> &statement)
        {
            // todo: to be implemented
        }

        void FunctionDefinitionEmitter::EmitExpressionStatement(const std::shared_ptr<ExpressionStatement> &expression_statement)
        {
            // todo: to be implemented 
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
                    return EmitBinaryExpression(binary_expression);
                }
                case EXPRESSION_REFERENCE:
                {
                    auto const& ref_expression = dynamic_pointer_cast<ReferenceExpression>(expression);
                    return EmitReferenceExpression(ref_expression);
                }
                break;
                case EXPRESSION_ARRAY:
                break;
                case EXPRESSION_INVOKE:
                break;
            }
            return nullptr;
        }

        Value* FunctionDefinitionEmitter::EmitBinaryExpression(const std::shared_ptr<BinaryExpression> &expression)
        {
            auto const &left_expr = expression->GetLeftExpression();
            auto const &right_expr = expression->GetRightExpression();
            auto const &opr = expression->GetOperator();

            auto left_value = Emit(left_expr);
            if (!left_value)
            {
                throw EmitterException(ERR_EMITTER_FAILED_LEFT_EXPRESSION,
                ERR_POS(left_expr));
            }

            auto right_value = Emit(right_expr);
            if (!right_value)
            {
                throw EmitterException(ERR_EMITTER_FAILED_RIGHT_EXPRESSION,
                ERR_POS(right_expr));
            }

            auto const operator_type = opr->GetOperatorType();
            auto value = EmitOperation(operator_type,
            left_value, right_value, expression);
            return value;
        }

        Value* FunctionDefinitionEmitter::EmitReferenceExpression(const std::shared_ptr<ReferenceExpression> &expression)
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

        Value* FunctionDefinitionEmitter::EmitOperation(const OperatorType operator_type,
        Value* left_value,
        Value* right_value,
        const std::shared_ptr<BinaryExpression> &expression)
        {
            switch (operator_type)
            {
                case OPERATOR_ADD: return EmitAdd(left_value, right_value);
                case OPERATOR_SUB: return EmitSub(left_value, right_value, expression);
                default: throw EmitterException(ERR_EMITTER_BINARY_FAILED_EXPRESSION,
                ERR_POS(expression));
            }
        }

        Value* FunctionDefinitionEmitter::EmitSub(Value* left_value, Value* right_value,
        const std::shared_ptr<BinaryExpression> &expression)
        {
            auto builder = this->GetBuilder();
            auto &context = *(this->GetContext());

            auto const left_type = left_value->getType();
            auto const right_type = right_value->getType();            
            if ((left_type->isIntegerTy(64)) && (right_type->isIntegerTy(64)))
            {
                auto value = builder->CreateNSWSub(left_value, right_value);
                return value;
            }
            else if ((left_type->isIntegerTy(64)) && (right_type->isDoubleTy()))
            {
                left_value = builder->CreateSIToFP(left_value, Type::getDoubleTy(context));
                auto value = builder->CreateFSub(left_value, right_value, "");
                return value;
            }
            else if ((left_type->isDoubleTy()) && (right_type->isIntegerTy(64)))
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
            else if ((left_type->isIntegerTy(8)) && (right_type->isIntegerTy(8)))
            {
                left_value = builder->CreateCast(Instruction::ZExt, left_value, Type::getInt32Ty(context));
                right_value = builder->CreateCast(Instruction::ZExt, right_value, Type::getInt32Ty(context));
                auto value = builder->CreateNSWSub(left_value, right_value);
                return value;
            }
            else if ((left_type->isIntegerTy(8)) && (right_type->isIntegerTy(64)))
            {
                left_value = builder->CreateCast(Instruction::ZExt, left_value, right_type);
                auto value = builder->CreateNSWSub(left_value, right_value);
                return value;
            }
            else if ((left_type->isIntegerTy(64)) && (right_type->isIntegerTy(8)))
            {
                right_value = builder->CreateCast(Instruction::ZExt, right_value, left_type);
                auto value = builder->CreateNSWSub(left_value, right_value);
                return value;
            }

            throw EmitterException(ERR_EMITTER_SUB_OPERATION_UNSUPPORTED, ERR_POS(expression));
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
                auto left_bits = left_type->getIntegerBitWidth();
                auto right_bits = right_type->getIntegerBitWidth();                
                if (left_bits < right_bits)
                {
                    left_value = builder->CreateCast(Instruction::CastOps::ZExt,
                    left_value, right_type);
                }
                else if (left_bits > right_bits)
                {
                    right_value = builder->CreateCast(Instruction::CastOps::ZExt,
                    right_value, left_type);
                }

                auto value = builder->CreateNSWAdd(left_value, right_value);
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

        void FunctionDefinitionEmitter::EmitReturn(const std::shared_ptr<ReturnStatement> &statement)
        {
            auto const &expr = statement->GetExpression();
            auto builder = this->GetBuilder();

            if (expr)
            {
                auto value = Emit(expr);
                if (value)
                {
                    auto return_type = _function->getFunctionType()->getReturnType();
                    if (!return_type)
                    {
                        throw std::runtime_error("function cannot return a value.");
                    }
                    auto value_type = value->getType();
                    if ((return_type->isIntegerTy(8)) && (value_type->isIntegerTy(64)))
                    {
                        throw EmitterException(ERR_EMITTER_EXPLICIT_CAST_REQUIRED, ERR_POS(expr));
                    }
                    else if ((return_type->isIntegerTy(64)) && (value_type->isIntegerTy(8)))
                    {
                        value = builder->CreateCast(Instruction::CastOps::ZExt, value, return_type);
                    }
                    else if ((return_type->isIntegerTy(8)) && (value_type->isIntegerTy(32)))
                    {
                        value = builder->CreateCast(Instruction::Trunc, value, return_type);
                    }
                    builder->CreateRet(value);
                }
                else
                {
                    throw EmitterException(ERR_EMITTER_EVAL_FAILED_EXPRESSION, ERR_POS(expr));
                }
            }
            else
            {
                builder->CreateRetVoid();
            }
        }

        void FunctionDefinitionEmitter::EmitStatement(const std::shared_ptr<Statement> &statement)
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
                EmitExpressionStatement(expr_statement);
                break;
            }
            case STMT_RETURN:
            {
                auto const &ret_statement = dynamic_pointer_cast<ReturnStatement>(statement);
                EmitReturn(ret_statement);
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