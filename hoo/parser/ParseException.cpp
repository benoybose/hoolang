#include <hoo/parser/ParseException.hh>
#include <hoo/parser/SyntaxError.hh>
#include <hoo/parser/ParseError.hh>

#include <list>
#include <memory>

namespace hoo
{
    namespace parser
    {
        ParseException::ParseException(std::list<std::shared_ptr<SyntaxError>> syntax_errors,
                                       std::list<std::shared_ptr<ParseError>> parse_errors)
            : _syntax_errors(syntax_errors),
              _parse_errors(parse_errors)
        {
        }

        std::list<std::shared_ptr<SyntaxError>> ParseException::GetSyntaxErrors() const
        {
            return this->_syntax_errors;
        }

        std::list<std::shared_ptr<ParseError>> ParseException::GetParseErrors() const
        {
            return this->_parse_errors;
        }
    } // namespace parser
} // namespace hoo