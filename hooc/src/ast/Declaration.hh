//
// Created by benoy on 5/19/2019.
//

#ifndef PROJECT_DECLARATION_HH
#define PROJECT_DECLARATION_HH

#include "TypeSpecification.hh"

#include <string>

namespace hooc {
    namespace ast {
        class Declaration {
        private:
            TypeSpecification* _declared_type;
            std::string _name;
            void* _initializer;

        public:
            Declaration(std::string name, TypeSpecification* declared_type, void* initializer);
            virtual ~Declaration();

        public:
            const TypeSpecification* GetDelcaredType() const;
            const std::string& GetName() const;
            const void* GetInitializer() const;
        };
    }
}



#endif //PROJECT_DECLARATION_HH
