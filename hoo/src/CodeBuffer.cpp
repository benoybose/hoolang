#include "CodeBuffer.hh"
#include "HooConfig.hh"

#include <vector>
#include <cstdint>
#include <cstddef>
#include <cstring>

#ifdef HOO_WIN64
#include <windows.h>
#endif

#ifdef HOO_LINUX64

#include <sys/mman.h>
#include <unistd.h>

#endif

namespace hoo {
    namespace jit {
        CodeBuffer::CodeBuffer() :
                _buffer(nullptr), _size(0),
                _page_count(0), _position(-1),
                _locked(false) {
        }

        CodeBuffer::~CodeBuffer() {
            if (nullptr != this->_buffer) {
                this->Free();
                this->_size = 0;
                this->_position = -1;
                this->_page_count = 0;
            }
        }

        void CodeBuffer::Allocate(size_t size) {
            auto page_size = this->GetPageSize();
            this->_page_count = size / page_size;

            if (0 < (size % page_size)) {
                this->_page_count++;
            }

            this->_size = this->_page_count * page_size;
            this->_position = -1;

#ifdef HOO_WIN64
            this->_buffer = reinterpret_cast<uint8_t *>(
                    VirtualAlloc(NULL, this->_size,
                                 MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)
            );
#endif
#ifdef HOO_LINUX64
            this->_buffer = reinterpret_cast<uint8_t *>(
                    mmap(0, this->_size,
                         PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE,
                         -1, 0)
            );
#endif
            if (nullptr != this->_buffer) {
                std::memset(this->_buffer, 0, this->_size);
            }
        }

        size_t CodeBuffer::GetPageSize() {
#ifdef HOO_WIN64
            SYSTEM_INFO info;
            GetSystemInfo(&info);
            return (size_t) info.dwPageSize;
#endif
#ifdef HOO_LINUX64
            return (size_t) sysconf(_SC_PAGE_SIZE);
#endif
        }

        CodeBuffer::CodeLocation CodeBuffer::Write(std::vector<uint8_t> code) {
            const auto starting_position = this->_position + 1;
            const size_t existing_size = starting_position;
            const size_t modified_size = existing_size + code.size();
            const auto data = code.data();


            if ((0 == this->_size) &&
                (nullptr == this->_buffer) &&
                (-1 == this->_position) &&
                (0 == this->_page_count)) {
                this->Allocate(code.size());
                std::memcpy(this->_buffer, data, code.size());
            } else if (modified_size < this->_size) {
                std::memcpy(&this->_buffer[this->_position + 1], data, code.size());
            } else {
                uint8_t *buffer = new uint8_t[modified_size]{0};
                if ((0 < existing_size) || (0 != this->_buffer)) {
                    std::memcpy(buffer, this->_buffer, existing_size);
                }

                std::memcpy(&buffer[this->_position + 1], data, code.size());

                if (0 != this->_buffer) {
                    this->Free();
                }

                this->Allocate(modified_size);
                std::memcpy(this->_buffer, buffer, modified_size);
                delete buffer;
            }

            CodeLocation location(starting_position, code.size(), this->_buffer + starting_position);
            this->_position = modified_size - 1;
            return location;
        }

        void CodeBuffer::Free() {
            if (nullptr != this->_buffer) {
#ifdef HOO_WIN64
                VirtualFree(this->_buffer, this->_size, MEM_RELEASE);
#endif
#ifdef HOO_LINUX64
                munmap(this->_buffer, this->_size);
#endif
                this->_buffer = nullptr;
                this->_position = -1;
                this->_page_count = 0;
                this->_size = 0;
            }
        }

        const uint8_t *CodeBuffer::GetBuffer() const {
            return this->_buffer;
        }

        bool CodeBuffer::IsLocked() const {
            return _locked;
        }

        bool CodeBuffer::Lock() {
#ifdef HOO_WIN64
            DWORD old = 0;
            return VirtualProtect(this->_buffer, this->_size, PAGE_EXECUTE_READ, &old);
#endif
#ifdef HOO_LINUX64
			return (0 == mprotect(this->_buffer, this->_size, PROT_READ | PROT_EXEC));
#endif
        }

        size_t CodeBuffer::GetSize() const {
            return _size;
        }

        size_t CodeBuffer::GetPageCount() const {
            return _page_count;
        }

        size_t CodeBuffer::GetPosition() const {
            return _position;
        }

        CodeBuffer::CodeLocation::CodeLocation() :
                _start(-1), _count(0), _address(nullptr) {

        }

        CodeBuffer::CodeLocation::CodeLocation(size_t start, size_t count, uint8_t *address) :
                _start(start), _count(count), _address(address) {
        }

        CodeBuffer::CodeLocation::CodeLocation(const CodeBuffer::CodeLocation &code_location) :
                _start(code_location._start), _count(code_location._count), _address(code_location._address) {

        }

        CodeBuffer::CodeLocation &CodeBuffer::CodeLocation::operator=(const CodeBuffer::CodeLocation &code_location) {
            _start = code_location._start;
            _count = code_location._count;
            _address = code_location._address;
            return *(this);
        }

        const size_t CodeBuffer::CodeLocation::GetStart() const {
            return _start;
        }

        const size_t CodeBuffer::CodeLocation::GetCount() const {
            return _count;
        }

        const uint8_t *CodeBuffer::CodeLocation::GetAddress() const {
            return this->_address;
        }
    }
}