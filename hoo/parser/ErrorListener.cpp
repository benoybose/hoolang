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

#include <hoo/parser/ErrorListener.hh>
#include <hoo/parser/ParseError.hh>
#include <hoo/parser/SyntaxError.hh>
#include <hoo/parser/BaseError.hh>
#include "antlr4-runtime.h"

#include <sstream>

using namespace antlr4;

namespace hoo
{
    namespace parser
    {
        void ErrorListener::syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line,
                                        size_t charPositionInLine, const std::string &msg,
                                        std::exception_ptr e)
        {
            auto error = CreateSyntaxError(offendingSymbol, msg);
            this->_errors.push_back(error);
        }

        void ErrorListener::Add(ParserRuleContext *ctx, const std::string &message)
        {
            auto start = ctx->getStart();
            auto error = CreateSyntaxError(start, message);
            this->_errors.push_back(error);
        }

        void ErrorListener::Add(ErrorCode error_code, const std::string &message)
        {
            auto error = CreateParseError(error_code, message);
            this->_errors.push_back(error);
        }

        std::shared_ptr<BaseError> ErrorListener::CreateSyntaxError(Token *start,
                                                                    const std::string &message)
        {
            auto errorText = start->getText();
            if (20 > errorText.length())
            {
                errorText = errorText.substr(0, 20);
                errorText = errorText += "...";
            }

            auto line = start->getLine();
            auto column = start->getCharPositionInLine();

            std::stringstream out;
            out << "Syntax error on line: "
                << line
                << ", column: "
                << column
                << " near \'" << errorText << "\'.";
            if (!message.empty())
            {
                out << " " << message;
            }
            auto msg = out.str();
            BaseError *error = (BaseError *)new SyntaxError(line, column, msg);
            return std::shared_ptr<BaseError>(error);
        }

        std::shared_ptr<BaseError> ErrorListener::CreateParseError(ErrorCode error_code,
                                                    const std::string &message)
        {
            BaseError *error = (BaseError*) new ParseError(error_code, message);
            return std::shared_ptr<BaseError>(error);
        }

        ErrorListener::~ErrorListener()
        {
        }

        const std::list<std::shared_ptr<BaseError>> &ErrorListener::GetErrors() const
        {
            return this->_errors;
        }

        ErrorListener::ErrorListener() : BaseErrorListener()
        {
        }
    } // namespace parser
} // namespace hoo
