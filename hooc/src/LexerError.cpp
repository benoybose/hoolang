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

#include "LexerError.hh"


namespace hooc {
    const std::string ERROR_LEXER_NOERROR = "";
    const std::string ERROR_LEXER_UNKNOWN = "Unknown error.";

    LexerError::LexerError(): _error(0) {}

    LexerError::LexerError(int error): _error(error) {
    }

    LexerError::LexerError(const LexerError &error): _error(error._error) {
    }

    LexerError &LexerError::operator=(const LexerError &error) {
        this->_error = error._error;
        return *(this);
    }

    const int LexerError::GetErrorCode() const {
        return this->_error;
    }

    const std::string &LexerError::GetMessage() const {
        switch (this->_error) {
            case 0: return ERROR_LEXER_NOERROR;
            default: return ERROR_LEXER_UNKNOWN;
        }
    }

}
