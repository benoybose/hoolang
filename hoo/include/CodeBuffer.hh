#ifndef PROJECT_CODEBUFFER_HH
#define PROJECT_CODEBUFFER_HH

#include <vector>
#include <cstdint>
#include <cstddef>
#include <cstdbool>

namespace hoo {
    namespace jit {
        class CodeBuffer {
        public:
            CodeBuffer();

            virtual ~CodeBuffer();

        public:
            size_t Write(std::vector<uint8_t> code);

            const uint8_t *GetBuffer() const;

            bool Lock();

            size_t GetSize() const;

            size_t GetPageCount() const;

            long GetPosition() const;

            bool IsLocked() const;


        private:
            uint8_t *_buffer;
            size_t _size;
            size_t _page_count;
            long int _position;
            bool _locked;

        private:
            void Allocate(size_t size);

            void Free();

            size_t GetPageSize();
        };
    }
}

#endif //PROJECT_CODEBUFFER_HH
