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

#ifndef PROJECT_LEXER_H
#define PROJECT_LEXER_H

#include "TokenDescriptor.hh"
#include "LexerError.hh"
#include "Token.hh"

#include <sstream>
#include <cstddef>
#include <string>

namespace hooc {
    class Lexer {
    private:
        std::string _text;
        std::istringstream &_stream;
        size_t _position;
        size_t _line_number;
        size_t _column_number;
        std::list<hooc::TokenDescriptor> _descriptors;


    public:
        Lexer(std::istringstream &stream);

    public:
        void Add(int token_id, std::string pattern);
        bool Tokenize(LexerError &error, Token &token);

    public:
        const std::list<hooc::TokenDescriptor>& GetDescriptors() const;

    };
}

#endif //PROJECT_LEXER_H
