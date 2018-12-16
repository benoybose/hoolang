#define BOOST_TEST_MODULE Arithmetic Statement Test

#include "StatementList.hh"
#include "ExpressionStatement.hh"
#include "LiteralExpression.hh"
#include "HooLexer.h"
#include "HooParser.h"
#include "Listener.hh"

#include <boost/test/included/unit_test.hpp>

using namespace std;
using namespace hooc;
using namespace antlr4;
using namespace antlr4::tree;

BOOST_AUTO_TEST_CASE(GrammarTest) {
    const std::string source = "namespace test;\n"
                               "\n"
                               "class Application\n"
                               "{\n"
                               "\tfunc (args:string[]) main\n"
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
}