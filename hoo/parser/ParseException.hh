#ifndef _PARSE_EXCEPTION_H
#define _PARSE_EXCEPTION_H

#include <hoo/parser/BaseError.hh>

#include <exception>
#include <list>

namespace hoo
{
    namespace parser
    {
        class ParseException : std::exception
        {
        private:
            std::list<BaseError *> _errors;

        public:
            ParseException(std::list<BaseError *> errors);

        public:
            const std::list<BaseError *> &GetErrors() const;
        };
    } // namespace parser
} // namespace hoo

#endif