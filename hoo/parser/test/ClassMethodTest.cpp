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

#include "ParserTestUnitBase.hh"

#include <hoo/ast/AST.hh>
#include <hoo/test/HooTest.hh>
#include <hoo/parser/ParserDriver.hh>
#include <hoo/parser/ParseException.hh>

#include <sstream>
#include <memory>

using namespace hoo::ast;
using namespace hoo::test;
using namespace hoo::parser;

class ClassMethodTest : public ParserTestUnitBase
{
public:
    ClassMethodTest()
    {
        // RegisterTestCase("TEST01",
        //                  &ClassMethodTest::TEST01);
        RegisterTestCase("TEST02",
                         &ClassMethodTest::TEST02);
        RegisterTestCase("TEST03",
                         &ClassMethodTest::TEST03);
    }

public:
    void TEST01()
    {
        const auto source = R"source(
        class Maths {
            public func add() {
            }
        }
        )source";
        auto func_def = GetClassMethod(source, "Maths", "add");
        auto func_decl = func_def->GetDeclaration();
        auto declarator = func_decl->GetDeclarator();
        Equal(declarator, DECLARATOR_PUBLIC);
        auto return_type = func_decl->GetReturnType();
        Null(return_type);
    }

    void TEST02()
    {
        const auto source = R"source(
        class Maths {
            public func add(a:int, b:int) {
            }
        }
        )source";
        auto func_def = GetClassMethod(source, "Maths", "add");
        auto func_decl = func_def->GetDeclaration();
        auto declarator = func_decl->GetDeclarator();
        Equal(declarator, DECLARATOR_PUBLIC);
        auto return_type = func_decl->GetReturnType();
        Null(return_type);
    }

    void TEST03()
    {
        const auto source = R"source(
        class Maths {
            public func:int add(a:int, b:int) {
                return a + b;
            }
        }
        )source";
        auto func_def = GetClassMethod(source, "Maths", "add");
        auto func_decl = func_def->GetDeclaration();
        auto declarator = func_decl->GetDeclarator();
        Equal(declarator, DECLARATOR_PUBLIC);
        auto return_type = func_decl->GetReturnType();
        Null(return_type);
    }
};

HOO_TEST_CASE(ClassMethodTest)