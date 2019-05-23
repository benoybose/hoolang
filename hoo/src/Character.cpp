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

#include "Character.hh"

namespace hoo {
    const std::string TYPENAME_CHARACTER = "hoo.character";

    Character::Character(): ByteVector({}) {
    }

    Character::Character(const Character &value): ByteVector({}) {
        for(auto iterator = value.begin(); iterator != value.end(); ++iterator) {
            ByteVector::insert(this->end(), *iterator);
        }
    }

    Character Character::MakeCharacter(uint8_t byte0,
                                       uint8_t byte1,
                                       uint8_t byte2,
                                       uint8_t byte3) {
        Character character;
        if(0 != byte0) {
            character.insert(character.end(), byte0);
            if(0 != byte1) {
                character.insert(character.end(), byte1);
                if(0 != byte2) {
                    character.insert(character.end(), byte2);
                    if(0 != byte3) {
                        character.insert(character.end(), byte3);
                    }
                }
            }
        }
        return character;
    }

    size_t Character::GetSize() const {
        return this->size();
    }

    uint8_t Character::at(int index) const {
        return ByteVector::at(index);
    }
}