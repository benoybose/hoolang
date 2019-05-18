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
        typedef enum {
            TYPESPEC_SIMPLE,
            TYPESPEC_NESTED,
            TYPESPEC_ARRAY
        } TYPESPEC_TYPE;
        class TypeSpecification {
        protected:
            TYPESPEC_TYPE _type;
            TypeSpecification* _parent;
            std::string _name;
            bool _is_array;
        public:
            explicit TypeSpecification(std::string &name);
            explicit TypeSpecification(const std::string &name);
        public:
            const std::string &GetName() const;
            const TYPESPEC_TYPE GetType() const;
        };

        class NestedTypeSpecification : public TypeSpecification {
        public:
            NestedTypeSpecification(TypeSpecification *typeSpecification,
                    std::string& name);
            NestedTypeSpecification(TypeSpecification *typeSpecification,
                    const std::string& name);
        public:
            const TypeSpecification *GetParent() const;
        };

        class ArrayTypeSpecification: public NestedTypeSpecification {
        public:
            ArrayTypeSpecification(TypeSpecification* parent);
        };
    }
}


#endif //PROJECT_TYPESPECIFICATION_HH
