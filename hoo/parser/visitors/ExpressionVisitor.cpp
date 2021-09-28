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
#include <hoo/ast/CastExpression.hh>
#include <hoo/parser/ErrorListener.hh>
#include <hoo/parser/visitors/ExpressionVisitor.hh>
#include <hoo/parser/InvalidExprType.hh>
#include <hoo/parser/visitors/VisitorHelper.hh>
#include <hoo/parser/visitors/TypeSpecificationVisitor.hh>

#include <regex>
#include <list>
#include <memory>
#include <sstream>

using namespace antlr4;
using namespace antlrcpp;
using namespace hoo::ast;

namespace hoo
{
    namespace parser
    {
        ExpressionVisitor::ExpressionVisitor(ErrorListener *error_listener)
            : _error_listener(error_listener)
        {
        }

        Any ExpressionVisitor::visitLiteralExpression(HooParser::LiteralExpressionContext *ctx)
        {
            Expression *expression = nullptr;
            auto byte_constant_terminal = ctx->ByteLiteral();
            if (nullptr != byte_constant_terminal)
            {
                auto byte_text = byte_constant_terminal->getText();
                auto type = std::shared_ptr<TypeSpecification>(new BasicTypeSpec(BASIC_DATA_TYPE_BYTE));
                Expression *byte_expression = new LiteralExpression(type, byte_text);
                VisitorHelper::AssignPositions(byte_expression, ctx);
                return Any(byte_expression);
            }

            auto integer_constant_terminal = ctx->IntegerLiteral();
            if (nullptr != integer_constant_terminal)
            {
                auto integer_text = integer_constant_terminal->getText();
                auto type = std::shared_ptr<TypeSpecification>(new BasicTypeSpec(BASIC_DATA_TYPE_INT));
                Expression *integer_expression = new LiteralExpression(type, integer_text);
                VisitorHelper::AssignPositions(integer_expression, ctx);
                return Any(integer_expression);
            }

            auto double_constant_literal = ctx->DoubleLiteral();
            if (nullptr != double_constant_literal)
            {
                auto float_text = double_constant_literal->getText();
                auto type = std::shared_ptr<TypeSpecification>(new BasicTypeSpec(BASIC_DATA_TYPE_DOUBLE));
                Expression *double_expression = new LiteralExpression(type, float_text);
                VisitorHelper::AssignPositions(double_expression, ctx);
                return Any(double_expression);
            }

            auto char_constant_terminal = ctx->CharLiteral();
            if (nullptr != char_constant_terminal)
            {
                auto char_text = char_constant_terminal->getText();
                auto type = std::shared_ptr<TypeSpecification>(new BasicTypeSpec(BASIC_DATA_TYPE_CHAR));
                Expression *char_expression = new LiteralExpression(type, char_text);
                VisitorHelper::AssignPositions(char_expression, ctx);
                return Any(char_expression);
            }

            auto bool_constant_terminal = ctx->BooleanLiteral();
            if (nullptr != bool_constant_terminal)
            {
                auto bool_text = bool_constant_terminal->getText();
                auto type = std::shared_ptr<TypeSpecification>(new BasicTypeSpec(BASIC_DATA_TYPE_BOOL));
                Expression *bool_expression = new LiteralExpression(type, bool_text);
                VisitorHelper::AssignPositions(bool_expression, ctx);
                return Any(bool_expression);
            }

            _error_listener->Add(ctx, "Invalid literal expression on constant expression.");
            return Any(expression);
        }

        Any ExpressionVisitor::visitStringExpression(HooParser::StringExpressionContext *ctx)
        {
            auto string_terminal = ctx->StringLiteral();
            auto string_text = string_terminal->getText();
            auto type = std::shared_ptr<TypeSpecification>(new BasicTypeSpec(BASIC_DATA_TYPE_STRING));
            Expression *string_expression = new LiteralExpression(type, string_text);
            VisitorHelper::AssignPositions(string_expression, ctx);
            return Any(string_expression);
        }

        Any ExpressionVisitor::visitIdentifierExpression(HooParser::IdentifierExpressionContext *ctx)
        {
            auto id_terminal = ctx->Identifier();
            auto id_name = id_terminal->getText();
            Expression *id_expression = new ReferenceExpression(id_name);
            VisitorHelper::AssignPositions(id_expression, ctx);
            return Any(id_expression);
        }

        Any ExpressionVisitor::visitSimpleExpression(HooParser::SimpleExpressionContext *ctx)
        {
            Expression *expression = nullptr;
            try
            {
                expression = this->visit(ctx->primaryExpression()).as<Expression *>();
            }
            catch (...)
            {
                _error_listener->Add(ctx, "Error while parsing simple expression.");
            }
            return expression;
        }

