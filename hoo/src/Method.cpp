#include "Method.hh"
#include "JITException.hh"

namespace hoo {
    namespace jit {
        const std::string TYPENAME_VOID = "hoo.void";

        Method::Method(const std::string &methodName, Module *module) :
                _module(module),
                _name(methodName),
                _returnType(TYPENAME_VOID) {
        }

        Module *Method::GetModule() const {
            return this->_module;
        }

        const std::string &Method::GetName() const {
            return this->_name;
        }

        void Method::SetReturnType(const std::string &returnType) {
            this->_returnType = returnType;
        }

        const std::string &Method::GetReturnType() const {
            return this->_returnType;
        }

        MethodParam& Method::AddParameter(const std::string &typeName,
                                          std::string paramName) {
            if (this->HasParam(paramName)) {
                throw JITException(HOO_ERROR_DUPLICATE_PARAM_NAME);
            }

            auto param = new MethodParam(typeName, paramName,
                    this->_params.size());
            this->_params.push_back(param);
            return *(param);
        }

        bool Method::HasParam(const std::string &paramName) {
            for (auto iterator = this->_params.begin();
                 iterator != this->_params.end(); ++iterator) {
                if (0 == (*iterator)->_name.compare(paramName)) {
                    return true;
                }
            }
            return false;
        }

        const std::list<MethodParam *> &Method::GetParameters() const {
            return this->_params;
        }
    }
}