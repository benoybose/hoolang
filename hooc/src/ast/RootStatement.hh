//
// Created by benoy on 5/16/2019.
//

#ifndef PROJECT_ROOTSTATEMENT_HH
#define PROJECT_ROOTSTATEMENT_HH

namespace hooc {
    namespace ast {
        typedef enum {
            Class,
            Interface
        } ROOT_STATEMENT_TYPE;

        class RootStatement {
        protected:
            RootStatement(ROOT_STATEMENT_TYPE type);

        private:
            ROOT_STATEMENT_TYPE _type;

        public:
            const ROOT_STATEMENT_TYPE GetType() const;
        };
    }
}

#endif //PROJECT_ROOTSTATEMENT_HH
