#include <hoo/emitter/EmitterException.hh>

#include <string>
#include <stdexcept>

namespace hoo
{
    namespace emitter
    {
        EmitterException::EmitterException(const std::string &message, int error_no,
        std::shared_ptr<Position> start,
        std::shared_ptr<Position> end) :
        std::runtime_error(message),
        _message(message),
        _error_no(error_no),
        _start(start),
        _end(end)
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

        const std::shared_ptr<Position> EmitterException::GetStart() const
        {
            return this->_start;
        }
        
        const std::shared_ptr<Position> EmitterException::GetEnd() const
        {
            return this->_end;
        }
    }
}