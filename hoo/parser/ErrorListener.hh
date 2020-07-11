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

#ifndef HC_COMPILATIONERRORLISTENER_HH
#define HC_COMPILATIONERRORLISTENER_HH

#include "antlr4-runtime.h"
#include <hoo/parser/BaseError.hh>

#include <list>

using namespace antlr4;

namespace hoo {
    namespace parser {
        class ErrorListener: public BaseErrorListener {

        public:
            ErrorListener();

        private:
            std::list<BaseError*> _errors;

        public:
            void syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line, size_t charPositionInLine,
                             const std::string &msg, std::exception_ptr e) override;
            void Add(BaseError* error);

        public:
            const std::list<BaseError*>& GetErrors() const;

        public:
            virtual ~ErrorListener();

        };
    }
}




#endif //HC_COMPILATIONERRORLISTENER_HH
