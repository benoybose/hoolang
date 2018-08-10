#ifndef PROJECT_STACKSCOPE_HH
#define PROJECT_STACKSCOPE_HH

#include "StackItem.hh"

#include <list>

namespace hoo {
    namespace jit {
        class StackScope {
        private:
            StackScope* _parent;
            std::list<StackItem*> _items;

        protected:
            StackScope(StackScope* parent);

        protected:
            size_t AddItem(StackItem *item);
            bool HasItem(const std::string& name);

        public:
            StackScope *GetParent() const;
            const std::list<StackItem *> &GetItems() const;

        };
    }
}

#endif //PROJECT_STACKSCOPE_HH
