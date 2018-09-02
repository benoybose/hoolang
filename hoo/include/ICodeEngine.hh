//
// Created by COMP on 31-08-2018.
//

#ifndef ICODEENGINE_HH
#define ICODEENGINE_HH

#include "Value.hh"

#include <string>
#include <vector>

namespace hoo {
    namespace jit {
        namespace code {
            class ICodeEngine {
            public:
                virtual std::string GetId() = 0;
                virtual std::vector<uint8_t> EmitFunctionHeader(size_t param_count) = 0;
                virtual std::vector<uint8_t> EmitFunctionFooter(ValuePtr value) = 0;
                virtual std::vector<uint8_t> EmitFunctionFooter() = 0;
            };
        }
    }
}

#endif //PROJECT_ICODEENGINE_HH
