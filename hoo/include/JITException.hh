//
// Created by COMP on 27-07-2018.
//

#ifndef PROJECT_JITEXCEPTION_HH
#define PROJECT_JITEXCEPTION_HH

#include <exception>
#include <string>

namespace hoo {
    namespace jit {
        extern const int HOO_ERROR_DUPLICATE_MODULE_NAME;

        class JITException : public std::exception {
        public:
            JITException(int errorCode);

            virtual ~JITException() throw();

        public:
            std::string GetMessage();

            int GetErrorCode();

        private:
            int _errorCode;
            std::string _message;
        };
    }
}

#endif //PROJECT_JITEXCEPTION_HH
