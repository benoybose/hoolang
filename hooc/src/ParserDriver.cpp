/*
 * Copyright 2018 Benoy Bose
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

#include <ParserDriver.hh>

#include "ParserDriver.hh"
#include "Listener.hh"
#include "antlr4-runtime.h"
#include "HooLexer.h"
#include "HooParser.h"

using namespace hooc;
using namespace antlr4;
using namespace antlr4::tree;

namespace hooc
{
    class ErrorLister: public BaseErrorListener
    {
        void syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line, size_t charPositionInLine,
                         const std::string &msg, std::exception_ptr e) override {

        }

        void reportAmbiguity(Parser *recognizer, const dfa::DFA &dfa, size_t startIndex, size_t stopIndex, bool exact,
                             const antlrcpp::BitSet &ambigAlts, atn::ATNConfigSet *configs) override {

        }

        void reportAttemptingFullContext(Parser *recognizer, const dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
                                         const antlrcpp::BitSet &conflictingAlts, atn::ATNConfigSet *configs) override {

        }

        void reportContextSensitivity(Parser *recognizer, const dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
                                      size_t prediction, atn::ATNConfigSet *configs) override {

        }

    };

    ParserDriver::ParserDriver(const std::string &source_code): _source_code(source_code) {
    }

    bool ParserDriver::Compile(Unit* unit) {
            ANTLRInputStream* stream = nullptr;
            HooLexer* lexer = nullptr;
            CommonTokenStream* tokens = nullptr;
            HooParser* parser = nullptr;
            HooParser::UnitContext* tree = nullptr;
            auto error = false;

            try {
                    stream = new ANTLRInputStream(this->_source_code);
                    lexer = new HooLexer(stream);
                    tokens = new CommonTokenStream(lexer);
                    parser = new HooParser(tokens);
                    parser->addErrorListener(new ErrorLister());
                    auto errorHandler = std::shared_ptr<ANTLRErrorStrategy>(new DefaultErrorStrategy());
                    parser->setErrorHandler( errorHandler );
                    tree = parser->unit();

                    if(nullptr == tree) {
                        error = true;
                    }

                    if(nullptr != tree->exception) {
                        error = true;
                    }

            } catch(const ParseCancellationException& ex) {
                    error = true;
            }

            if(nullptr != stream) {
                    delete stream;
            }

            if(nullptr != lexer) {
                    delete lexer;
            }


            if(nullptr != tokens) {
                    delete tokens;
            }

            if(nullptr != parser) {
                    delete parser;
            }

            return (!error);
    }
}
