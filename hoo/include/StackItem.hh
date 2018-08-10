#ifndef PROJECT_STACKCONTENT_HH
#define PROJECT_STACKCONTENT_HH

#include <string>

namespace hoo {
    namespace jit {
        typedef enum {
            STACKITEM_PARAM,
            STACKITEM_LOCALVAR
        } StackItemType;

        class StackScope;

        class StackItem {
            friend class StackScope;

        private:
            StackItemType _itemType;
            std::string _type;
            std::string _name;
            size_t _ordinal;
            StackScope *_scope;

        protected:
            StackItem(StackItemType itemType,
                      const std::string &type,
                      const std::string &name,
                      StackScope *scope);

        public:

            const std::string &GetType() const;

            const std::string &GetName() const;

            size_t GetOrdinal() const;

            StackScope *GetScope() const;

            StackItemType GetItemType() const;

        protected:
            void SetOrdinal(size_t ordinal);

        };
    }
}

#endif //PROJECT_STACKCONTENT_HH

