#include "Parser.hh"
#include "ParserDriver.hh"
#include "FlexScanner.hh"
#include "Logger.hh"

#include "Operator.hh"
#include "Expression.hh"
#include "LiteralExpression.hh"
#include "BinaryExpression.hh"
#include "Statement.hh"
#include "ExpressionStatement.hh"

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

    ast::Operator ParserDriver::Operator(char op) {
        switch(op) {
            case '+': return ast::Operator(new hooc::Operator(hooc::OperatorType::AddOperator));
            case '-': return ast::Operator(new hooc::Operator(hooc::OperatorType::SubtractOperator));
            case '*': return ast::Operator(new hooc::Operator(hooc::OperatorType::MultiplicationOperator));
            case '/': return ast::Operator(new hooc::Operator(hooc::OperatorType::DivisionOperator));
            case '%': return ast::Operator(new hooc::Operator(hooc::OperatorType::ModulationOperator));
        }
    }

    ast::Expression ParserDriver::LiteralExpression(hooc::LiteralType literalType,
                                                          std::string input) {
        ast::Expression expression(new hooc::LiteralExpression(literalType, input.c_str()));
        return expression;
    }

    ast::Expression ParserDriver::BinaryExpression(ast::Expression &lvalue,
                                                         ast::Operator &opr,
                                                         ast::Expression &rvalue) {
        ast::Expression binaryExpression(new hooc::BinaryExpression(lvalue, opr, rvalue));
        return binaryExpression;
    }

    ast::Statement ParserDriver::ExpressionStatement(hooc::ast::Expression expression) {
        ast::Statement statement(new hooc::ExpressionStatement(expression));
        return statement;
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
