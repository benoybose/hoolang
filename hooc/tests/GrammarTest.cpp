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

#define BOOST_TEST_MODULE "Grammar Test"

#include "compiler/ParserDriver.hh"
#include "antlr4-runtime.h"
#include "ast/Unit.h"
#include "ast/Statement.hh"
#include "ast/Declaration.hh"
#include "ast/TypeSpecification.hh"

#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <string>

using namespace std;
using namespace hooc;
using namespace hooc::compiler;
using namespace hooc::ast;

BOOST_AUTO_TEST_SUITE(GrammarTest)

    BOOST_AUTO_TEST_CASE(ClassDefinision) {
//        auto source_path = boost::filesystem::absolute("test.hoo").string();
//        const std::string source = "namespace test.grammar;\n"
//                                   "\n"
//                                   "class Application\n"
//                                   "{\n"
//                                   "\tfunc:int (args:string[]) main\n"
//                                   "\t{\n"
//                                   "\t\tvar result = add(10, 45);\n"
//                                   "\t\tconsole.print(result);\n"
//                                   "\t}\n"
//                                   "\t\n"
//                                   "\tfunc:int(a:int, b:int) add\n"
//                                   "\t{\n"
//                                   "\t\treturn a + b;\n"
//                                   "\t}\n"
//                                   "}";
//        ParserDriver driver(source, source_path);
//        auto unit = driver.BuildCompilationUnit();
    }

    BOOST_AUTO_TEST_CASE(SimpleVaraibleDeclaration) {
        BOOST_TEST_MESSAGE("Testing variable declaration without initializer");
        auto source_path = boost::filesystem::absolute("test.hoo").string();
        auto variable_declaration1 = "var age:int;";
        ParserDriver driver1(variable_declaration1, source_path);
        auto module1 = driver1.BuildCompilationUnit();
        BOOST_CHECK(nullptr != module1);
        auto unit = module1->GetUnit();
        BOOST_CHECK(nullptr != unit);
        auto unit_items = unit->GetItems();
        BOOST_CHECK(1 == unit_items.size());
        auto item = *(unit_items.begin());
        auto item_type = item->GetUnitItemType();
        BOOST_CHECK(UNIT_ITEM_STATEMENT == item_type);
        auto statement = (Statement *) item;
        auto statement_type = statement->GetStatementType();
        BOOST_CHECK(statement_type == STMT_DECLARATION);
        auto stmt_declaration = (DeclarationStatement *) statement;
        auto declaration = stmt_declaration->GetDeclaration();
        BOOST_CHECK(nullptr != declaration);

        auto declarator = declaration->GetDeclarator();
        auto name = declaration->GetName();
        auto type = declaration->GetDelcaredType();

        BOOST_CHECK(declarator == "var");
        BOOST_CHECK(name == "age");
        BOOST_CHECK(nullptr != type);
        auto type_name = type->GetName();
        BOOST_CHECK(type_name == "int");
    }

    BOOST_AUTO_TEST_CASE(VariableDeclarationInitializer) {
        BOOST_TEST_MESSAGE("Testing variable declaration with initializer");
        auto source_path = boost::filesystem::absolute("test.hoo").string();
        auto variable_declaration2 = "var age:int = 362880;";
        ParserDriver driver2(variable_declaration2, source_path);
        auto compilation_unit2 = driver2.BuildCompilationUnit();
        BOOST_CHECK(nullptr != compilation_unit2);
    }

BOOST_AUTO_TEST_SUITE_END()