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

#ifndef HC_UNIT_H
#define HC_UNIT_H

#include <hoo/ast/UnitItem.hh>

#include <list>
#include <memory>
#include <string>

namespace hoo
{
    namespace ast
    {
        class Unit
        {
        private:
            std::list<std::shared_ptr<UnitItem>> _items;
            std::string _name;

        public:
        Unit(const std::string &name);
        Unit(std::list<std::shared_ptr<UnitItem>> items, const std::string &name);

        public:
        std::list<std::shared_ptr<UnitItem>> GetItems();

        public:
        const std::string& GetName();

        public:
            virtual ~Unit();
        };
    } // namespace ast
} // namespace hoo

#endif //HC_UNIT_H
