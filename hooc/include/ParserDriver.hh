//
// Created by COMP on 10-06-2018.
//

#ifndef HOOC_PARSERDRIVER_HH
#define HOOC_PARSERDRIVER_HH

#include <string>
#include "Parser.hh"
#include "FlexScanner.hh"
#include <istream>

namespace hooc {
    class ParserDriver {
    private:
        std::string _file = "";
        yyFlexLexer* _scanner = nullptr;
        std::istream* _fileInputStream = nullptr;
        Parser* _parser = nullptr;

    public:
        explicit ParserDriver(std::string file);
        virtual ~ParserDriver();

    public:
        int Parse();
        int Scan(hooc::Parser::semantic_type* lval);
        std::string* getFile();
    };
}

#endif //HOOC_PARSERDRIVER_HH
