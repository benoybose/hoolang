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

#ifndef HOOLANG_FUNCEMITTER_HH
#define HOOLANG_FUNCEMITTER_HH

#include <ast/FunctionDefinition.hh>
#include <emitter/FuncEmitterContext.hh>
#include <emitter/Code.hh>
#include <emitter/NameMangler.hh>
#include <emitter/EmitterConfig.hh>

using namespace hooc::ast;

namespace hooc {
    namespace emitter {
        class FuncEmitter {
        private:
            FunctionDefinition *_definition;
            FuncEmitterContext *_function_context;
            NameMangler _mangler;
            EmitterConfig _config;

        protected:
            FuncEmitter(FunctionDefinition *definition,
                        EmitterConfig config);

        protected:
            FunctionDefinition *GetDefinition() const;

            const NameMangler &GetMangler() const;

            void SetFunctionContext(FuncEmitterContext* context);

        public:
            const EmitterConfig &GetConfig() const;

            FuncEmitterContext *GetFunctionContext() const;

        public:
            virtual Code *GenerateCode() = 0;

        public:
            virtual ~FuncEmitter();
        };
    }
}

#endif //HOOLANG_FUNCEMITTER_HH
