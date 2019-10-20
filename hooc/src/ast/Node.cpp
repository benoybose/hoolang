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

#include <utility>

#include "Node.hh"
#include <antlr4-runtime.h>

using namespace antlr4;

namespace hooc {
    namespace ast {
        Node::Node(ParserRuleContext *context, std::string file_name) :
                _file_name(std::move(file_name)),
                _start(nullptr),
                _end(nullptr) {
            this->_start = new Position(context->start->getLine(),
                                        context->start->getCharPositionInLine());
            this->_end = new Position(context->stop->getLine(),
                                      context->stop->getCharPositionInLine());
        }

        const std::string &Node::GetFileName() const {
            return _file_name;
        }

        Position *Node::GetStart() const {
            return _start;
        }

        Position *Node::GetEnd() const {
            return _end;
        }

        Node::~Node() {
            delete this->_start;
            delete this->_end;
        }
    }
}
