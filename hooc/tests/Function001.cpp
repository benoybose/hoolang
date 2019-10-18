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
#include "ast/Unit.hh"
#include "ast/Statement.hh"
#include "ast/ReferenceExpression.hh"
#include "ast/ArrayAccessExpression.hh"
#include "ast/LiteralExpression.hh"
#include "HoocTestHelper.hh"

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <ast/ExpressionStatement.hh>
#include <ast/FunctionDefinition.hh>
#include <ast/BasicDataTypeSpecification.hh>

using namespace std;
using namespace hooc;
using namespace hooc::compiler;
using namespace hooc::ast;

BOOST_AUTO_TEST_SUITE(Function001)

    BOOST_AUTO_TEST_CASE(F1) {
        std::string source = "func:int add(a:int, b:int) { return a + b; }";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        auto items = unit->GetItems();
        auto first_item = *(items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_DEFINITION, first_item->GetUnitItemType());
        auto definition = (Definition* ) first_item;
        BOOST_CHECK_EQUAL(DEFINITION_FUNCTION, definition->GetDefinitionType());
        auto func_def = (FunctionDefinition*) definition;
        auto func_decl = func_def->GetDeclaration();
        BOOST_CHECK_EQUAL("add", func_decl->GetName());
        auto func_return_type = func_decl->GetReturnType();
        BOOST_CHECK_NE(nullptr, func_return_type);
        BOOST_CHECK_EQUAL(TYPE_SPEC_BASIC, func_return_type->GetType());
        BOOST_CHECK_EQUAL("int", func_return_type->GetName());
        auto basic_type = (BasicDataTypeSpecification *) func_return_type;
        BOOST_CHECK_EQUAL(BASIC_DATA_TYPE_INT, basic_type->GetDataType());
        auto parameters = func_decl->GetParamList();
        BOOST_CHECK_EQUAL(2, parameters.size());
        auto param1 = *(parameters.begin());
        BOOST_CHECK_EQUAL("a", param1->GetName());
        BOOST_CHECK_EQUAL("int", param1->GetDelcaredType()->GetName());
        auto param2 = *(++ parameters.begin());
        BOOST_CHECK_EQUAL("b", param2->GetName());
        BOOST_CHECK_EQUAL("int", param2->GetDelcaredType()->GetName());
        auto statements = func_def->GetStatements();
        BOOST_CHECK_EQUAL(STMT_COMPOUND, statements->GetStatementType());
    }

BOOST_AUTO_TEST_SUITE_END()

