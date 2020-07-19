#ifndef _PARSE_EXCEPTION_H
#define _PARSE_EXCEPTION_H

#include <hoo/parser/SyntaxError.hh>
#include <hoo/parser/ParseError.hh>

#include <exception>
#include <list>
#include <memory>

namespace hoo
{
    namespace parser
    {
        class ParseException : std::exception
        {
        private:
            std::list<std::shared_ptr<SyntaxError>> _syntax_errors;
            std::list<std::shared_ptr<ParseError>> _parse_errors;

        public:
            ParseException(std::list<std::shared_ptr<SyntaxError>> syntax_errors,
                           std::list<std::shared_ptr<ParseError>> parse_errors);

        public:
            std::list<std::shared_ptr<SyntaxError>> GetSyntaxErrors() const;
            std::list<std::shared_ptr<ParseError>> GetParseErrors() const;
        };
    } // namespace parser
} // namespace hoo

#endif