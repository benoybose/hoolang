//
// Created by benoy on 12/21/2018.
//

#ifndef COMPILATIONERROR_HH
#define COMPILATIONERROR_HH

#include <string>
#include <list>

namespace hooc {
    class CompilationError {
    private:
        size_t _line_number;
        size_t _character_position;
        std::string _message;

    public:
        CompilationError(size_t line_number, size_t character_position,
                const std::string &message);

    public:
        int GetLineNumber() const;
        int GetColumnnNumber() const;
        const std::string &GetMessage() const;
    };
}



#endif //PROJECT_COMPILATIONERROR_HH
