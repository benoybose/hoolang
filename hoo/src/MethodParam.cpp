#include "MethodParam.hh"

namespace hoo {
    namespace jit {
        MethodParam::MethodParam(const std::string &type,
                                 const std::string &name,
                                 size_t ordinal) :
                _name(name), _type(type), _ordinal(ordinal) {
        }

        const std::string &MethodParam::GetName() const {
            return _name;
        }

        const std::string &MethodParam::GetType() const {
            return _type;
        }

        size_t MethodParam::GetOrdinal() const {
            return _ordinal;
        }
    }
}