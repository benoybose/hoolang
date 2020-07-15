/*
 * Copyright 2020 Benoy Bose
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

#include <hoo/ast/TypeSpecification.hh>

#include <string>
#include <list>

namespace hoo {
    namespace ast {

        TypeSpecification::TypeSpecification(TypeSpecificationType type) :
                _type(type) {

        }

        TypeSpecificationType TypeSpecification::GetType() const {
            return _type;
        }

        TypeSpecification::~TypeSpecification() {

        }

//        TypeSpecification::TypeSpecification(std::string &name) :
//                _name(name),
//                _is_array(false),
//                _parent(nullptr) {
//        }
//
//        TypeSpecification::TypeSpecification(const std::string &name) :
//                _name(name),
//                _is_array(false),
//                _parent(nullptr){
//        }
//
//        TypeSpecification::~TypeSpecification() {
//        }
//
//        const TYPESPEC_TYPE TypeSpecification::GetType() const {
//            return this->_type;
//        }
//
//        const std::string &TypeSpecification::GetName() const {
//            return _name;
//        }
//
//        NestedTypeSpecification::NestedTypeSpecification(TypeSpecification *typeSpecification,
//                                                         std::string &name) :
//                TypeSpecification(name) {
//        }
//
//        NestedTypeSpecification::NestedTypeSpecification(TypeSpecification *typeSpecification,
//                                                         const std::string &name) :
//                TypeSpecification(name) {
//        }
//
//        NestedTypeSpecification::~NestedTypeSpecification() {
//            if(nullptr != this->_parent) {
//                delete this->_parent;
//            }
//        }
//
//        const TypeSpecification *NestedTypeSpecification::GetParent() const {
//            return this->_parent;
//        }
//
//        ArrayTypeSpecification::ArrayTypeSpecification(TypeSpecification *parent):
//                NestedTypeSpecification(parent, ""){
//        }
//
//        ArrayTypeSpecification::~ArrayTypeSpecification() {
//        }
    }
}
