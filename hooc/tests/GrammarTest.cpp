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
    auto stream = new ANTLRInputStream("name");
    auto lexer = new HooLexer(stream);
    auto tokens = new CommonTokenStream(lexer);
    auto parser = new HooParser(tokens);
    auto tree = parser->primaryExpression();
    auto walker = new ParseTreeWalker();
    auto listener = new Listener();
    walker->walk(listener, tree);

    delete listener;
    delete walker;
    delete tree;
    // delete parser;
    delete tokens;
    delete lexer;
    delete stream;
}