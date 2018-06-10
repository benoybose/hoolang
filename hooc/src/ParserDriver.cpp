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

    ParserDriver::ParserDriver(std::istream *stream, std::string file) {
        this->_file = file;
        this->_scanner = new yyFlexLexer(*stream, std::cout);
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
        Token inputToken =  (Token) this->_scanner->yylex();
        switch(inputToken) {
            case Token::TOKEN_OPR_ADD:
            case Token::TOKEN_OPR_DIV:
            case Token::TOKEN_OPR_MUL:
            case Token::TOKEN_OPR_SUB:
            case Token::TOKEN_OPR_MOD:
                lval->build(this->CreateOperator(inputToken));
                break;
        }
        return inputToken;
    }

    std::string* ParserDriver::getFile() {
        return &this->_file;
    }

    void Parser::error(const std::string &msg) {

    }

    Operator ParserDriver::CreateOperator(hooc::Token inputToken) {
        switch (inputToken) {
            case Token::TOKEN_OPR_ADD: return Operator(OperatorType::Add);
            case Token::TOKEN_OPR_SUB: return Operator(OperatorType::Subtract);
            case Token::TOKEN_OPR_MUL: return Operator(OperatorType::Multiplication);
            case Token::TOKEN_OPR_DIV: return Operator(OperatorType::Division);
            case Token::TOKEN_OPR_MOD: return Operator(OperatorType::Modulation);
            default: return Operator();
        }
    }
}

int yyFlexLexer::yywrap() {
    return 1;
}
