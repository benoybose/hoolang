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

#include "TypeSpecification.hh"
#include "LiteralExpression.hh"

#include <string>
#include <list>

namespace hooc {
    namespace ast {

        TypeSpecification::TypeSpecification() {
        }

        TypeSpecification::TypeSpecification(std::string root) {
            this->_type_path.push_back(root);
        }

        const std::list<std::string> &TypeSpecification::GetTypePath() const {
            return this->_type_path;
        }

        bool TypeSpecification::IsArray() const {
            return _is_array;
        }

        const hoo::Integer TypeSpecification::GetArraySize() const {
            return this->_array_size;
        }

        void TypeSpecification::AddPath(std::string path) {
            this->_type_path.push_back(path);
        }

        void TypeSpecification::AddPath(const std::list<std::string> &path) {
            for(auto iterator = path.begin(); iterator != path.end(); ++iterator) {
                this->_type_path.push_back(*iterator);
            }
        }

        void TypeSpecification::SetAsArray(bool is_array) {
            if(!is_array) {
                this->_array_size = 0;
            }
            this->_is_array = is_array;
        }

        void TypeSpecification::SetArraySize(hoo::Integer array_size) {
            if(0 < array_size) {
                this->_is_array = true;
            }
            this->_array_size = array_size;
        }
    }
}
