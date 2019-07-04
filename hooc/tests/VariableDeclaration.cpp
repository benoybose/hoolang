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

#include "compiler/ParserDriver.hh"
#include "antlr4-runtime.h"
#include "ast/Unit.h"
#include "ast/Statement.hh"
#include "ast/Declaration.hh"
#include "ast/TypeSpecification.hh"


#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <ast/LiteralExpression.hh>

using namespace std;
using namespace hooc;
using namespace hooc::compiler;
using namespace hooc::ast;

BOOST_AUTO_TEST_SUITE(VariableDeclaration)

    BOOST_AUTO_TEST_CASE(SimpleVaraibleDeclaration) {
        BOOST_TEST_MESSAGE("Testing variable declaration without initializer");

        auto source = "var age:int;";
        ParserDriver driver1(source, "test.hoo");

        auto module = driver1.BuildModule();
        BOOST_CHECK(nullptr != module);

        auto unit = module->GetUnit();
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

        auto source = "var age:int = 362880;";
        ParserDriver driver(source, "test.hoo");

        auto module = driver.BuildModule();
        BOOST_CHECK(nullptr != module);

        auto unit = module->GetUnit();
        BOOST_CHECK(nullptr != unit);
        BOOST_CHECK(1 == unit->GetItems().size());

        auto item = *unit->GetItems().begin();
        BOOST_CHECK(nullptr != item);
        BOOST_CHECK(UNIT_ITEM_STATEMENT == item->GetUnitItemType());

        auto stmt = (Statement *) item;
        BOOST_CHECK(STMT_DECLARATION == stmt->GetStatementType());

        auto decl = ((DeclarationStatement *) stmt)->GetDeclaration();
        BOOST_CHECK(decl->GetName() == "age");
        BOOST_CHECK(decl->GetDeclarator() == "var");
        BOOST_CHECK(decl->GetDelcaredType()->GetName() == "int");

        auto initializer = decl->GetInitializer();
        BOOST_CHECK(nullptr != initializer);
        BOOST_CHECK(EXPRESSION_LITERAL == initializer->GetExpressionType());
        auto expression = (LiteralExpression *) initializer;
        BOOST_CHECK(LITERAL_INTEGER == expression->GetLiteralType());
        BOOST_CHECK("362880" == expression->GetValue());
    }

BOOST_AUTO_TEST_SUITE_END()