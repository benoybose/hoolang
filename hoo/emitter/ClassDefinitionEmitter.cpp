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

#include <hoo/emitter/ClassDefinitionEmitter.hh>
#include <hoo/emitter/DefinitionEmitter.hh>
#include <hoo/emitter/EmitterException.hh>
#include <hoo/ast/ClassDefinition.hh>

#include <memory>

namespace hoo
{
    namespace emitter
    {
        ClassDefinitionEmitter::ClassDefinitionEmitter(std::shared_ptr<ClassDefinition>  class_definition,
        const EmitterBase& parent_emitter,
        std::shared_ptr<ClassDefinition> parent_class_definition) : 
        DefinitionEmitterExtended(class_definition, parent_emitter, parent_class_definition)
        {
        }

        void ClassDefinitionEmitter::Emit()
        {
            auto class_definition = GetDefinition();
            auto const& class_body = class_definition ->GetBody();
            auto const& class_body_items = class_body->GetItems();

            std::list<std::shared_ptr<DeclarationStatement>> declaration_statements;

            for (auto const& class_body_item : class_body_items)
            {
                auto const class_body_item_type = class_body_item->GetType();
                switch (class_body_item_type)
                {
                    case CLSBODY_DECLARATIONSTMT:
                    {
                        auto const& declaration_statement = class_body_item->GetDeclarationStatement();
                        declaration_statements.push_back(declaration_statement);
                        break;
                    }
                    case CLSBODY_DEFINITION:
                    {
                        auto const& definition = class_body_item->GetDefinition();
                        DefinitionEmitter emitter(definition, *this, class_definition);
                        emitter.Emit();                        
                        break;
                    }
                    default:
                    {
                        throw EmitterException(EMITTER_ERR_03MSG, EMITTER_ERR_03);
                    }
                }
            }            
        }
    }
}
