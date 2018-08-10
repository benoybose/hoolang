//
// Created by COMP on 10-08-2018.
//

#ifndef PROJECT_METHODPARAM_HH
#define PROJECT_METHODPARAM_HH

#include <string>

#include "StackItem.hh"

namespace hoo {
    namespace jit {
        class Method;

        class MethodParam: public StackItem {
            friend class Method;

        protected:
            MethodParam(const std::string &type, const std::string &name);
        };
    }
}

#endif //PROJECT_METHODPARAM_HH
