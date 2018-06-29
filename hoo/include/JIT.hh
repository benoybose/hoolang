//
// Created by COMP on 26-06-2018.
//

#include "Module.hh"

#include <list>
#include <memory>

#ifndef HOO_JIT_HH
#define HOO_JIT_HH

namespace hoo {
    namespace jit {
        class JIT {
        private:
            ModulePtrMap _moduleList;

        public:
            JIT();

        public:
            Module &CreateModule(ModuleType module_type, std::string name);

            Module &GetModule(std::string moduleName) const;
        };
    }
}


#endif //HOO_JIT_HH
