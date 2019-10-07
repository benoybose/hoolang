/*
 * Copyright 2019 Benoy Bose
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "JIT.hh"
#include "JITException.hh"

namespace hoo {
    namespace jit {

        JIT::JIT() {}

        JITModule &JIT::CreateModule(ModuleType module_type, std::string moduleName) {
            if (_modules.find(moduleName) != _modules.end()) {
                throw JITException(HOO_ERROR_DUPLICATE_MODULE_NAME);
            }

            JITModule *module = new JITModule(module_type, moduleName, this);
            _modules[moduleName] = module;
            return *module;
        }

        JITModule &JIT::GetModule(std::string moduleName) const {
            auto module = _modules.at(moduleName);
            return *module;
        }

        std::list<std::string> JIT::GetModuleNames() const {
            std::list<std::string> moduleNames;
            for (auto module : this->_modules) {
                moduleNames.push_back(module.first);
            }
            return moduleNames;
        }

        JIT::~JIT() {
            for (auto iterator = this->_modules.begin();
                 iterator != this->_modules.end(); ++iterator) {
                try {
                    auto module = iterator->second;
                    if (nullptr != module) {
                        delete module;
                    }
                }
                catch (...) {
                }
            }
            this->_modules.clear();
        }
    }
}

