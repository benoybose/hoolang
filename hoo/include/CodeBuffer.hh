/*
 * Copyright 2019 Benoy Bose
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
