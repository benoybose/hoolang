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

/**
 * File: Module.cpp
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#include "Module.hh"

#include <string>
#include <Poco/RegularExpression.h>
#include <exception>

namespace hooc {
    Module::Module(std::string fileName, std::string nameSpace):
            _fileName(fileName) {
        if ((nameSpace.empty()) || (!IsNamespaceValid(nameSpace))) {
            _nameSpace = "global";
        } else {
            _nameSpace = nameSpace;
        }
    }

    void Module::Add(hooc::ast::Statement statement) {
        this->_statementList->Add(statement);
    }

    std::string Module::NormalizeName() {
        const Poco::RegularExpression regExp("[a-zA-Z_][a-zA-Z0-9_]*");
        std::string moduleName;
        if(0 == regExp.extract(this->_fileName, moduleName)) {
            throw std::invalid_argument("File name is not acceptable.");
        } else {
            this->_moduleName = moduleName;
        }
    }

    bool Module::IsNamespaceValid(std::string nameSpace) {
        const Poco::RegularExpression regExp("^([a-zA-Z_][a-zA-Z0-9_]*)([\\.]([a-zA-Z_][a-zA-Z0-9_]*))*$");
        return regExp.match(nameSpace);
    }
}