        Any ExpressionVisitor::visitArrayAccessExpression(HooParser::ArrayAccessExpressionContext *ctx)
        {
            std::shared_ptr<Expression> container;
            try
            {
                auto container_exp = this->visit(ctx->container).as<Expression *>();
                container = std::shared_ptr<Expression>(container_exp);
            }
            catch (...)
            {
                _error_listener->Add(ctx->container,
                                     "Error while parsing container of array access expression.");
            }

            std::shared_ptr<Expression> access_index;
            try
            {
                auto access_index_exp = this->visit(ctx->accessIndex).as<Expression *>();
                access_index = std::shared_ptr<Expression>(access_index_exp);
            }
            catch (...)
            {
                _error_listener->Add(ctx->accessIndex, "Error while parsing index expression of array access expression.");
            }

            Expression *array_access_expression = nullptr;
            if ((container) && (access_index))
            {
                array_access_expression = (Expression *)new ArrayAccessExpression(container,
                access_index);
                VisitorHelper::AssignPositions(array_access_expression, ctx);
            }
            return Any(array_access_expression);
        }

        Any ExpressionVisitor::visitInvokeExpression(HooParser::InvokeExpressionContext *ctx)
        {
            std::shared_ptr<Expression> receiver_expr;
            try
            {
                auto receiver = this->visit(ctx->receiver)
                                    .as<Expression *>();
                receiver_expr = std::shared_ptr<Expression>(receiver);
            }
            catch (...)
            {
                _error_listener->Add(ctx, "Invalid expression on invocation expression.");
            }

            std::list<std::shared_ptr<Expression>> argument_list;
            if (nullptr != ctx->arguments)
            {
                auto arg_ctxs = ctx->arguments->expression();
                for (auto arg_ctx : arg_ctxs)
                {
                    try
                    {
                        auto expr = this->visit(arg_ctx).as<Expression *>();
                        auto arg = std::shared_ptr<Expression>(expr);
                        argument_list.push_back(arg);
                    }
                    catch (...)
                    {
                        _error_listener->Add(arg_ctx,
                                             "Invalid expression as argument for invocation.");
                    }
                }
            }

            Expression *invoke_expression = nullptr;
            if (receiver_expr)
            {
                invoke_expression = new InvokeExpression(receiver_expr, argument_list);
                VisitorHelper::AssignPositions(invoke_expression, ctx);
            }
            else
            {
                _error_listener->Add(ctx, "Invalid invocation expression.");
            }
            return Any(invoke_expression);
        }

        Any ExpressionVisitor::visitNestedExpression(HooParser::NestedExpressionContext *ctx)
        {
            std::shared_ptr<Expression> parent;
            try
            {
                auto parent_expr = this->visit(ctx->parent).as<Expression *>();
                parent = std::shared_ptr<Expression>(parent_expr);
            }
            catch (...)
            {
                _error_listener->Add(ctx->parent, "Invalid expression on nested reference expression.");
            }

            std::string name = "";
            if (nullptr != ctx->name)
            {
                name = ctx->name->getText();
            }
            else
            {
                _error_listener->Add(ctx, "Invalid name on nested reference expression.");
            }

            Expression *reference_expression = new ReferenceExpression(parent, name);
            VisitorHelper::AssignPositions(reference_expression, ctx);
            return Any(reference_expression);
        }

        Any ExpressionVisitor::visitBinaryBitExpression(HooParser::BinaryBitExpressionContext *ctx)
        {
            Expression *expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
            return Any(expr);
        }

        Any ExpressionVisitor::visitBinaryAddExpression(HooParser::BinaryAddExpressionContext *ctx)
        {
            Expression *expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
            return Any(expr);
        }

        Any ExpressionVisitor::visitBinaryMultiplicateExpression(
            HooParser::BinaryMultiplicateExpressionContext *ctx)
        {
            Expression *expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
            return Any(expr);
        }

        Any ExpressionVisitor::visitBinaryCompareExpression(
            HooParser::BinaryCompareExpressionContext *ctx)
        {
            auto expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
            return Any((Expression *)expr);
        }

        Any ExpressionVisitor::visitBinaryLogicExpression(HooParser::BinaryLogicExpressionContext *ctx)
        {
            Expression *expr = CreateBinaryExpression(ctx->lvalue,
                                                      ctx->opr, ctx->rvalue, ctx);
            return Any((Expression *)expr);
        }

        Any ExpressionVisitor::visitBinaryAssignmentExpression(
            HooParser::BinaryAssignmentExpressionContext *ctx)
        {
            Expression *expr = CreateBinaryExpression(ctx->lvalue,
            ctx->opr, ctx->rvalue, ctx);
            return Any((Expression *)expr);
        }

        Any ExpressionVisitor::visitGroupedExpression(HooParser::GroupedExpressionContext *ctx)
        {
            auto expression = this->visit(ctx->expression()).as<Expression *>();
            VisitorHelper::AssignPositions(expression, ctx);
            return Any(expression);
        }

        Any ExpressionVisitor::visitCastExpression(HooParser::CastExpressionContext *ctx)
        {
            TypeSpecificationVisitor type_spec_visitor(_error_listener);
            auto type_spec_ctx = ctx->typeSpecifier();
            auto type_spec = type_spec_visitor.visit(type_spec_ctx)
            .as<TypeSpecification*>();
            auto expr_ctx = ctx->expression();
            auto expr = this->visit(expr_ctx)
            .as<Expression*>();
            Expression* expression = (Expression*) new CastExpression(std::shared_ptr<TypeSpecification>(type_spec),
            std::shared_ptr<Expression>(expr));
            return Any(expression);
        }

