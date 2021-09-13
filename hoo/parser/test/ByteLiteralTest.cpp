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

#include "ParserTestUnitBase.hh"
#include <hoo/test/HooTest.hh>

class ByteLiteralTest : public ParserTestUnitBase
{
public:
    ByteLiteralTest()
    {
        RegisterTestCase("ByteLiteral01Test",
                         &ByteLiteralTest::ByteLiteral01Test);
        RegisterTestCase("ByteLiteral02Test",
                         &ByteLiteralTest::ByteLiteral02Test);
    }

public:
    void ByteLiteral01Test()
    {
        const std::string source = R"source(
        class Bar {
            private foo() : byte {
                return 0xFF;
            }            
        }
        )source";
        const auto class_name = "Bar";
        const auto function_name = "foo";

        auto func_def = GetClassMethod(source, class_name, function_name);
        auto func_decl = func_def->GetDeclaration();
        auto declarator = func_decl->GetDeclarator();
        Equal(declarator, DECLARATOR_PRIVATE);
        auto return_type = func_decl->GetReturnType();
        VerifyType(return_type, BASIC_DATA_TYPE_BYTE);
        auto func_body = func_def->GetBody();
        auto compound_stmt = AsCompoundStatement(func_body);
        auto body_return_type = compound_stmt->GetReturnType();
        NotNull(body_return_type);
        VerifyType(body_return_type, BASIC_DATA_TYPE_BYTE);
    }

    void ByteLiteral02Test()
    {
        const std::string source = R"source(
        class Bar {
            private foo() : byte {
                return 0XFE;
            }            
        }
        )source";
        const auto class_name = "Bar";
        const auto function_name = "foo";

        auto func_def = GetClassMethod(source, class_name, function_name);
        auto func_decl = func_def->GetDeclaration();
        auto declarator = func_decl->GetDeclarator();
        Equal(declarator, DECLARATOR_PRIVATE);
        auto return_type = func_decl->GetReturnType();
        VerifyType(return_type, BASIC_DATA_TYPE_BYTE);
        auto func_body = func_def->GetBody();
        auto compound_stmt = AsCompoundStatement(func_body);
        auto body_return_type = compound_stmt->GetReturnType();
        NotNull(body_return_type);
        VerifyType(body_return_type, BASIC_DATA_TYPE_BYTE);
    }
};

HOO_TEST_CASE(ByteLiteralTest)