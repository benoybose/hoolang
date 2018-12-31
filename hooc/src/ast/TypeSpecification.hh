/*
 * Copyright 2018 Benoy Bose
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

#ifndef TYPESPECIFICATION_HH
#define TYPESPECIFICATION_HH

#include "HooTypes.hh"

#include <string>
#include <list>

namespace hooc {
    namespace ast {
        class TypeSpecification {
        public:
            TypeSpecification();
            TypeSpecification(std::string root);

        public:
            const std::list<std::string> &GetTypePath() const;

            bool IsArray() const;

            const hoo::Integer GetArraySize() const;

        public:
            void AddPath(std::string path);
            void AddPath(const std::list<std::string>& path);
            void SetAsArray(bool is_array = true);
            void SetArraySize(hoo::Integer array_size);

        private:
            std::list<std::string> _type_path;
            bool _is_array;
            hoo::Integer _array_size;
        };
    }
}


#endif //PROJECT_TYPESPECIFICATION_HH
