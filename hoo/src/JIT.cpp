#include "JIT.hh"

namespace hoo {
    namespace jit {

        JIT::JIT() {}

        Module &JIT::CreateModule(ModuleType module_type, std::string moduleName) {
            Module *module = new Module(module_type, moduleName, this);
            _modules.emplace(moduleName, module);
        }

        Module &JIT::GetModule(std::string moduleName) const {
            auto module = _modules.at(moduleName);
            return *module;
        }
    }
}
