#include "Parser.hh"
#include "ParserDriver.hh"
#include "FlexScanner.hh"
#include <fstream>

#include <string>

namespace hooc {

    ParserDriver::ParserDriver(std::string file) {
        this->_file = file;
        if(file.empty()) {
            this->_scanner = new yyFlexLexer(std::cin, std::cout);
        } else {
            _fileInputStream = new std::ifstream(file, std::ios_base::in);
            this->_scanner = new yyFlexLexer(*_fileInputStream, std::cout);
        }

        this->_parser = new Parser(*this);
    }

    ParserDriver::~ParserDriver() {
        if(nullptr != this->_fileInputStream) {
            delete this->_fileInputStream;
        }

        if(nullptr != this->_scanner) {
            delete this->_scanner;
        }

        if(nullptr != this->_parser) {
            delete this->_parser;
        }
    }

    int ParserDriver::Parse() {
        int success = this->_parser->parse();
        return success;
    }

    int ParserDriver::Scan(hooc::Parser::semantic_type *lval) {
        int token = this->_scanner->yylex();
        return token;
    }

    std::string* ParserDriver::getFile() {
        return &this->_file;
    }

    void Parser::error(const std::string &msg) {

    }
}

int yyFlexLexer::yywrap() {
    return 1;
}
