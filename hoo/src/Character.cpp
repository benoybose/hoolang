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