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

#ifndef PARSERDRIVER_HH
#define PARSERDRIVER_HH

#include <HooParser.h>

#include <hoo/ast/Unit.hh>
#include <hoo/parser/ParserContext.hh>

#include <string>
#include <list>
#include <memory>

namespace hoo
{
    namespace parser
    {
        class ParserDriver
        {
        private:
            std::string _source_code;
            std::string _name;
            bool _debug;

        public:
            ParserDriver(const std::string &source_code,
            const std::string& name,
            bool debug = false);

        public:
            std::shared_ptr<hoo::ast::Unit> Build();
        };
    } // namespace parser
} // namespace hoo

#endif //PROJECT_PARSERDRIVER_HH
