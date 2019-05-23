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

#ifndef PROJECT_JITEXCEPTION_HH
#define PROJECT_JITEXCEPTION_HH

#include <exception>
#include <string>

namespace hoo {
    namespace jit {
        extern const int HOO_ERROR_DUPLICATE_MODULE_NAME;
        extern const int HOO_ERROR_DUPLICATE_ITEM_NAME;

        class JITException : public std::exception {
        public:
            JITException(int errorCode);

            virtual ~JITException() throw();

        public:
            std::string GetMessage();

            int GetErrorCode();

        private:
            int _errorCode;
            std::string _message;
        };
    }
}

#endif //PROJECT_JITEXCEPTION_HH
