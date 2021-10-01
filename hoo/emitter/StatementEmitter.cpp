#include <hoo/emitter/StatementEmitter.hh>
#include <hoo/emitter/EmitterBase.hh>
#include <hoo/emitter/EmitterException.hh>
#include <hoo/emitter/ExpressionEmitter.hh>
#include <hoo/emitter/EmitterUtils.hh>
#include <hoo/ast/ExpressionStatement.hh>
#include <hoo/ast/ReturnStatement.hh>

#include <memory>

namespace hoo
{
    namespace emitter
    {
        StatementEmitter::StatementEmitter(const std::shared_ptr<Statement> &statement,
                                           const EmitterContext &emitter_context)
            : EmitterBase(emitter_context)
        {
        }

        void StatementEmitter::Emit(const std::shared_ptr<Statement> &statement)
        {
            auto const statement_type = statement->GetStatementType();
            switch (statement_type)
            {
            case STMT_NOOP:
                break;
            case STMT_COMPOUND:
            {
                auto const &compound_statement = dynamic_pointer_cast<CompoundStatement>(statement);
                EmitCompound(compound_statement);
                break;
            }
            case STMT_DECLARATION:
            {
                auto const &delc_statement = dynamic_pointer_cast<DeclarationStatement>(statement);
                EmitDeclaration(delc_statement);
                break;
            }
            case STMT_EXPRESSION:
            {
                auto const &expr_statement = dynamic_pointer_cast<ExpressionStatement>(statement);
                EmitExpression(expr_statement);
                break;
            }
            case STMT_RETURN:
            {
                auto const &ret_statement = dynamic_pointer_cast<ReturnStatement>(statement);
                EmitReturn(ret_statement);
                break;
            }
            default:
                throw EmitterException(ERR_EMITTER_UNSUPPORTED_STATEMENT);
            }
        }

        void StatementEmitter::EmitCompound(const std::shared_ptr<CompoundStatement> &statement)
        {
            auto const &statements = statement->GetStatements();
            for (auto const &statement : statements)
            {
                Emit(statement);
            }
        }

        void StatementEmitter::EmitDeclaration(const std::shared_ptr<DeclarationStatement> &statement)
        {
            throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);
        }

