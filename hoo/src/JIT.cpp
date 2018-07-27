#include "JIT.hh"
#include "JITException.hh"

namespace hoo {
    namespace jit {

        JIT::JIT() {}

        Module &JIT::CreateModule(ModuleType module_type, std::string moduleName) {
            if(_modules.find(moduleName) !=  _modules.end()) {
                throw JITException(HOO_ERROR_DUPLICATE_MODULE_NAME);
            }

            Module *module = new Module(module_type, moduleName, this);
            _modules.emplace(moduleName, module);
        }

        Module &JIT::GetModule(std::string moduleName) const {
            auto module = _modules.at(moduleName);
            return *module;
        }

        std::list<std::string> JIT::GetModuleNames() const {
            std::list<std::string> moduleNames;
            for(auto module : this->_modules) {
                moduleNames.push_back(module.first);
            }
            return moduleNames;
        }
    }
}
