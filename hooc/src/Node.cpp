//
// Created by COMP on 22-06-2018.
//

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
