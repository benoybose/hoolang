//
// Created by COMP on 10-06-2018.
//

#ifndef HOOC_PARSERDRIVER_HH
#define HOOC_PARSERDRIVER_HH

#include <string>
#include "Parser.hh"
#include "FlexScanner.hh"
#include "hcoperator.hh"
#include <istream>


namespace hooc {
    typedef hooc::Parser::token_type Token;

    class ParserDriver {
    private:
        std::string _file = "";
        yyFlexLexer* _scanner = nullptr;
        std::istream* _fileInputStream = nullptr;
        Parser* _parser = nullptr;

    public:
        explicit ParserDriver(std::string file);
        ParserDriver(std::istream* stream, std::string file);
        virtual ~ParserDriver();

    public:
        int Parse();
        int Scan(hooc::Parser::semantic_type* lval);
        std::string* getFile();

    private:
        Operator CreateOperator(Token inputToken);

    };
}

#endif //HOOC_PARSERDRIVER_HH
