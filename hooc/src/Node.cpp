//
// Created by COMP on 22-06-2018.
//

#include "Node.hh"

#include <string>

namespace hooc {
    Node::Node() {
        this->_nodeType = hooc::NodeType ::InvalidNode;
    }

    Node::Node(hooc::NodeType nodeType) {
        this->_nodeType = nodeType;
    }

    Node::Node(const hooc::Node &node) {
        this->_nodeType = node._nodeType;
    }

    NodeType Node::getNodeType() {
        return this->getNodeType();
    }

    std::string Node::getNodeTypeName() {
        switch(this->_nodeType) {
            case hooc::NodeType ::InvalidNode: return "Invalid Node";
            case hooc::NodeType ::ExpressionNode: return "Expression Node";
            case hooc::NodeType ::OperatorNode: return "Operator Node";
            case hooc::NodeType ::ProgramNode: return "Program Node";
            case hooc::NodeType ::StatementListNode: return "Statement List Node";
            case hooc::NodeType ::StatementNode: return "Statement Node";
        }
    }
}
