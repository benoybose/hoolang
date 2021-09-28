/*
 * Copyright 2021 Benoy Bose
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <hoo/emitter/FunctionDefinitionEmitter.hh>
#include <hoo/emitter/EmitterUtils.hh>
#include <hoo/emitter/EmitterException.hh>
#include <hoo/emitter/StatementEmitter.hh>
#include <hoo/emitter/CastEmitter.hh>

#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/BasicBlock.h>

#include <exception>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace hoo::ast;
using namespace llvm;

namespace hoo
{
    namespace emitter
    {
        FunctionDefinitionEmitter::FunctionDefinitionEmitter(std::shared_ptr<FunctionDefinition> function_definition,
        const EmitterContext& emitter_context,
        std::shared_ptr<ClassDefinition> parent_class_definition) :
        DefinitionEmitterExtended(function_definition, emitter_context, parent_class_definition)
        {
        }

        void FunctionDefinitionEmitter::Emit()
        {
            auto const &function_definition = this->GetDefinition();
            auto const &parent_class = this->GetParentClass();
            if (!function_definition)
            {
                throw EmitterException(ERR_EMITTER_INVALID_CLASS_DEFINITION);
            }

            auto const &function_declaration = function_definition->GetDeclaration();
            std::string function_name = function_declaration->GetName();

            if (parent_class)
            {
                auto parent_class_name = parent_class->GetClassName();
                function_name = parent_class_name + "$" + function_name;
            }

            auto return_type = function_declaration->GetReturnType();
            auto context = _emitter_context.GetContext();

            Type *function_return_type = nullptr;
            if (!return_type)
            {
                function_return_type = Type::getVoidTy(*context);
            }
            else
            {
                function_return_type = EmitterUtils::ResolveType(return_type, *context);
            }

            auto param_list = function_declaration->GetParamList();
            param_list.reverse();

            std::vector<Type *> params;
            for (auto const &param : param_list)
            {
                auto param_type_spec = param->GetType();
                auto param_type = EmitterUtils::ResolveType(param_type_spec, *context);
                params.push_back(param_type);
            }

            FunctionType *function_type = nullptr;
            if (!params.empty())
            {
                function_type = FunctionType::get(function_return_type, params, false);
            }
            else
            {
                function_type = FunctionType::get(function_return_type, false);
            }

            auto current_module = _emitter_context.GetModule();
            auto function = Function::Create(function_type,
            Function::ExternalLinkage,
            function_name, current_module);

            if (function_return_type->isIntegerTy(8))
            {
                function->addAttribute(0, Attribute::ZExt);
            }

            _emitter_context.SetFunction(function);
            auto block_context = _emitter_context.BeginBlock("entry");
            unsigned int arg_index = 0;
            for (auto const &param : param_list)
            {
                auto arg = function->getArg(arg_index);
                auto const &arg_name = param->GetName();
                arg->setName(arg_name);
                if (arg->getType()->isIntegerTy(8))
                {
                    arg->addAttr(Attribute::ZExt);
                }

                block_context->AddSymbol(arg_name, arg);
                arg_index += 1;
            }

            auto const &body = function_definition->GetBody();
            StatementEmitter emitter(body, _emitter_context);
            emitter.Emit(body);
            _emitter_context.EndBlock();
        }
    }
}