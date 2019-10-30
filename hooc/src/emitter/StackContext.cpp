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

#include "StackContext.hh"

namespace hooc {
    namespace emitter {
        StackContext::StackContext(size_t depth) : _depth(depth) {
        }

        size_t StackContext::GetDepth() const {
            return _depth;
        }

        list<StackContext *> StackContext::GetChildren() const {
            return this->_children;
        }

        size_t StackContext::AddChild(StackContext *child) {
            this->_children.push_back(child);
            return this->_children.size();
        }

        StackContext::~StackContext() {
            auto iterator = this->_children.begin();
            while(iterator != this->_children.end()) {
                auto child = *(iterator);
                delete child;
                iterator ++;
            }
        }
    }
}
