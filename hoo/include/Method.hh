//
// Created by COMP on 29-06-2018.
//

#ifndef PROJECT_METHOD_HH
#define PROJECT_METHOD_HH

#include <string>
#include <memory>
#include <list>

namespace hoo {
    namespace jit {
        class Module;


        class Method {
            friend class Module;

        private:
            Module* _module;
            std::string _name;

        private:
            Method(const std::string &methodName, Module* module);

        public:
            Module* GetModule() const;
            const std::string &GetName() const;
        };

        typedef std::list<Method*> MethodList;
    }
}

#endif //PROJECT_METHOD_HH
