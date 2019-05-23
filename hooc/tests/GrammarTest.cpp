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

#define BOOST_TEST_MODULE Arithmetic Statement Test

#include "compiler/ParserDriver.hh"
#include "antlr4-runtime.h"

#include <boost/test/included/unit_test.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace hooc;
using namespace hooc::compiler;

BOOST_AUTO_TEST_CASE(GrammarTest) {
    auto source_path = boost::filesystem::absolute("test.hoo")
            .string();

    const std::string source = "namespace test.grammar;\n"
                               "\n"
                               "class Application\n"
                               "{\n"
                               "\tfunc:int (args:string[]) main\n"
                               "\t{\n"
                               "\t\tvar result = add(10, 45);\n"
                               "\t\tconsole.print(result);\n"
                               "\t}\n"
                               "\t\n"
                               "\tfunc:int(a:int, b:int) add\n"
                               "\t{\n"
                               "\t\treturn a + b;\n"
                               "\t}\n"
                               "}";
    ParserDriver driver(source, source_path);
    auto unit = driver.Compile();
}