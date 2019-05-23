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

#include "StackScope.hh"
#include "StackItem.hh"
#include "JITException.hh"

namespace hoo {
    namespace jit {
        StackScope::StackScope(hoo::jit::StackScope *parent):
                _parent(parent) {
        }

        size_t StackScope::AddItem(StackItem *item) {
            if(this->HasItem(item->GetName())) {
                throw JITException(HOO_ERROR_DUPLICATE_ITEM_NAME);
            }
            item->SetOrdinal(this->_items.size());
            this->_items.push_back(item);
            return 0;
        }

        StackScope *StackScope::GetParent() const {
            return this->_parent;
        }

        const std::list<StackItem *> &StackScope::GetItems() const {
            return this->_items;
        }

        bool StackScope::HasItem(const std::string &name) {
            for(auto index = this->_items.begin();
                    index != this->_items.end();
                    ++index) {
                auto item = *(index);
                if(0 == item->GetName().compare(name)) {
                    return true;
                }
            }
            return false;
        }
    }
}