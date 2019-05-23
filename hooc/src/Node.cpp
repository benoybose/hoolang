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

#include "Node.hh"

#include <string>

namespace hooc {
    Node::Node(hooc::NodeType nodeType) {
        this->_nodeType = nodeType;
    }

    NodeType Node::GetNodeType() {
        return this->_nodeType;
    }

    std::string Node::GetNodeTypeName() {
        switch(this->_nodeType) {
            case hooc::NodeType ::NODE_INVALID: return "Invalid Node";
            case hooc::NodeType ::NODE_EXPRESSION: return "Expression Node";
            case hooc::NodeType ::NODE_OPERATOR: return "Operator Node";
            case hooc::NodeType ::NODE_PROGRAM: return "Program Node";
            case hooc::NodeType ::NODE_STATEMENTLIST: return "Statement List Node";
            case hooc::NodeType ::NODE_STATEMENT: return "Statement Node";
            default: return "Unknown Node";
        }
    }
}
