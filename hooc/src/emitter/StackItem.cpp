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

#include <utility>

#include "StackItem.hh"

namespace hooc {
    namespace emitter {
        StackItem::StackItem(string name, StackItemType stack_item_type,
                            int64_t position,
                            const TypeSpecification *type_specification)
                : _name(std::move(name)),
                  _stack_item_type(stack_item_type),
                  _position(position),
                  _type_specification(type_specification) {
        }

        const string &StackItem::GetName() const {
            return _name;
        }

        int64_t StackItem::GetPosition() const {
            return _position;
        }

        const TypeSpecification *StackItem::GetTypeSpecification() const {
            return _type_specification;
        }

        const StackItemType StackItem::GetStakcItemType() const {
            return _stack_item_type;
        }

        bool StackItemComparer::operator()(const StackItem &a, const StackItem &b) const {
            auto name_a = a.GetName();
            auto name_b = b.GetName();
            if(name_a != name_b) {
                return true;
            }
            auto pos_a = a.GetPosition();
            auto pos_b = b.GetPosition();
            if(pos_a != pos_b) {
                return true;
            }
            return false;
        }

        const StackItem& GetStackItem(const StackItemSet& items, size_t index) {
            auto iterator = items.begin();
            auto item_index = 0;
            while(item_index < index) {
                item_index ++;
                iterator ++;
            }

            const StackItem& item = *(iterator);
            return item;
        }
    }
}