        void StatementEmitter::EmitExpression(const std::shared_ptr<ExpressionStatement> &expression_statement)
        {
            throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);
        }

        void StatementEmitter::EmitReturn(const std::shared_ptr<ReturnStatement> &statement)
        {
            auto const &expr = statement->GetExpression();
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();

            auto block_context = _emitter_context.GetCurrentBlockContext();
            if (!block_context)
            {
                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
            }

            auto function = _emitter_context.GetFunction();
            if (expr)
            {
                ExpressionEmitter emitter(expr, _emitter_context);
                auto value = emitter.Emit();

                if (value)
                {
                    auto return_type = function->getFunctionType()->getReturnType();
                    if (!return_type)
                    {
                        throw std::runtime_error("function cannot return a value.");
                    }

                    auto value_type = value->getType();
                    auto return_basic_type = EmitterUtils::GetBasicDataType(return_type);
                    auto value_basic_type = EmitterUtils::GetBasicDataType(value_type);

                    if ((return_basic_type == BASIC_DATA_TYPE_INVALID) ||
                        (value_basic_type == BASIC_DATA_TYPE_INVALID))
                    {
                        throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);
                    }
                    else
                    {
                        switch (return_basic_type)
                        {
                        case BASIC_DATA_TYPE_BOOL:
                        {
                            switch (value_basic_type)
                            {
                            case BASIC_DATA_TYPE_BOOL:
                            {
                                builder->CreateRet(value);
                                break;
                            }
                            case BASIC_DATA_TYPE_BYTE:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_CHAR:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_DOUBLE:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_INT:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_INVALID:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_STRING:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            }
                            break;
                        }

                        case BASIC_DATA_TYPE_BYTE:
                        {
                            switch (value_basic_type)
                            {
                            case BASIC_DATA_TYPE_BOOL:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_BYTE:
                            {
                                builder->CreateRet(value);
                                break;
                            }
                            case BASIC_DATA_TYPE_CHAR:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_DOUBLE:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_INT:
                                throw EmitterException(ERR_EMITTER_EXPLICIT_CAST_REQUIRED, ERR_POS(expr));
                            case BASIC_DATA_TYPE_INVALID:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_STRING:
                                throw EmitterException(ERR_EMITTER_EXPLICIT_CONV_REQUIRED, ERR_POS(expr));
                            }
                            break;
                        }

                        case BASIC_DATA_TYPE_CHAR:
                        {
                            switch (value_basic_type)
                            {
                            case BASIC_DATA_TYPE_BOOL:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_BYTE:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_CHAR:
                            {
                                builder->CreateRet(value);
                                break;
                            }
                            case BASIC_DATA_TYPE_DOUBLE:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_INT:
                                throw EmitterException(ERR_EMITTER_EXPLICIT_CAST_REQUIRED, ERR_POS(expr));
                            case BASIC_DATA_TYPE_INVALID:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_STRING:
                                throw EmitterException(ERR_EMITTER_EXPLICIT_CONV_REQUIRED, ERR_POS(expr));
                            }
                            break;
                        }

                        case BASIC_DATA_TYPE_DOUBLE:
                        {
                            switch (value_basic_type)
                            {
                            case BASIC_DATA_TYPE_BOOL:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_BYTE:
                            {
                                value = builder->CreateCast(Instruction::SExt, value, Type::getInt64Ty(*context));
                                value = builder->CreateSIToFP(value, return_type);
                                builder->CreateRet(value);
                                break;
                            }
                            case BASIC_DATA_TYPE_CHAR:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_DOUBLE:
                            {
                                builder->CreateRet(value);
                                break;
                            }
                            case BASIC_DATA_TYPE_INT:
                            {
                                value = builder->CreateSIToFP(value, return_type);
                                builder->CreateRet(value);
                                break;
                            }
                            case BASIC_DATA_TYPE_INVALID:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_STRING:
                                throw EmitterException(ERR_EMITTER_EXPLICIT_CONV_REQUIRED, ERR_POS(expr));
                            }
                            break;
                        }

                        case BASIC_DATA_TYPE_INT:
                        {
                            switch (value_basic_type)
                            {
                            case BASIC_DATA_TYPE_BOOL:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_BYTE:
                            {
                                value = builder->CreateCast(Instruction::SExt, value, return_type);
                                builder->CreateRet(value);
                                break;
                            }
                            case BASIC_DATA_TYPE_CHAR:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_DOUBLE:
                                throw EmitterException(ERR_EMITTER_EXPLICIT_CAST_REQUIRED, ERR_POS(expr));
                            case BASIC_DATA_TYPE_INT:
                            {
                                builder->CreateRet(value);
                                break;
                            }
                            case BASIC_DATA_TYPE_INVALID:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_STRING:
                                throw EmitterException(ERR_EMITTER_EXPLICIT_CONV_REQUIRED, ERR_POS(expr));
                            }
                            break;
                        }

                        case BASIC_DATA_TYPE_INVALID:
                            throw EmitterException(ERR_EMITTER_INVALID_RETURN);

                        case BASIC_DATA_TYPE_STRING:
                        {
                            switch (value_basic_type)
                            {
                            case BASIC_DATA_TYPE_BOOL:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_BYTE:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_CHAR:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_DOUBLE:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_INT:
                                throw EmitterException(ERR_EMITTER_EXPLICIT_CAST_REQUIRED, ERR_POS(expr));
                            case BASIC_DATA_TYPE_INVALID:
                                throw EmitterException(ERR_EMITTER_INVALID_RETURN, ERR_POS(expr));
                            case BASIC_DATA_TYPE_STRING:
                            {
                                builder->CreateRet(value);
                                break;
                            }
                            }
                            break;
                        }
                        }
                    }
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
    }
}