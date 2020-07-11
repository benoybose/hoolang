/*
 * Copyright 2019 Benoy Bose
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

#ifndef HOOC_COMPILATION_UNIT_H
#define HOOC_COMPILATION_UNIT_H

#include "BaseError.hh"
#include <hoo/ast/Unit.hh>

#include <string>
#include <memory>
#include <list>

namespace hoo
{
    namespace parser
    {
        class Module
        {

        public:
            Module(ast::Unit *unit,
                   std::list<BaseError *> errors);

        private:
            ast::Unit *_unit;
            std::list<BaseError *> _errors;

        public:
            const ast::Unit *GetUnit();
            bool Success();
            const std::list<BaseError *> &GetErrors() const;

            virtual ~Module();
        };
    } // namespace parser
} // namespace hoo

#endif
