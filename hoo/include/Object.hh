//
// Created by COMP on 27-06-2018.
//

#ifndef PROJECT_OBJECT_HH
#define PROJECT_OBJECT_HH

#include <string>
#include <memory>

namespace hoo {
    class Object {
    private:
        std::string _type_name;

    public:
        explicit Object(const std::string &type_name);

    public:
        const std::string &GetTypeName() const;
    };

    typedef std::shared_ptr<Object> ObjectPtr;
}

#endif //PROJECT_OBJECT_HH
