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