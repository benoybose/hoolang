//
// Created by COMP on 28-06-2018.
//

#ifndef PROJECT_CHARACTERCLASS_HH
#define PROJECT_CHARACTERCLASS_HH

#include "Object.hh"

namespace hoo {
    extern const std::string TYPENAME_CHARACTER; // = "hoo.character"
    class CharacterClass: public Object {
    private:
        unsigned char _size;
        unsigned char _bytes[4];
    public:
        CharacterClass(char byte0,
                       unsigned char byte1 = 0,
                       unsigned char byte2 = 0,
                       unsigned char byte3 = 0);

    public:
        unsigned char GetSize() const;
        unsigned char GetByte0() const;
        unsigned char GetByte1() const;
        unsigned char GetByte2() const;
        unsigned char GetByte3() const;
    };
}

#endif //PROJECT_CHARACTERCLASS_HH
