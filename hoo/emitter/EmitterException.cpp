#include <hoo/emitter/EmitterException.hh>

#include <string>

namespace hoo
{
    namespace emitter
    {
        EmitterException::EmitterException(const std::string &message, int error_no) : 
            _message(message),
            _error_no(error_no)
        {
        }

        const std::string& EmitterException::GetMessage()
        {
            return this->_message;
        }

        const int EmitterException::GetErrorNo()
        {
            return this->_error_no;
        }

        const char* EmitterException::what() const throw()
        {
            return this->_message.c_str();
        }
    }
}