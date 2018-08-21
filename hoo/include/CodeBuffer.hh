#ifndef PROJECT_CODEBUFFER_HH
#define PROJECT_CODEBUFFER_HH

#include <vector>

namespace hoo {
    namespace jit {
        class CodeBuffer {
        public:
            CodeBuffer(std::vector<unsigned char> code);

        public:
            const unsigned char *GetBuffer() const;

        private:
            unsigned char *_buffer;
            size_t _size;
        };
    }
}

#endif //PROJECT_CODEBUFFER_HH