        Expression *ExpressionVisitor::CreateBinaryExpression(HooParser::ExpressionContext *lvalue,
                                                              antlr4::Token *opr,
                                                              HooParser::ExpressionContext *rvalue,
                                                              ParserRuleContext *context)
        {

            std::shared_ptr<Expression> left_expression;
            try
            {
                auto left = this->visit(lvalue).as<Expression *>();
                left_expression = std::shared_ptr<Expression>(left);
            }
            catch (...)
            {
                _error_listener->Add(lvalue, "Error while parsing left value expression of a binary expression.");
            }

            std::shared_ptr<Expression> right_expression;
            try
            {
                auto right = this->visit(rvalue)
                                 .as<Expression *>();
                right_expression = std::shared_ptr<Expression>(right);
            }
            catch (...)
            {
                _error_listener->Add(rvalue, "Error while parsing right value expression of a binary expression");
            }

            std::shared_ptr<Operator> opr_expression;
            auto expr_operator = new Operator(opr->getText());
            if (OPERATOR_INVALID != expr_operator->GetOperatorType())
            {
                opr_expression = std::shared_ptr<Operator>(expr_operator);
            }

            Expression *binary_expression = nullptr;
            if ((left_expression) && (opr_expression) && (right_expression))
            {
                auto type = DeduceType(left_expression,
                opr_expression, right_expression);
                binary_expression = new BinaryExpression(left_expression,
                opr_expression, right_expression, type);
                VisitorHelper::AssignPositions(binary_expression, context);

            }
            return Any(binary_expression);
        }

        std::shared_ptr<TypeSpecification>
        ExpressionVisitor::DeduceType(std::shared_ptr<Expression> left_expr,
                                      std::shared_ptr<Operator> opr,
                                      std::shared_ptr<Expression> right_expr)
        {
            auto left_type = left_expr->GetType();
            auto right_type = right_expr->GetType();

            if ((!left_type) || (!opr) || (!right_type))
            {
                return std::shared_ptr<TypeSpecification>(nullptr);
            }

            const auto opr_type = opr->GetOperatorType();
            switch (opr_type)
            {
            case OPERATOR_EQUAL:
            case OPERATOR_NOT_EQUAL:
            case OPERATOR_GREATER_THAN:
            case OPERATOR_LESS_THAN:
            case OPERATOR_GREATER_THAN_EQUAL:
            case OPERATOR_LESS_THAN_EQUAL:
            case OPERATOR_LOGICAL_AND:
            case OPERATOR_LOGICAL_OR:
                return std::shared_ptr<TypeSpecification>(new BasicTypeSpec(BASIC_DATA_TYPE_BOOL));
            default:
                break;
            }

            if ((left_type->GetType() == TYPE_SPEC_BASIC) &&
                (right_type->GetType() == TYPE_SPEC_BASIC))
            {
                auto left_basic_type = static_pointer_cast<BasicTypeSpec>(left_type);
                auto right_basic_type = static_pointer_cast<BasicTypeSpec>(right_type);
                const auto ltype = left_basic_type->GetDataType();
                const auto rtype = right_basic_type->GetDataType();
                BasicDataTypeType expr_type = BASIC_DATA_TYPE_INVALID;
                switch (ltype)
                {
                case BASIC_DATA_TYPE_BYTE:
                    expr_type = GetOperatedTypeByte(opr_type, rtype);
                    break;

                case BASIC_DATA_TYPE_INT:
                    expr_type = GetOperatedTypeInt(opr_type, rtype);
                    break;

                case BASIC_DATA_TYPE_DOUBLE:
                    expr_type = GetOperatedTypeDouble(opr_type, rtype);
                    break;

                case BASIC_DATA_TYPE_BOOL:
                    expr_type = GetOperatedTypeBool(opr_type, rtype);
                    break;

                case BASIC_DATA_TYPE_CHAR:
                    expr_type = GetOperatedTypeChar(opr_type, rtype);
                    break;

                case BASIC_DATA_TYPE_STRING:
                    expr_type = GetOperatedTypeString(opr_type, rtype);
                    break;

                case BASIC_DATA_TYPE_INVALID:
                    expr_type = BASIC_DATA_TYPE_INVALID;
                }

                if (BASIC_DATA_TYPE_INVALID == expr_type)
                {
                    auto ltype_name = GetBasicDataTypeName(ltype);
                    auto rtype_name = GetBasicDataTypeName(rtype);
                    auto opr_name = Operator::GetOperatorSymbol(opr_type);
                    std::ostringstream out;
                    out << "operator \"" << opr_name << "\" "
                        << "cannot be applied as ("
                        << ltype_name << ") " << opr_name
                        << " (" << rtype_name << ")";
                    const auto message = out.str();
                    throw InvalidExprType(message);
                }
                else
                {
                    return std::shared_ptr<TypeSpecification>(new BasicTypeSpec(expr_type));
                }
            }

            return std::shared_ptr<TypeSpecification>(nullptr);
        }
    } // namespace parser
} // namespace hoo