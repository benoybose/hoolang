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

#include "CompilationContext.hh"

#include "CompilationContext.hh"

namespace hooc {
    namespace compiler {
        CompilationContext::CompilationContext(std::string source_code) {
            stream = new antlr4::ANTLRInputStream(source_code);
            lexer = new HooLexer(stream);
            tokens = new antlr4::CommonTokenStream(lexer);
            parser = new HooParser(tokens);
            auto errorHandler = std::shared_ptr<antlr4::ANTLRErrorStrategy>(new antlr4::DefaultErrorStrategy());
            parser->setErrorHandler(errorHandler);
            lexer->removeErrorListeners();
            parser->removeErrorListeners();
        }

        CompilationContext::~CompilationContext() {
            if (nullptr != this->parser) {
                delete this->parser;
            }

            if (nullptr != this->tokens) {
                delete this->tokens;
            }

            if (nullptr != this->lexer) {
                delete this->lexer;
            }

            if (nullptr != this->stream) {
                delete this->stream;
            }
        }

        void CompilationContext::AddErrorListener(antlr4::ANTLRErrorListener *errorListener) {
            this->parser->addErrorListener(errorListener);
        }

        HooParser::UnitContext* CompilationContext::GetUnit() {
            return this->parser->unit();
        }
    }
}
