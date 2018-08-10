//
// Created by COMP on 10-08-2018.
//

#ifndef PROJECT_METHODPARAM_HH
#define PROJECT_METHODPARAM_HH

#include <string>

namespace hoo {
    namespace jit {
        class Method;

        class MethodParam {
            friend class Method;

        private:
            MethodParam(const std::string &type, const std::string &name, size_t ordinal);

        public:
            const std::string &GetName() const;

            const std::string &GetType() const;

            size_t GetOrdinal() const;

        private:
            std::string _name;
            std::string _type;
            size_t _ordinal;
        };
    }
}

#endif //PROJECT_METHODPARAM_HH
