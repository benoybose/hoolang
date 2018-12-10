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

#include "TokenDescriptor.hh"

namespace hooc {
    TokenDescriptor::TokenDescriptor(): _token_id(-1) {
    }

    TokenDescriptor::TokenDescriptor(int token_id, boost::regex pattern):
        _token_id(token_id),
        _pattern(pattern) {
    }

    int TokenDescriptor::GetTokenId() const {
        return this->_token_id;
    }

    const boost::regex& TokenDescriptor::GetPattern() const {
        return this->_pattern;
    }

    TokenDescriptor::TokenDescriptor(const TokenDescriptor &descriptor):
    _token_id(descriptor._token_id),
    _pattern(descriptor._pattern) {
    }

    TokenDescriptor &TokenDescriptor::operator=(const TokenDescriptor &descriptor) {
        this->_token_id = descriptor._token_id;
        this->_pattern = descriptor._pattern;
        return *(this);
    }

    bool TokenDescriptor::operator==(const hooc::TokenDescriptor &rhs) const {
        return _token_id == rhs._token_id &&
               _pattern == rhs._pattern;
    }

    bool TokenDescriptor::operator!=(const hooc::TokenDescriptor &rhs) const {
        return !(rhs == *this);
    }
}
