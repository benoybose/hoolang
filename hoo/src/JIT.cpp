#include "JIT.hh"

namespace hoo {
    namespace jit {

        Module &JIT::CreateModule(ModuleType module_type, std::string name) {
            ModulePtr module = ModulePtr(new Module(module_type, name));
            _moduleList.emplace(name, module);
        }

        Module &JIT::GetModule(std::string moduleName) const {
            auto module = _moduleList.at(moduleName);
            return * module.get();
        }
    }
}
