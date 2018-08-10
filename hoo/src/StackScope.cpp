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