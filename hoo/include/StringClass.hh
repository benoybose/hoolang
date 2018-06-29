//
// Created by COMP on 27-06-2018.
//

#ifndef PROJECT_STRINGCLASS_HH
#define PROJECT_STRINGCLASS_HH

#include "Object.hh"

#include <string>

namespace hoo {
    extern const std::string TYPENAME_STRING;

    class StringClass: public Object {
    private:
        std::string _value;

    public:
        StringClass();
        explicit StringClass(const std::string& text);
        explicit StringClass(const char* text);

    public:
        const std::string& GetValue() const;
    };
}

#endif //PROJECT_STRINGCLASS_HH
