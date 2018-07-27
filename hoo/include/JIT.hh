//
// Created by COMP on 26-06-2018.
//

#include "Module.hh"

#include <list>
#include <memory>

#ifndef HOO_JIT_HH
#define HOO_JIT_HH

#include <memory>

namespace hoo {
    namespace jit {
        class JIT;

        typedef std::shared_ptr<JIT> JITPtr;

        class JIT {
        private:
            ModuleMap _modules;

        public:
            JIT();

        public:
            Module &CreateModule(ModuleType module_type, std::string moduleName);

            Module &GetModule(std::string moduleName) const;
        };
    }
}


#endif //HOO_JIT_HH
