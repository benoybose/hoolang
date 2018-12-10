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

#include <Token.hh>

#include "Token.hh"

namespace hooc {
    Token::Token(int token_id, const std::string &text, size_t position, size_t line_number, size_t column_number)
            : _token_id(token_id), _text(text), _position(position), _line_number(line_number),
              _column_number(column_number) {

    }

    Token::Token(): _token_id(-1),
        _text(""),
        _position(0),
        _line_number(0),
        _column_number(0) {
    }

    Token::Token(const Token &token): _token_id(token._token_id),
    _text(token._text),
    _position(token._position),
    _column_number(token._column_number),
    _line_number(token._line_number){

    }

    Token &Token::operator=(const Token &token) {
        this->_token_id = token._token_id;
        this->_text = token._text;
        this->_position = token._position;
        this->_line_number = token._line_number;
        this->_column_number = token._column_number;
        return *this;
    }

    int Token::GetTokenId() const {
        return _token_id;
    }

    const std::string &Token::GetText() const {
        return _text;
    }

    size_t Token::GetPosition() const {
        return _position;
    }

    size_t Token::GetLineNumber() const {
        return _line_number;
    }

    size_t Token::GetColumnNumber() const {
        return _column_number;
    }
}
