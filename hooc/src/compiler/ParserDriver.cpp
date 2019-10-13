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

#include "ParserDriver.hh"
#include "antlr4-runtime.h"
#include "CompilationError.hh"
#include "compiler/CompilationContext.hh"
#include "compiler/CompilationError.hh"
#include "compiler/CompilationErrorListener.hh"
#include "visitors/UnitVisitor.hh"

#include <list>
#include <exception>
#include <memory>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>

using namespace hooc;
using namespace hooc::ast;
using namespace antlr4;
using namespace antlr4::tree;

namespace hooc {
    namespace compiler {

        ParserDriver::ParserDriver(const std::string &source_code, const std::string &file_path) :
                _source_code(source_code) {
            this->_file_path = boost::filesystem::relative(file_path,
                                                           boost::filesystem::current_path());
        }

        Module* ParserDriver::BuildModule() {
            CompilationContext context(this->_source_code);
            Module* module = nullptr;
            Unit* unit = nullptr;

            try {
                auto unitContext = context.GetUnit();
                if (nullptr == unitContext) {
                    throw std::runtime_error("Parsing failed because of unknown error.");
                }

                UnitVisitor visitor;
                unit = visitor.visit(unitContext).as<Unit*>();
            } catch (const std::exception &ex) {
                std::string message(ex.what());
                auto error = new CompilationError(0, 0, message);
                context.AddCompilationError(error);
            }

            auto errors = context.GetErrors();
            module = new Module("", "",
                                unit, errors);
            return module;
        }
    }
}
