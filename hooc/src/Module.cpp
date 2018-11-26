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
#include "StatementList.hh"

#include <string>
#include <exception>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

namespace hooc {
    const std::string NAMESPACE_GLOBAL = "global";

    Module::Module(std::string fileName, std::string nameSpace):
            _fileName(fileName) {
        if ((nameSpace.empty()) || (!IsNamespaceValid(nameSpace))) {
            _nameSpace = NAMESPACE_GLOBAL;
        } else {
            _nameSpace = nameSpace;
        }
        this->_statementList = ast::StatementList(new hooc::StatementList());
        this->_moduleName = this->NormalizeName();
    }

    void Module::Add(hooc::ast::Statement statement) {
        this->_statementList->Add(statement);
    }

    const std::string& Module::GetModuleName() const {
        return this->_moduleName;
    }

    const std::string& Module::GetNameSpaace() const {
        return this->_nameSpace;
    }

    std::string Module::NormalizeName() {
        const boost::filesystem::path path(this->_fileName);
        const boost::regex regex("[a-zA-Z_][a-zA-Z0-9_]*");
        const std::string file_name = path.filename().stem().string();

        boost::match_results<std::string::const_iterator> what;
        std::string::const_iterator start = file_name.begin();
        std::string::const_iterator end = file_name.end();

        if(boost::regex_search(start, end, what, regex, boost::match_default)) {
            std::string match;
            match.assign(what[0].first, what[0].second);
            return match;
        } else {
            return "";
        }
    }

    bool Module::IsNamespaceValid(std::string nameSpace) {
        const boost::regex regex("^([a-zA-Z_][a-zA-Z0-9_]*)([\\.]([a-zA-Z_][a-zA-Z0-9_]*))*$");
        if(boost::regex_match(nameSpace, regex)) {
            return true;
        } else {
            return false;
        }
    }

    const std::list<hooc::ast::Statement>& Module::GetStatements() const {
        return this->_statementList->GetStatements();
    }
}