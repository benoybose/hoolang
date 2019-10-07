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

#ifndef PROJECT_METHOD_HH
#define PROJECT_METHOD_HH

#include "MethodParam.hh"
#include "StackScope.hh"
#include "ICodeGeneratable.hh"

#include <string>
#include <memory>
#include <list>
#include <tuple>
#include <vector>
#include <cstdint>

namespace hoo {
    namespace jit {

        extern const std::string TYPENAME_VOID;

        class JITModule;

        class Method : public StackScope, public ICodeGeneratable {
            friend class JITModule;

        private:
            JITModule *_module;
            std::string _name;
            std::string _returnType;

        private:
            Method(const std::string &methodName, JITModule *module);

        public:
            JITModule *GetModule() const;

            const std::string &GetName() const;

            void SetReturnType(const std::string &returnType);

            const std::string &GetReturnType() const;

            MethodParam &AddParameter(const std::string &typeName,
                                      std::string paramName);

            const std::list<StackItem *> GetParameters() const;

            std::vector<uint8_t > Generate() override;

        };

        typedef std::list<Method *> MethodList;
    }
}

#endif //PROJECT_METHOD_HH
