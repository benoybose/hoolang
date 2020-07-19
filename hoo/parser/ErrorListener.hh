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

#ifndef HC_COMPILATIONERRORLISTENER_HH
#define HC_COMPILATIONERRORLISTENER_HH

#include "antlr4-runtime.h"
#include <hoo/parser/SyntaxError.hh>
#include <hoo/parser/ParseError.hh>
#include "ParserRuleContext.h"

#include <list>
#include <memory>

using namespace antlr4;

namespace hoo
{
    namespace parser
    {
        class ErrorListener : public BaseErrorListener
        {

        public:
            ErrorListener();

        private:
            std::list<std::shared_ptr<SyntaxError>> _syntax_errors;
            std::list<std::shared_ptr<ParseError>> _parse_errors;

        public:
            void syntaxError(Recognizer *recognizer,
                             Token *offendingSymbol,
                             size_t line, size_t charPositionInLine,
                             const std::string &msg, std::exception_ptr e) override;

            void Add(ParserRuleContext *ctx, const std::string &message);
            void Add(ErrorCode error_code, const std::string &message);

        public:
            std::list<std::shared_ptr<SyntaxError>> GetSyntaxErrors() const;
            std::list<std::shared_ptr<ParseError>> GetParseErrors() const;
            bool HasErrors() const;

        private:
            std::shared_ptr<SyntaxError> CreateSyntaxError(Token *start,
                                                                          const std::string &message);
            std::shared_ptr<ParseError> CreateParseError(ErrorCode error_code,
                                                                         const std::string &message);

        public:
            virtual ~ErrorListener();
        };
    } // namespace parser
} // namespace hoo

#endif //HC_COMPILATIONERRORLISTENER_HH
