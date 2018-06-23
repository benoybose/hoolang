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
#include "Statement.hh"
#include "ExpressionStatement.hh"
#include "hcstmtlist.hh"

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
        ast::Operator Operator(char op);
        ast::Expression LiteralExpression(hooc::LiteralType literalType, std::string input);
        ast::Expression BinaryExpression(ast::Expression& lvalue,
                                               ast::Operator& opr, ast::Expression& rvalue);
        ast::Statement ExpressionStatement(ast::Expression expression);
        ast::StatementList StatementList(ast::Statement statement);
    };
}

#endif //HOOC_PARSERDRIVER_HH
