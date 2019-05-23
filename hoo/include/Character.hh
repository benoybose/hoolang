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

#ifndef CHARACTERCLASS_HH
#define CHARACTERCLASS_HH

#include <vector>
#include <cstdint>
#include <string>

namespace hoo {
    extern const std::string TYPENAME_CHARACTER;
    typedef std::vector<uint8_t> ByteVector;
    class Character: protected ByteVector{
    public:
        Character();
        Character(const Character& value);

    public:
        static Character MakeCharacter(uint8_t b1, uint8_t b2 = 0, uint8_t b3 = 0, uint8_t b4 = 0);

    public:
        size_t GetSize() const;
        uint8_t at(int index) const;
    };


}

#endif // CHARACTERCLASS_HH
