#include <hoo/emitter/StatementEmitter.hh>
#include <hoo/emitter/EmitterBase.hh>
#include <hoo/emitter/EmitterException.hh>
#include <hoo/emitter/ExpressionEmitter.hh>
#include <hoo/ast/ExpressionStatement.hh>
#include <hoo/ast/ReturnStatement.hh>

#include <memory>

namespace hoo
{
    namespace emitter
    {
        StatementEmitter::StatementEmitter(const std::shared_ptr<Statement> &statement,
            const EmitterContext& emitter_context)
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
                    else if ((return_type->isIntegerTy(8)) && (value_type->isDoubleTy()))
                    {
                        throw EmitterException(ERR_EMITTER_EXPLICIT_CAST_REQUIRED, ERR_POS(expr));
                    }
                    else if ((return_type->isIntegerTy(64)) && (value_type->isDoubleTy()))
                    {
                        throw EmitterException(ERR_EMITTER_EXPLICIT_CAST_REQUIRED, ERR_POS(expr));
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
    }
}