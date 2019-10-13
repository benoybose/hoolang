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

using namespace std;
using namespace hooc;
using namespace hooc::compiler;
using namespace hooc::ast;

BOOST_AUTO_TEST_SUITE(Function001)

    BOOST_AUTO_TEST_CASE(F1) {
        std::string source = "func:int add(a:int, b:int) { return a + b; }";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
//        BOOST_CHECK(module->Success());
    }

BOOST_AUTO_TEST_SUITE_END()

