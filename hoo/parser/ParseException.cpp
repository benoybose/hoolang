#include <hoo/parser/ParseException.hh>

#include <list>

namespace hoo
{
    namespace parser
    {
        ParseException::ParseException(std::list<std::shared_ptr<BaseError>> errors)
            : _errors(errors)
        {
        }

        const std::list<std::shared_ptr<BaseError>> &ParseException::GetErrors() const
        {
            return this->_errors;
        }
    } // namespace parser
} // namespace hoo