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

    UseSpecification::UseSpecification(const Namespace &_namespace, const std::string &name) : _namespace(
            _namespace), _name(name) {

    }

    const Namespace &UseSpecification::GetNamespace() const {
        return _namespace;
    }

    const std::string &UseSpecification::GetName() const {
        return _name;
    }

    void UseSpecification::SetNamespace(const Namespace &_namespace) {
        UseSpecification::_namespace = _namespace;
    }

    void UseSpecification::SetName(const std::string &_name) {
        UseSpecification::_name = _name;
    }
}