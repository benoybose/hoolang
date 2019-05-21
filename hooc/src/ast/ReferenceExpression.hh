//
// Created by benoy on 5/21/2019.
//

#ifndef REFERENCEEXPRESSION_HH
#define REFERENCEEXPRESSION_HH

#include "Expression.hh"

#include <string>

namespace hooc {
    namespace ast {
        class ReferenceExpression: public Expression {
        private:
            ReferenceExpression* _parent;
            std::string _name;

        public:
            explicit ReferenceExpression(std::string& name);
            explicit ReferenceExpression(const std::string& name);
            ReferenceExpression(ReferenceExpression* parent, std::string& name);
            ReferenceExpression(ReferenceExpression* parent, const std::string& name);

        public:
            const std::string& GetName() const;
            const ReferenceExpression* GetParent() const;
        };
    }
}




#endif //PROJECT_REFERENCEEXPRESSION_HH
