#include "JITException.hh"

namespace hoo {
    namespace jit {
        const int HOO_ERROR_DUPLICATE_MODULE_NAME = 3000;

        JITException::JITException(int errorCode) : std::exception() {
            this->_errorCode = errorCode;
        }

        JITException::~JITException() {}

        std::string JITException::GetMessage() {
            switch (this->_errorCode) {
                case HOO_ERROR_DUPLICATE_MODULE_NAME:
                    return std::string("Duplicate module.");
            }
        }

        int JITException::GetErrorCode() {
            return this->_errorCode;
        }
    }
}