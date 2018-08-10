#include "StackItem.hh"

namespace hoo {
    namespace jit {
        StackItem::StackItem(StackItemType itemType, const std::string &type, const std::string &name, StackScope *scope)
                : _itemType(itemType),
                  _type(type),
                  _name(name),
                  _ordinal(0),
                  _scope(scope) {

        }

        const std::string &StackItem::GetType() const {
            return this->_type;
        }

        const std::string &StackItem::GetName() const {
            return this->_name;
        }

        size_t StackItem::GetOrdinal() const {
            return this->_ordinal;
        }

        StackScope *StackItem::GetScope() const {
            return this->_scope;
        }

        StackItemType StackItem::GetItemType() const {
            return this->_itemType;
        }

        void StackItem::SetOrdinal(size_t ordinal) {
            this->_ordinal = ordinal;
        }
    }
}