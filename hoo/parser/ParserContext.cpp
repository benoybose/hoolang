/*
 * Copyright 2019 Benoy Bose
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

#include <hoo/parser/ParserContext.hh>

namespace hoo
{
    namespace parser
    {
        ParserContext::ParserContext(std::string source_code)
        {
            stream = new antlr4::ANTLRInputStream(source_code);
            lexer = new HooLexer(stream);
            tokens = new antlr4::CommonTokenStream(lexer);
            parser = new HooParser(tokens);
            error_listener = new ErrorListener();
            auto errorHandler = std::shared_ptr<antlr4::ANTLRErrorStrategy>(new antlr4::DefaultErrorStrategy());
            parser->setErrorHandler(errorHandler);
            lexer->removeErrorListeners();
            parser->removeErrorListeners();
            parser->addErrorListener(error_listener);
        }

        ParserContext::~ParserContext()
        {
            delete error_listener;
            delete tokens;
            delete lexer;
            delete stream;
            delete parser;
        }

        HooParser::UnitContext *ParserContext::GetUnit()
        {
            return this->parser->unit();
        }

        void ParserContext::AddCompilationError(BaseError *error)
        {
            error_listener->Add(error);
        }

        const std::list<BaseError *> &ParserContext::GetErrors() const
        {
            return error_listener->GetErrors();
        }
    } // namespace parser
} // namespace hoo
