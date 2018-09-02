#include "CodeEngineFactory.hh"
#include "ICodeEngine.hh"

#include <string>

namespace hoo {
    namespace jit {
        namespace code {
            CodeEngineFactory *CodeEngineFactory::_instance = nullptr;

            CodeEngineFactory::CodeEngineFactory() {
            }

            CodeEngineFactory *CodeEngineFactory::GetInstance() {
                if (nullptr == CodeEngineFactory::_instance) {
                    CodeEngineFactory::_instance = new CodeEngineFactory();
                }
                return CodeEngineFactory::_instance;
            }

            ICodeEngine *CodeEngineFactory::GetEngine(std::string engineId) {

            }
        }
    }
}