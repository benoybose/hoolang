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
            class CodeLocation {
            private:
                size_t _start;
                size_t _count;
                uint8_t *_address;

            public:
                CodeLocation();

                CodeLocation(size_t start, size_t count, uint8_t *address);

                CodeLocation(const CodeLocation &code_location);

            public:
                CodeLocation &operator=(const CodeLocation &code_location);

            public:
                const size_t GetStart() const;

                const size_t GetCount() const;

                const uint8_t *GetAddress() const;


            };

        public:
            CodeBuffer();

            virtual ~CodeBuffer();

        public:
            CodeLocation Write(std::vector<uint8_t> code);

            const uint8_t *GetBuffer() const;

            bool Lock();

            size_t GetSize() const;

            size_t GetPageCount() const;

            size_t GetPosition() const;

            bool IsLocked() const;


        private:
            uint8_t *_buffer;
            size_t _size;
            size_t _page_count;
            size_t _position;
            bool _locked;

        private:
            void Allocate(size_t size);

            void Free();

            size_t GetPageSize();
        };
    }
}

#endif //PROJECT_CODEBUFFER_HH
