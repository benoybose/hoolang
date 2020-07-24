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

class ClassMethodTest01 : public ParserTestUnitBase
{
public:
    ClassMethodTest01()
    {
        // RegisterTestCase("EmptyFunctionTest",
        //                  &ClassMethodTest01::EmptyFunctionTest);
        RegisterTestCase("FunctionReturnTypeTest",
                         &ClassMethodTest01::FunctionReturnTypeTest);
    }

private:
    std::shared_ptr<FunctionDefinition> GetClassMethod(const std::string source,
                                                       const std::string &expcted_class_name,
                                                       const std::string &expected_func_name)
    {
        auto unit = DoesNotThrowAndReturn<ParseException,
                                          std::shared_ptr<hoo::ast::Unit>>([this, source]()
                                                                               -> std::shared_ptr<hoo::ast::Unit> {
            auto unit = ParseUnit(source);
            return unit;
        });
        NotNull(unit);

        auto class_definition = GetClassByName(unit, expcted_class_name);
        NotNull(class_definition);

        auto function_definitions = GetFunctionsByName(class_definition, expected_func_name);
        NotEmpty(function_definitions);
        auto func_def = *function_definitions.begin();
        return func_def;
    }

public:
    void EmptyFunctionTest()
    {
        std::ostringstream out;
        out << "class Maths {" << std::endl
            << "\tpublic func add() {" << std::endl
            << "\t}" << std::endl
            << "}";
        auto source = out.str();
        auto func_def = GetClassMethod(source, "Maths", "add");
        auto func_decl = func_def->GetDeclaration();
        auto declarator = func_decl->GetDeclarator();
        Equal(declarator, DECLARATOR_PUBLIC);
        auto return_type = func_decl->GetReturnType();
        Null(return_type);
    }

    void FunctionReturnTypeTest()
    {
        std::ostringstream out;
        out << "class Bar {" << std::endl
            << "\tpublic func:int foo() {" << std::endl
            << "\t\treturn 23;"
            << "\t}" << std::endl
            << "}";
        const auto source = out.str();
        const auto class_name = "Bar";
        const auto function_name = "foo";

        auto func_def = GetClassMethod(source, class_name, function_name);
        auto func_decl = func_def->GetDeclaration();
        auto declarator = func_decl->GetDeclarator();
        Equal(declarator, DECLARATOR_PUBLIC);
        auto return_type = func_decl->GetReturnType();
        VerifyType(return_type, BASIC_DATA_TYPE_INT);
        auto func_body = func_def->GetBody();
        auto compound_stmt = AsCompoundStatement(func_body);
        auto body_return_type = compound_stmt->GetReturnType();
        // NotNull(body_return_type);
    }
};

HOO_TEST_CASE(ClassMethodTest01)