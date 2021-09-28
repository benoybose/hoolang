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

#include <hoo/emitter/DefinitionEmitter.hh>
#include <hoo/emitter/ClassDefinitionEmitter.hh>
#include <hoo/emitter/EmitterException.hh>
#include <hoo/emitter/FunctionDefinitionEmitter.hh>

#include <hoo/ast/ClassDefinition.hh>
#include <hoo/ast/FunctionDefinition.hh>

#include <memory>

namespace hoo
{
    namespace emitter
    {
        DefinitionEmitter::DefinitionEmitter(std::shared_ptr<Definition>  definition,
        const EmitterContext& context,
        std::shared_ptr<ClassDefinition> parent_class_definition) :
        EmitterBase(context),
        _definition(definition),
        _parent_class_definition (parent_class_definition)
        {
        }

        std::shared_ptr<ClassDefinition> DefinitionEmitter::GetParentClass()
        {
            return _parent_class_definition;
        }

        void DefinitionEmitter::Emit()
        {
            auto const definitionType = _definition->GetDefinitionType();
            switch (definitionType) {
                case DEFINITION_CLASS:
                {
                    auto classDefinition = std::dynamic_pointer_cast<ClassDefinition>(_definition);
                    ClassDefinitionEmitter emitter(classDefinition,
                    _emitter_context,
                    _parent_class_definition);
                    emitter.Emit();
                    break;
                }
                case DEFINITION_FUNCTION:
                {
                    auto function_definition = std::dynamic_pointer_cast<FunctionDefinition>(_definition);
                    FunctionDefinitionEmitter emitter(function_definition,
                    _emitter_context,
                    _parent_class_definition);
                    emitter.Emit();
                    break;
                }
                default:
                {
                    throw EmitterException(ERR_EMITTER_UNSUPPORTED_DEFINITION);
                }
            }
        }
    }
}

