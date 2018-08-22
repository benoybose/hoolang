#include "CodeBuffer.hh"
#include "HooConfig.hh"

#include <vector>
#include <cstdint>

#ifdef HOO_WIN64
#include <windows.h>
#endif

//#ifdef HOO_LINUX64
#include <sys/mman.h>
#include <unistd.h>
//#endif

namespace hoo {
    namespace jit {
        CodeBuffer::CodeBuffer():
                _buffer(nullptr), _size(0),
                _page_count(0), _position(-1){
        }

        void CodeBuffer::Allocate(size_t size) {
            auto page_size = this->GetPageSize();
            this->_page_count = size / page_size;

            if(0 > size % page_size) {
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
            this->_buffer = reinterpret_cast<uint8_t*>(
                    mmap(0, this->_size,
                         PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE,
                         -1, 0)
            );
#endif
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
    }
}