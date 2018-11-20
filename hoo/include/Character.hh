#ifndef CHARACTERCLASS_HH
#define CHARACTERCLASS_HH

#include <vector>
#include <cstdint>
#include <string>

namespace hoo {
    extern const std::string TYPENAME_CHARACTER;
    typedef std::vector<uint8_t> ByteVector;
    class Character: public std::vector<uint8_t>{
    public:
        Character();
        Character(const Character& value);
        Character(const std::vector<uint8_t> value);

    public:
        static Character MakeCharacter(uint8_t b1);
        static Character MakeCharacter(uint8_t b1, uint8_t b2);
        static Character MakeCharacter(uint8_t b1, uint8_t b2, uint8_t b3);
        static Character MakeCharacter(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
    };


}

#endif // CHARACTERCLASS_HH
