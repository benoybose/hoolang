//
// Created by COMP on 10-06-2018.
//

#ifndef HOOC_PARSERDRIVER_HH
#define HOOC_PARSERDRIVER_HH

#include <string>
#include "Parser.hh"
#include "FlexScanner.hh"
#include "Operator.hh"
#include "Expression.hh"
#include "LiteralExpression.hh"
#include "BinaryExpression.hh"

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

    public:
        ast::Operator CreateOperator(char op);
        ast::Expression CreateLiteralExpression(hooc::LiteralType literalType, std::string input);
        ast::Expression CreateBinaryExpression(ast::Expression& lvalue, ast::Operator& opr, ast::Expression& rvalue);

    };
}

#endif //HOOC_PARSERDRIVER_HH
