#include "Method.hh"
#include "JITException.hh"
#include "StackScope.hh"

#include <algorithm>

namespace hoo {
    namespace jit {
        const std::string TYPENAME_VOID = "hoo.void";

        Method::Method(const std::string &methodName, Module *module) :
                StackScope(nullptr),
                _name(methodName),
                _module(module),
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

        MethodParam &Method::AddParameter(const std::string &typeName, std::string paramName) {
            if (this->HasItem(paramName)) {
                throw JITException(HOO_ERROR_DUPLICATE_ITEM_NAME);
            }

            auto param = new MethodParam(typeName, paramName);
            this->AddItem(param);
            return *(param);
        }

        const std::list<StackItem *> Method::GetParameters() const {
            auto items = this->GetItems();
            std::list<StackItem *> params;
            std::copy_if(items.begin(), items.end(), std::back_inserter(params), [](StackItem *item) { return true; });
            return params;
        }
    }
}