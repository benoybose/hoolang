#ifndef PROJECT_MODULE_HH
#define PROJECT_MODULE_HH

#include "Method.hh"

#include <string>
#include <memory>
#include <list>
#include <map>

namespace hoo {
    namespace jit {
        typedef enum {
            MODULE_INSTANCE,
            MODULE_CLASS
        } ModuleType;

        class JIT;

        class Module;

        class Module {
            friend class JIT;

        private:
            ModuleType _moduleType;
            std::string _name;
            JIT* _jit;
            MethodList _methods;

        private:
            Module(ModuleType module_type, std::string name, JIT* jit);

        public:
            ModuleType GetModuleType() const;

            const std::string &GetName() const;

            JIT* GetJIT() const;
            Method &CreateMethod(const std::string& name);
        };

        typedef std::map<std::string, Module*> ModuleMap;
    }
}

#endif //PROJECT_MODULE_HH
