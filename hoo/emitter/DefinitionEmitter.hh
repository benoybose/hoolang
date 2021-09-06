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

#ifndef _DEFINITION_EMITTER_HH
#define _DEFINITION_EMITTER_HH

#include <hoo/emitter/EmitterBase.hh>
#include <hoo/ast/Definition.hh>
#include <hoo/ast/ClassDefinition.hh>

#include <memory>

using namespace hoo::ast;

namespace hoo
{
    namespace emitter
    {
        class DefinitionEmitter : public EmitterBase
        {
            private:
            std::shared_ptr<Definition>  _definition;
            std::shared_ptr<ClassDefinition>  _parent_class_definition;

            public:
            DefinitionEmitter(std::shared_ptr<Definition>  definition,
            const EmitterBase& parent_emitter,
            std::shared_ptr<ClassDefinition> parent_class_definition);

            public:
            std::shared_ptr<ClassDefinition> GetParentClass();
            void Emit();
        };

        template <typename T> class DefinitionEmitterExtended : public DefinitionEmitter
        {
            private:
            std::shared_ptr<T> _typed_definition;

            public:
            DefinitionEmitterExtended(std::shared_ptr<T>  definition,
            const EmitterBase& parent_emitter,
            std::shared_ptr<ClassDefinition> parent_class_definition) : 
            DefinitionEmitter(dynamic_pointer_cast<Definition> (definition), parent_emitter, parent_class_definition),
            _typed_definition (definition)
            {}

            public:
            inline std::shared_ptr<T> GetDefinition() { return _typed_definition; }
        };
    }
}

#endif // _DEFINITION_EMITTER_HH