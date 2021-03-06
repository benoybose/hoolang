/*
 * Copyright 2020 Benoy Bose
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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