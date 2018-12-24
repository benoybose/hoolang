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
#include "CompilationError.hh"
#include "ParseContext.hh"

#include <exception>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>

using namespace hooc;
using namespace antlr4;
using namespace antlr4::tree;

namespace hooc {
    class ErrorLister : public BaseErrorListener {
    private:
        std::list<CompilationError> _errors;

    public:
        void syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line, size_t charPositionInLine,
                         const std::string &msg, std::exception_ptr e) override {
            CompilationError error(line, charPositionInLine, msg);
            this->_errors.push_back(error);
        }

        const std::list<CompilationError> &GetSyntaxErrors() const {
            return this->_errors;
        }
    };

    ParserDriver::ParserDriver(const std::string &source_code, const std::string &file_path) :
            _source_code(source_code) {
        this->_file_path = boost::filesystem::relative(file_path,
                boost::filesystem::current_path());
    }

    CompilationUnit *ParserDriver::Compile(CompilationErrorList &errors) {
        CompilationUnit *unit = nullptr;
        ParseContext parseContext(this->_source_code);
        ErrorLister errorListener;
        parseContext.AddErrorListener(&errorListener);

        try {
            auto unitContext = parseContext.GetUnitContext();
            if (nullptr == unitContext) {
                throw std::runtime_error("Parsing failed because of unknown error.");
            }

            if (0 < errorListener.GetSyntaxErrors().size()) {
                auto errors = errorListener.GetSyntaxErrors();
                std::ostringstream message;
                for (auto iterator = errors.begin(); iterator != errors.end(); ++iterator) {
                    auto error = *(iterator);
                    message << "Error on line number " << error.GetLineNumber()
                            << " at column " << error.GetCharacterPosition()
                            << ". " << error.GetMessage()
                            << std::endl;

                    errors.push_back(error);
                }
                throw std::runtime_error(message.str());
            }

            if (nullptr != unitContext->exception) {
                throw std::current_exception();
            }

            unit = new CompilationUnit(
                    boost::filesystem::current_path(),
                    this->_file_path);
            Compile(unitContext, unit, errors);

        } catch (const std::exception &ex) {
            Logger::Error(ex.what());
            if (nullptr != unit) {
                delete unit;
            }
            CompilationError error(-1, -1, ex.what());
            errors.push_back(error);
        }
        return unit;
    }

    bool ParserDriver::Compile(UnitContext context,
                               CompilationUnit *unit,
                               CompilationErrorList &errors) {
        bool success = true;
        auto classDefinition = context->classDefinition();
        if(nullptr == classDefinition) {

        }

        return success;
    }
}
