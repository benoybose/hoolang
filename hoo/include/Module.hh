#ifndef PROJECT_MODULE_HH
#define PROJECT_MODULE_HH

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

        class Module {
            friend class JIT;
        private:
            ModuleType _moduleType;
            std::string _name;

        private:
            Module(ModuleType module_type,
                   std::string name);
        public:
            ModuleType GetModuleType() const;
            const std::string &GetName() const;
        };

        typedef std::shared_ptr<Module> ModulePtr;
        typedef std::map<std::string, ModulePtr> ModulePtrMap;
    }
}

#endif //PROJECT_MODULE_HH
