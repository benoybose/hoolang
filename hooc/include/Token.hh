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

#ifndef PROJECT_TOKEN_HH
#define PROJECT_TOKEN_HH

#include <string>

namespace hooc {
    class Token {
    private:
        int _token_id;
        std::string _text;
        size_t _position;
        size_t _line_number;
        size_t _column_number;

    public:
        Token();
        Token(int token_id,
                const std::string &text,
                size_t position,
                size_t line_number,
                size_t column_number);
        Token(const Token& token);

    public:
        Token& operator = (const Token& token);

    public:
        int GetTokenId() const;

        const std::string &GetText() const;

        size_t GetPosition() const;

        size_t GetLineNumber() const;

        size_t GetColumnNumber() const;
    };
}


#endif //PROJECT_TOKEN_HH
