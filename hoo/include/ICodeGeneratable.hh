//
// Created by COMP on 21-08-2018.
//

#ifndef PROJECT_ICODEGENERATABLE_HH
#define PROJECT_ICODEGENERATABLE_HH

#include <vector>

namespace hoo {
    namespace jit {
        class ICodeGeneratable {
        public:
            virtual std::vector<unsigned char> Generate() = 0;
        };
    }
}

#endif //PROJECT_ICODEGENERATABLE_HH
