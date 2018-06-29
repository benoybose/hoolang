#include "Module.hh"

namespace hoo {
    namespace jit {
        Module::Module(hoo::jit::ModuleType module_type, std::string name):
                _moduleType(module_type),
                _name(name) {
        }

        ModuleType Module::GetModuleType() const {
            return _moduleType;
        }

        const std::string &Module::GetName() const {
            return _name;
        }
    }
}