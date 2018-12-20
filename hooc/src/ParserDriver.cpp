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

#include "ParserDriver.hh"
#include "Listener.hh"
#include "antlr4-runtime.h"
#include "HooLexer.h"
#include "HooParser.h"
#include "Logger.hh"

#include <exception>
#include <boost/log/trivial.hpp>

using namespace hooc;
using namespace antlr4;
using namespace antlr4::tree;

namespace hooc {
    SyntaxError::SyntaxError(size_t lineno, size_t columnno, const std::string &message) :
            _lineno(lineno),
            _columnno(columnno),
            _message(message) {
    }

    int SyntaxError::GetLineNumber() const {
        return this->_lineno;
    }

    int SyntaxError::GetColumnnNumber() const {
        return this->_columnno;
    }

    const std::string &SyntaxError::GetMessage() const {
        return this->_message;
    }

    class ErrorLister : public BaseErrorListener {
    private:
        std::list<SyntaxError> _errors;

    public:
        void syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line, size_t charPositionInLine,
                         const std::string &msg, std::exception_ptr e) override {
            SyntaxError error(line, charPositionInLine, msg);
            this->_errors.push_back(error);
        }

        const std::list<SyntaxError> &GetSyntaxErrors() const {
            return this->_errors;
        }
    };

    ParserDriver::ParserDriver(const std::string &source_code, const std::string &file_path) :
            _source_code(source_code) {
    }

    bool ParserDriver::Compile(Unit *unit) {
        ANTLRInputStream *stream = nullptr;
        HooLexer *lexer = nullptr;
        CommonTokenStream *tokens = nullptr;
        HooParser *parser = nullptr;
        HooParser::UnitContext *tree = nullptr;
        auto error = false;
        auto errorListener = new ErrorLister();

        try {
            stream = new ANTLRInputStream(this->_source_code);
            lexer = new HooLexer(stream);
            tokens = new CommonTokenStream(lexer);
            parser = new HooParser(tokens);
            parser->addErrorListener(errorListener);
            auto errorHandler = std::shared_ptr<ANTLRErrorStrategy>(new DefaultErrorStrategy());
            parser->setErrorHandler(errorHandler);
            tree = parser->unit();

            if (nullptr == tree) {
                throw std::runtime_error("Parsing failed because of unknown error");
            }

            if (0 < errorListener->GetSyntaxErrors().size()) {
                auto errors = errorListener->GetSyntaxErrors();
                std::ostringstream message;
                for (auto iterator = errors.begin(); iterator != errors.end(); ++iterator) {
                    auto error = *(iterator);
                    message << "Error on line number " << error.GetLineNumber()
                            << " at column " << error.GetColumnnNumber()
                            << ". " << error.GetMessage()
                            << std::endl;
                }
                throw std::runtime_error(message.str());
            }

            if (nullptr != tree->exception) {
                throw std::current_exception();
            }
        } catch (const std::exception &ex) {

            Logger::Error(ex.what());
            error = true;
        }

        if (nullptr != stream) {
            delete stream;
        }

        if (nullptr != lexer) {
            delete lexer;
        }


        if (nullptr != tokens) {
            delete tokens;
        }

        if (nullptr != parser) {
            delete parser;
        }

        if (nullptr != errorListener) {
            delete errorListener;
        }

        return (!error);
    }
}
