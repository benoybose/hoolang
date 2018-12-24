//
// Created by benoybose on 23/12/18.
//

#ifndef HOOC_CLASS_HH
#define HOOC_CLASS_HH

#include <string>
#include <memory>

namespace hooc {
    class Class {
    private:
        std::string _name;

    public:
        Class();
        Class(std::string name);

    public:
        const std::string& GetName() const;
    };

    typedef std::shared_ptr<Class> ClassRef;
}


#endif //PROJECT_CLASS_HH
