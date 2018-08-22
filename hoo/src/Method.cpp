#include "Method.hh"
#include "JITException.hh"
#include "StackScope.hh"
#include "HooConfig.hh"

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

        std::vector<uint8_t> Method::Generate() {
            auto code = std::vector<unsigned char>();
#ifndef HOO_X64
            return code;
#else
            code.push_back(0x55); // push   RBP
            code.push_back(0x48); // mov    rbp,rsp
            code.push_back(0x89);
            code.push_back(0xe5);
            // todo: do other instructions
            code.push_back(0x5d); // pop    rbp
            code.push_back(0xc3); // ret
            return code;
#endif
        }
    }
}