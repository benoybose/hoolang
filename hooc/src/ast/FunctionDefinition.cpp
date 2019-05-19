//
// Created by benoy on 5/19/2019.
//

#include "FunctionDefinition.hh"

namespace hooc {
    namespace ast {
        FunctionDefinition::FunctionDefinition(std::string name, TypeSpecification *returnType,
                                               std::list<Declaration *> &param_list,
                                               void *statement): _name(name),
                                               _returnType(returnType),
                                               _param_list(param_list),
                                               _statement(statement) {
        }

        const std::string FunctionDefinition::GetName() const {
            return this->_name;
        }

        const TypeSpecification *FunctionDefinition::GetReturnType() const {
            return this->_returnType;
        }

        const std::list<Declaration *> &FunctionDefinition::GetParamList() const {
            return this->_param_list;
        }

        const void *FunctionDefinition::GetStatement() const {
            return this->_statement;
        }
    }
}
