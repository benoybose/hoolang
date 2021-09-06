#include <hoo/emitter/FunctionDefinitionEmitter.hh>
#include <hoo/emitter/EmitterUtils.hh>

#include <exception>
#include <string>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <vector>

using namespace hoo::ast;
using namespace llvm;

namespace hoo
{
    namespace emitter
    {
        FunctionDefinitionEmitter::FunctionDefinitionEmitter(std::shared_ptr<FunctionDefinition> function_definition,
            const EmitterBase& parent_emitter,
            std::shared_ptr<ClassDefinition> parent_class_definition) :
            DefinitionEmitterExtended (function_definition, parent_emitter, parent_class_definition)
        {
        }

        void FunctionDefinitionEmitter::Emit()
        {
            auto const& function_definition = this->GetDefinition();
            auto const& parent_class = this->GetParentClass();
            if (!function_definition)
            {
                throw std::runtime_error("valid function definition not found.");
            }

            auto function_declaration = function_definition->GetDeclaration();
            std::string function_name = function_declaration->GetName();

            if (parent_class)
            {
                auto parent_class_name = parent_class->GetClassName();
                function_name = parent_class_name + "." + function_name;
            }

            auto return_type = function_declaration->GetReturnType();
            auto &context = *(this->GetContext());

            Type* function_return_type = nullptr;
            if (!return_type) {
                function_return_type = Type::getVoidTy(context);
            } else {
                function_return_type = EmitterUtils::ResolveType(return_type, context);
            }

            auto param_list = function_declaration->GetParamList();
            std::vector<Type*> params;
            for (auto const& param : param_list)
            {
                auto param_type_spec = param->GetType();
                auto param_type = EmitterUtils::ResolveType(param_type_spec, context);
                params.push_back(param_type);
            }

            FunctionType* function_type = nullptr;
            if (!params.empty())
            {
                function_type = FunctionType::get(function_return_type, params, false);
            }
            else
            {
                function_type = FunctionType::get(function_return_type, false);
            }

            auto& module = *(this->GetModule());
            Function *function = Function::Create(function_type,
            Function::ExternalLinkage, 
            function_name, module);
        }
    }
}