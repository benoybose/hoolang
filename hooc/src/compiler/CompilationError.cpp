//
// Created by benoy on 12/21/2018.
//

#include "CompilationError.hh"

namespace hooc {
    namespace compiler {
        CompilationError::CompilationError(size_t line_number, size_t character_position, const std::string &message) :
                _line_number(line_number),
                _character_position(character_position),
                _message(message) {
        }

        int CompilationError::GetLineNumber() const {
            return this->_line_number;
        }

        int CompilationError::GetCharacterPosition() const {
            return this->_character_position;
        }

        const std::string &CompilationError::GetMessage() const {
            return this->_message;
        }
    }
}
