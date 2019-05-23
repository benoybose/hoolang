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

#ifndef PROJECT_TYPESPEC_HH
#define PROJECT_TYPESPEC_HH

#include <string>
#include <memory>

namespace hoo {
    namespace jit {
        class TypeSpec {
        private:
            std::string _typeName;
            std::size_t _size;
            bool _is_value;
        public:
            TypeSpec(const std::string &_typeName, size_t _size, bool _is_value);

        public:
            const std::string &GetTypeName() const;

            std::size_t GetSize();

            bool IsValueType();
        };

        typedef std::shared_ptr<TypeSpec> TypeSpecPtr;
    }
}

#endif //PROJECT_TYPESPEC_HH
