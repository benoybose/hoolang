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

#include "FuncEmitter.hh"
#include <emitter/StackItem.hh>

namespace hooc {
    namespace emitter {
        FuncEmitter::FuncEmitter(FunctionDefinition *definition, EmitterConfig config) :
                _definition(definition),
                _function_context(nullptr),
                _config(config) {
        }

        FunctionDefinition *FuncEmitter::GetDefinition() const {
            return _definition;
        }

        const NameMangler &FuncEmitter::GetMangler() const {
            return this->_mangler;
        }

        void FuncEmitter::SetFunctionContext(FuncEmitterContext *context) {
            this->_function_context = context;
        }

        const EmitterConfig &FuncEmitter::GetConfig() const {
            return _config;
        }

        FuncEmitterContext *FuncEmitter::GetFunctionContext() const {
            return _function_context;
        }

        FuncEmitter::~FuncEmitter() {
            delete this->_function_context;
        }
    }
}
