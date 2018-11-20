#include "Character.hh"

namespace hoo {
    const std::string TYPENAME_CHARACTER = "hoo.character";

    Character::Character() {
    }

    Character::Character(const Character &value):
    }

    Character::Character(const std::vector<uint8_t> value):
            std::vector(*this) {
    }

    Character Character::MakeCharacter(uint8_t b1) {
        return Character({ b1 });
    }

    Character Character::MakeCharacter(uint8_t b1,
                                       uint8_t b2) {
        return Character({ b1, b2 });
    }

    Character Character::MakeCharacter(uint8_t b1,
                                       uint8_t b2,
                                       uint8_t b3) {
        return Character({ b1, b2, b3 });
    }

    Character Character::MakeCharacter(uint8_t b1,
                                       uint8_t b2,
                                       uint8_t b3,
                                       uint8_t b4) {
        return Character({ b1, b2, b3, b4 });
    }
}