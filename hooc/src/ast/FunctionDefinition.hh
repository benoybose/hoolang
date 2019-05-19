//
// Created by benoy on 5/19/2019.
//

#ifndef PROJECT_FUNCTIONDEFINITION_HH
#define PROJECT_FUNCTIONDEFINITION_HH

#include "TypeSpecification.hh"
#include "Declaration.hh"

#include <string>
#include <list>

namespace hooc {
    namespace ast {
        class FunctionDefinition {
        private:
            TypeSpecification *_returnType;
            std::string _name;
            std::list<Declaration *> _param_list;
            void *_statement;
        public:
            FunctionDefinition(std::string name,
                               TypeSpecification *returnType,
                               std::list<Declaration *> &param_list,
                               void *statement);

        public:
            const std::string GetName() const;

            const TypeSpecification *GetReturnType() const;

            const std::list<Declaration *> &GetParamList() const;

            const void *GetStatement() const;
        };
    }
}

#endif //PROJECT_FUNCTIONDEFINITION_HH
