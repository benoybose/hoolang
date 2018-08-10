#include "MethodParam.hh"

namespace hoo {
    namespace jit {
        MethodParam::MethodParam(const std::string &type,
                                 const std::string &name) :
                StackItem(STACKITEM_PARAM,
                          type,
                          name,
                          nullptr) {

        }
    }
}