#define BOOST_TEST_MODULE Arithmetic Statement Test

#include "ParserDriver.hh"
#include "antlr4-runtime.h"

#include <boost/test/included/unit_test.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace hooc;

BOOST_AUTO_TEST_CASE(GrammarTest) {
    auto source_path = boost::filesystem::absolute("test.hoo")
            .string();

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
    ParserDriver driver(source, source_path);
    CompilationErrorList errors;
    auto unit = driver.Compile(errors);
}