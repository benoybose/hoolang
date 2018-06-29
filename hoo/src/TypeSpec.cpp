#include "TypeSpec.hh"

namespace hoo {
    namespace jit {
        TypeSpec::TypeSpec(const std::string &_typeName,
                           size_t _size,
                           bool _is_value) :
                _typeName(_typeName),
                _size(_size),
                _is_value(_is_value) {
        }

        const std::string &TypeSpec::GetTypeName() const {
            return this->_typeName;
        }

        std::size_t TypeSpec::GetSize() {
            return this->_size;
        }

        bool TypeSpec::IsValueType() {
            return this->_is_value;
        }
    }
}