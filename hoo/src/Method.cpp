#include "Method.hh"

namespace hoo {
    namespace jit {
        Method::Method(const std::string &methodName, Module* module) :
                _module(_module),
                _name(methodName) {
        }

        Module* Method::GetModule() const {
            return this->_module;
        }

        const std::string &Method::GetName() const {
            return this->_name;
        }
    }
}