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

#ifndef HOOLANG_STACKITEM_HH
#define HOOLANG_STACKITEM_HH

#include <ast/TypeSpecification.hh>
#include <string>
#include <set>
#include <cstdint>

using namespace std;
using namespace hooc::ast;

namespace hooc {
    namespace emitter {
        typedef enum {
            STACK_ITEM_ARGUMENT = 0,
            STACK_ITEM_VARIABLE = 1
        } StackItemType;

        class StackItem {
        private:
            string _name;
            StackItemType _stack_item_type;
            int64_t _position;
            const TypeSpecification *_type_specification;

        public:
            StackItem(string name, StackItemType stack_item_type,
                    int64_t position,
                    const TypeSpecification *type_specification);

            const string &GetName() const;

            int64_t GetPosition() const;

            const TypeSpecification *GetTypeSpecification() const;

            const StackItemType GetStakcItemType() const;
        };

        class StackItemComparer {
        public:
            bool operator()(const StackItem &a, const StackItem &b) const;
        };

        typedef std::set<StackItem, StackItemComparer> StackItemSet;

        extern const StackItem& GetStackItem(const StackItemSet& items, size_t index);
    }
}

#endif //HOOLANG_STACKITEM_HH
