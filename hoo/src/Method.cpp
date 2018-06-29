#include "Method.hh"

namespace hoo {
    namespace jit {
        Method::Method(Module *_module, const std::string &_name) :
                _module(_module),
                _name(_name) {

        }

        Module *Method::GetModule() const {
            return this->_module;
        }

        const std::string &Method::GetName() const {
            return this->_name;
        }
    }
}