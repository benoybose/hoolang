#ifndef _PARSE_EXCEPTION_H
#define _PARSE_EXCEPTION_H

#include <hoo/parser/BaseError.hh>

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
            std::list<std::shared_ptr<BaseError>> _errors;

        public:
            ParseException(std::list<std::shared_ptr<BaseError>> errors);

        public:
            const std::list<std::shared_ptr<BaseError>> &GetErrors() const;
        };
    } // namespace parser
} // namespace hoo

#endif