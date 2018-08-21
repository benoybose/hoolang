//
// Created by COMP on 29-06-2018.
//

#ifndef PROJECT_METHOD_HH
#define PROJECT_METHOD_HH

#include "MethodParam.hh"
#include "StackScope.hh"
#include "ICodeGeneratable.hh"

#include <string>
#include <memory>
#include <list>
#include <tuple>
#include <vector>

namespace hoo {
    namespace jit {

        extern const std::string TYPENAME_VOID;

        class Module;

        class Method : public StackScope, public ICodeGeneratable {
            friend class Module;

        private:
            Module *_module;
            std::string _name;
            std::string _returnType;

        private:
            Method(const std::string &methodName, Module *module);

        public:
            Module *GetModule() const;

            const std::string &GetName() const;

            void SetReturnType(const std::string &returnType);

            const std::string &GetReturnType() const;

            MethodParam &AddParameter(const std::string &typeName,
                                      std::string paramName);

            const std::list<StackItem *> GetParameters() const;

            std::vector<unsigned char> Generate() override;

        };

        typedef std::list<Method *> MethodList;
    }
}

#endif //PROJECT_METHOD_HH
