/*
 * Copyright 2020 Benoy Bose
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
#include <hoo/test/HooTest.hh>
#include <hoo/parser/ParserDriver.hh>

#include <sstream>
#include <memory>

using namespace hoo::ast;
using namespace hoo::test;
using namespace hoo::parser;

class ClassMethodTest01 : public TestUnit
{
public:
    ClassMethodTest01()
    {
        RegisterTestCase("EmptyFunctionTest",
                         &ClassMethodTest01::EmptyFunctionTest);
    }

    void EmptyFunctionTest()
    {
        std::ostringstream out;
        out << "class Maths {" << std::endl
            << "\tpublic func add() {" << std::endl
            << "\t}" << std::endl
            << "}";
        auto source = out.str();
        ParserDriver driver(source);
        auto unit = driver.Build();
        NotNull(unit);
        auto items = unit->GetItems();
        Count<>(items, 1);
        auto first_item = *items.begin();
        auto class_def = std::static_pointer_cast<ClassDefinition>(first_item);
        NotNull(class_def);
        auto class_name = class_def->GetClassName();
        StringEqual(class_name, "Maths");
        False(class_def->HasBaseEntities());
        False(class_def->IsEmpty());
        auto body = class_def->GetBody();
        NotNull(body);
        auto class_body_items = body->GetItems();
        Count<>(class_body_items, 1);
        auto first_class_item = *class_body_items.begin();
        NotNull(first_class_item);
        Equal(CLSBODY_DEFINITION, first_class_item->GetType());
        auto def = first_class_item->GetDefinition();
        NotNull(def);
        Equal(DEFINITION_FUNCTION, def->GetDefinitionType());
        auto func_def = std::static_pointer_cast<FunctionDefinition>(def);
        NotNull(func_def);
        auto func_decl = func_def->GetDeclaration();
        NotNull(func_decl);
        auto func_name = func_decl->GetName();
        StringEqual(func_name, "add");
        auto declarator = func_decl->GetDeclarator();
        Equal(declarator, DECLARATOR_PUBLIC);
        auto return_type = func_decl->GetReturnType();
        Null(return_type);
    }
};

HOO_TEST_CASE(ClassMethodTest01)