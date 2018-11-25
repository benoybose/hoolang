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
