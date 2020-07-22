/*
 * Copyright 2020 Benoy Bose
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

#include <hoo/ast/AST.hh>
#include <hoo/parser/ParseException.hh>

#include <list>
#include <memory>

using namespace hoo::ast;

class ParserTestHelper
{
public:
    ParserTestHelper();

public:
    static std::shared_ptr<Unit> BuildUnit(const std::string &source);
    static std::shared_ptr<ClassDefinition>
    GetClassByName(std::shared_ptr<Unit> unit,
                   const std::string &class_name);
    static std::list<std::shared_ptr<FunctionDefinition>>
    GetFunctionsByName(std::shared_ptr<ClassDefinition> class_definition,
                       const std::string &function_name);
};