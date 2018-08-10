#include "Module.hh"

namespace hoo {
    namespace jit {
        Module::Module(ModuleType module_type, std::string name, JIT *jit) :
                _moduleType(module_type),
                _name(name),
                _jit(jit) {
        }

        ModuleType Module::GetModuleType() const {
            return _moduleType;
        }

        const std::string &Module::GetName() const {
            return _name;
        }

        JIT *Module::GetJIT() const {
            return this->_jit;
        }

        Method &Module::CreateMethod(const std::string &name) {
            Method *method = new Method(name, this);
            this->_methods.push_back(method);
            return *(method);
        }

        Module::~Module() {
            for(auto iterator = this->_methods.begin();
                    iterator != this->_methods.end(); ++iterator) {
                Method* method = *iterator;
                if(nullptr != method) {
                    delete method;
                }
            }
            this->_methods.clear();
        }
    }
}