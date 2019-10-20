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

#include "Code.hh"

namespace hooc {
    namespace emitter {

        Code::Code(CodeType type, const std::string &name) :
                _type(type),
                _name(name) {

        }

        CodeType Code::GetType() const {
            return _type;
        }

        const std::string &Code::GetName() const {
            return _name;
        }

        const uint8_t *Code::GetBytes() const {
            return this->_buffer.data();
        }

        size_t Code::GetSize() const {
            return this->_buffer.size();
        }

        size_t Code::Add(uint8_t byte) {
            this->_buffer.push_back(byte);
            return this->_buffer.size();
        }
    }
}
