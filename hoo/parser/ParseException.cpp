#include <hoo/parser/ParseException.hh>

#include <list>

namespace hoo
{
    namespace parser
    {
        ParseException::ParseException(std::list<BaseError *> errors)
            : _errors(std::move(errors))
        {
        }

        const std::list<BaseError *> &ParseException::GetErrors() const
        {
            return this->_errors;
        }
    } // namespace parser
} // namespace hoo