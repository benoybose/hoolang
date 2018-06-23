#include "Parser.hh"
#include "ParserDriver.hh"
#include "FlexScanner.hh"
#include "Logger.hh"

#include "LiteralExpression.hh"

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
            case hooc::Token::TOKEN_LITERAL_INT:
                lval->build(std::string(this->_scanner->YYText()));
                break;
        }
        lval->build(std::string(this->_scanner->YYText()));
        return inputToken;
    }

    ast::Operator ParserDriver::CreateOperator(char op) {
        switch(op) {
            case '+': return ast::Operator(new Operator(hooc::OperatorType::AddOperator));
            case '-': return ast::Operator(new Operator(hooc::OperatorType::SubtractOperator));
            case '*': return ast::Operator(new Operator(hooc::OperatorType::MultiplicationOperator));
            case '/': return ast::Operator(new Operator(hooc::OperatorType::DivisionOperator));
            case '%': return ast::Operator(new Operator(hooc::OperatorType::ModulationOperator));
        }
    }

    ast::Expression ParserDriver::CreateLiteralExpression(hooc::LiteralType literalType,
                                                          std::string input) {
        ast::Expression expression = ast::Expression(new LiteralExpression(literalType, input.c_str()));
        return expression;
    }

    ast::Expression ParserDriver::CreateBinaryExpression(ast::Expression &lvalue,
                                                         ast::Operator &opr,
                                                         ast::Expression &rvalue) {
        ast::Expression binaryExpression = ast::Expression(new BinaryExpression(lvalue, opr, rvalue));
        return binaryExpression;
    }

    std::string* ParserDriver::getFile() {
        return &this->_file;
    }

    void Parser::error(const std::string &msg) {
        hooc::Logger::Error(msg);
    }
}

int yyFlexLexer::yywrap() {
    return 1;
}
