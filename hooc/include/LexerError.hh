/*
 * Copyright 2018 Benoy Bose
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

#ifndef PROJECT_LEXERERROR_HH
#define PROJECT_LEXERERROR_HH

#include <string>

namespace hooc {
    extern const std::string ERROR_LEXER_NOERROR; // = "";
    extern const std::string ERROR_LEXER_UNKNOWN; // = "Unknown error.";

    class LexerError {
    private:
        int _error;

    public:
        LexerError();
        LexerError(int error);
        LexerError(const LexerError& error);

    public:
        LexerError &operator = (const LexerError& error);

    public:
        const std::string& GetMessage() const;
        const int GetErrorCode() const;
    };
}


#endif //PROJECT_LEXERERROR_HH
