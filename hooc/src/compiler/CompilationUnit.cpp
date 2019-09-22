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

#include "CompilationUnit.hh"

#include <string>
#include <exception>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include "CompilationUnit.hh"


namespace hooc {
    namespace compiler {

        CompilationUnit::CompilationUnit(boost::filesystem::path compilation_root, boost::filesystem::path module_path,
                                         ast::Unit *unit, std::list<CompilationError *> errors)
                : _compilation_root(compilation_root),
                _module_path(module_path),
                _unit(unit),
                _errors(errors){

        }

        CompilationUnit::~CompilationUnit() {
            delete this->_unit;
            while(this->_errors.begin() != this->_errors.end()) {
                auto error = *(this->_errors.begin());
                this->_errors.remove(error);
                delete error;
            }
        }

        const boost::filesystem::path
        &CompilationUnit::GetCompilationRoot() const {
            return this->_compilation_root;
        }

        const boost::filesystem::path
        &CompilationUnit::GetModulePath() const {
            return this->_module_path;
        }

        const ast::Unit *CompilationUnit::GetUnit() {
            return this->_unit;
        }

        bool CompilationUnit::Success() {
            return this->_errors.empty();
        }

        const std::list<CompilationError *> & CompilationUnit::GetErrors() const {
            return this->_errors;
        }
    }
}