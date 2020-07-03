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

#ifndef HOOLANG_BASEERROR_HH
#define HOOLANG_BASEERROR_HH

#include <string>

namespace hooc {
    namespace compiler {
        typedef enum {
            ERROR_HOOC_SYNTAX,
            ERROR_HOOC_PARSE,
            ERROR_HOOC_SEMANTIC
        } ErrorType;

        typedef enum {
            ERROR_CODE_WRONG_SYNTAX = 1024,
            ERROR_CODE_FAILED_PARSING = 1025,
            ERROR_CODE_BAD_CAST_PARSING = 1026
        } ErrorCode;

        class BaseError {
        private:
            ErrorType _type;
            ErrorCode _code;
            std::string _message;

        public:
            BaseError(ErrorType type, ErrorCode code, const std::string& message);

            ErrorType GetType() const;

            ErrorCode GetCode() const;

            const std::string &GetMessage() const;
        };
    }
}



#endif //HOOLANG_BASEERROR_HH
