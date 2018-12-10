#define BOOST_TEST_MODULE Lexer Test

#include "Lexer.hh"

#include <boost/test/included/unit_test.hpp>
#include <sstream>
#include <boost/regex.hpp>
#include <list>
#include <array>

using namespace hooc;
using namespace std;

BOOST_AUTO_TEST_CASE(Test001_LexerTest_Integers) {
    istringstream stream("23 560 7876");
    Lexer lexer(stream);
    lexer.Add(200, "\\d+");
    lexer.Add(201, "\\s+");

    auto descriptors = lexer.GetDescriptors();
    BOOST_CHECK(2 == lexer.GetDescriptors().size());

    auto desc1 = *descriptors.begin();
    auto desc2 = *(++descriptors.begin());

    BOOST_CHECK(200 == desc1.GetTokenId());
    BOOST_CHECK(201 == desc2.GetTokenId());

    BOOST_CHECK("\\d+" == desc1.GetPattern().str());
    BOOST_CHECK("\\s+" == desc2.GetPattern().str());

    std::list<Token> tokens;
    bool tokenized = false;
    do {
        LexerError error;
        Token token;
        tokenized = lexer.Tokenize(error, token);
        if(tokenized) {
            tokens.push_back(token);
        }
    } while(tokenized);

    BOOST_CHECK(5 == tokens.size());
    std::array<Token, 5> token_array;

    BOOST_CHECK(200 == token_array[0].GetTokenId());
    BOOST_CHECK("23" == token_array[0].GetText());

    BOOST_CHECK(201 == token_array[1].GetTokenId());
    BOOST_CHECK(" " == token_array[1].GetText());

}