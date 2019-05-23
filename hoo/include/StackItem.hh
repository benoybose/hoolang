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

#include <string>

#ifndef HC_STACKITEM_H
#define HC_STACKITEM_H

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

#endif

