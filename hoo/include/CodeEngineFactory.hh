//
// Created by COMP on 31-08-2018.
//

#ifndef CODEENGINEFACTORY_HH
#define CODEENGINEFACTORY_HH

#include "ICodeEngine.hh"

#include <string>
namespace hoo {
    namespace jit {
        namespace code {
            class CodeEngineFactory {
            public:
                static CodeEngineFactory* GetInstance();
                ICodeEngine* GetEngine(std::string engineId);
            private:
                static CodeEngineFactory* _instance;

            private:
                CodeEngineFactory();
            };
        }
    }
}

#endif //PROJECT_CODEENGINEFACTORY_HH
