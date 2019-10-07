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

#include "JITModule.hh"

namespace hoo {
    namespace jit {
        JITModule::JITModule(ModuleType module_type, std::string name, JIT *jit) :
                _moduleType(module_type),
                _name(name),
                _jit(jit) {
        }

        ModuleType JITModule::GetModuleType() const {
            return _moduleType;
        }

        const std::string &JITModule::GetName() const {
            return _name;
        }

        JIT *JITModule::GetJIT() const {
            return this->_jit;
        }

        Method &JITModule::CreateMethod(const std::string &name) {
            Method *method = new Method(name, this);
            this->_methods.push_back(method);
            return *(method);
        }

        JITModule::~JITModule() {
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