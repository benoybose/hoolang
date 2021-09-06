/*
 * Copyright 2021 Benoy Bose
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

#ifndef EMITTER_EXCEPTION_HH
#define EMITTER_EXCEPTION_HH

#define EMITTER_ERR_01 1
#define EMITTER_ERR_01MSG "emitter: Unit item not supported"

#define EMITTER_ERR_02 2
#define EMITTER_ERR_02MSG "emitter: Definition not supported"

#define EMITTER_ERR_03 3
#define EMITTER_ERR_03MSG "emitter: Class body item not supported"

#include <exception>
#include <string>

namespace hoo
{
    namespace emitter
    {
        class EmitterException : virtual std::exception
        {
        private:
            std::string _message;
            int _error_no;

        public:
            EmitterException(const std::string &message, int error_no);

        public:
            virtual ~EmitterException() throw() {}

        public:
            const std::string &GetMessage();
            const int GetErrorNo();

        public:
            virtual const char *what() const throw();
        };
    }
}
#endif
