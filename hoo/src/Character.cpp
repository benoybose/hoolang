#include "CharacterClass.hh"

namespace hoo {
    const std::string TYPENAME_CHARACTER = "hoo.character";

    CharacterClass::CharacterClass(char byte0, unsigned char byte1,
                                   unsigned char byte2, unsigned char byte3) :
            Object(TYPENAME_CHARACTER), _size(4) {
        _bytes[0] = (unsigned) byte0;
        _bytes[1] = byte1;
        _bytes[2] = byte2;
        _bytes[3] = byte3;
        _size = 0;

        for (int index = 0; index < sizeof(_bytes); index++) {
            if (0 == _bytes[index]) break;
            _size++;
        }
    }

    unsigned char CharacterClass::GetSize() const {
        return this->_size;
    }

    unsigned char CharacterClass::GetByte0() const {
        return this->_bytes[0];
    }

    unsigned char CharacterClass::GetByte1() const {
        return this->_bytes[1];
    }

    unsigned char CharacterClass::GetByte2() const {
        return this->_bytes[2];
    }

    unsigned char CharacterClass::GetByte3() const {
        return this->_bytes[3];
    }
}