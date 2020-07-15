/*
 * Copyright 2019 Benoy Bose
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

#include <hoo/ast/AST.hh>
#include <hoo/parser/visitors/ClassDefinitionVisitor.hh>

#include <string>

using namespace antlr4;
using namespace antlrcpp;
using namespace hoo::ast;

namespace hoo
{
    namespace parser
    {
        Any ClassDefinitionVisitor::visitClassDefinition(HooParser::ClassDefinitionContext *ctx)
        {
            auto className = ctx->className->getText();
            std::list<std::string> base_entity_names;
            std::shared_ptr<ClassBody> class_body;
            auto base_entities = ctx->baseEntities;
            if (nullptr != base_entities)
            {
                auto base_types = base_entities->typeSpecifier();
                for (auto base_type : base_types)
                {
                    auto type = visit(base_type).as<TypeSpecification *>();
                    if (nullptr != type)
                    {
                        auto typeType = type->GetType();
                        if (typeType != TYPE_SPEC_REFERENCE)
                        {
                            delete type;
                            // todo: // Throw parse exception
                        }
                        else
                        {
                            auto base_entity_name = type->GetName();
                            base_entity_names.push_back(base_entity_name);
                            delete type;
                        }
                    }
                }
            }

            auto body_context = ctx->classBody();
            auto body = this->visit(body_context).as<ClassBody *>();
            class_body = std::shared_ptr<ClassBody>(body);

            auto classDefinition = new ClassDefinition(className,
                                                       base_entity_names,
                                                       class_body);
            Definition *definition = (Definition *)classDefinition;
            return Any(definition);
        }

        Any ClassDefinitionVisitor::visitClassBody(HooParser::ClassBodyContext *ctx)
        {
            auto class_body_item_contexts = ctx->classBodyItem();
            std::list<std::shared_ptr<ClassBodyItem>> items;
            for (auto class_body_item_context : class_body_item_contexts)
            {
                auto item = this->visit(class_body_item_context).as<ClassBodyItem *>();
                std::shared_ptr<ClassBodyItem> itemptr(item);
                items.push_back(itemptr);
            }
            ClassBody *class_body = new ClassBody(items);
            return Any(class_body);
        }
    } // namespace parser
} // namespace hoo