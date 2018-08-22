#ifndef PROJECT_ICODEGENERATABLE_HH
#define PROJECT_ICODEGENERATABLE_HH

#include <vector>
#include <cstdint>

namespace hoo {
    namespace jit {
        class ICodeGeneratable {
        public:
            virtual std::vector<uint8_t> Generate() = 0;
        };
    }
}

#endif //PROJECT_ICODEGENERATABLE_HH
