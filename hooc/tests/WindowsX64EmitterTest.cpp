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

#include "HoocTestHelper.hh"

#include <boost/test/unit_test.hpp>
#include <compiler/ParserDriver.hh>
#include <ast/FunctionDefinition.hh>
#include <emitter/x86/WindowsX64Emitter.hh>
#include <emitter/CodeType.hh>
#include <emitter/Code.hh>
#include <emitter/x86/X86Instruction.hh>
#include <misc/Utility.hh>

using namespace hooc::compiler;
using namespace hooc::ast;
using namespace hooc::emitter::x86;
using namespace hooc::emitter;
using namespace hooc::misc;

BOOST_AUTO_TEST_SUITE(WindowsX644EmitterTest)

    BOOST_AUTO_TEST_CASE(TEST01) {
        const std::string source = "func foo() {}";
        ParserDriver driver(source, "foo.hoo");
        auto module = driver.BuildModule();
        BOOST_ASSERT(module->Success());
        auto unit = module->GetUnit();
        auto func = (FunctionDefinition *) (*unit->GetItems().begin());
        BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
        WindowsX64Emitter emitter(unit);
        auto code = emitter.GenerateCode(func);
        BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
        BOOST_CHECK_EQUAL("_Z3foov", code->GetName());
        BOOST_CHECK_EQUAL(2, code->GetSize());
        const auto &buffer = code->GetBuffer();
        BOOST_CHECK_EQUAL(2, buffer.size());
        byte expected[2] = {static_cast<byte>(X86_OPCODE_NOP), static_cast<byte>(X86_OPCODE_RET)};
        BOOST_CHECK(VerifyByteVector(buffer, expected, 2));
    }

    BOOST_AUTO_TEST_CASE(TEST02) {
        const std::string source = "func foo(a:int) {}";
        ParserDriver driver(source, "foo.hoo");
        auto module = driver.BuildModule();
        BOOST_ASSERT(module->Success());
        auto unit = module->GetUnit();
        auto func = (FunctionDefinition *) (*unit->GetItems().begin());
        BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
        WindowsX64Emitter emitter(unit);
        auto code = emitter.GenerateCode(func);
        BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
        BOOST_CHECK_EQUAL("_Z3foox", code->GetName());
        BOOST_CHECK_EQUAL(11, code->GetSize());
        const auto &buffer = code->GetBuffer();
        BOOST_CHECK_EQUAL(11, buffer.size());
        byte expected[11] = {
                0x55,
                0x48, 0x89, 0xe5,
                0x48, 0x89, 0x4d, 0x10,
                0x90,
                0x5d,
                0xc3};
        BOOST_CHECK(VerifyByteVector(buffer, expected, 11));
    }

    BOOST_AUTO_TEST_CASE(TEST03) {
        const std::string source = "func foo(a:int, b:int) {}";
        ParserDriver driver(source, "foo.hoo");
        auto module = driver.BuildModule();
        BOOST_ASSERT(module->Success());
        auto unit = module->GetUnit();
        auto func = (FunctionDefinition *) (*unit->GetItems().begin());
        BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
        WindowsX64Emitter emitter(unit);
        auto code = emitter.GenerateCode(func);
        BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
        BOOST_CHECK_EQUAL("_Z3fooxx", code->GetName());
        BOOST_CHECK_EQUAL(15, code->GetSize());
        const auto &buffer = code->GetBuffer();
        BOOST_CHECK_EQUAL(15, buffer.size());
        byte expected[15] = {
                0x55,
                0x48, 0x89, 0xe5,
                0x48, 0x89, 0x4d, 0x10,
                0x48, 0x89, 0x55, 0x18,
                0x90,
                0x5d,
                0xc3};
        BOOST_CHECK(VerifyByteVector(buffer, expected, 15));
    }

    BOOST_AUTO_TEST_CASE(TEST04) {
        const std::string source = "func foo(a:int, b:int, c:int) {}";
        ParserDriver driver(source, "foo.hoo");
        auto module = driver.BuildModule();
        BOOST_ASSERT(module->Success());
        auto unit = module->GetUnit();
        auto func = (FunctionDefinition *) (*unit->GetItems().begin());
        BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
        WindowsX64Emitter emitter(unit);
        auto code = emitter.GenerateCode(func);
        BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
        BOOST_CHECK_EQUAL("_Z3fooxxx", code->GetName());
        BOOST_CHECK_EQUAL(19, code->GetSize());
        const auto &buffer = code->GetBuffer();
        BOOST_CHECK_EQUAL(19, buffer.size());
        byte expected[19] = {
                0x55,
                0x48, 0x89, 0xe5,
                0x48, 0x89, 0x4d, 0x10,
                0x48, 0x89, 0x55, 0x18,
                0x4c, 0x89, 0x45, 0x20,
                0x90,
                0x5d,
                0xc3};
        BOOST_CHECK(VerifyByteVector(buffer, expected, 19));
    }

    BOOST_AUTO_TEST_CASE(TEST05) {
        const std::string source = "func foo(a:int, b:int, c:int, d:int) {}";
        ParserDriver driver(source, "foo.hoo");
        auto module = driver.BuildModule();
        BOOST_ASSERT(module->Success());
        auto unit = module->GetUnit();
        auto func = (FunctionDefinition *) (*unit->GetItems().begin());
        BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
        WindowsX64Emitter emitter(unit);
        auto code = emitter.GenerateCode(func);
        BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
        BOOST_CHECK_EQUAL("_Z3fooxxxx", code->GetName());
        BOOST_CHECK_EQUAL(23, code->GetSize());
        const auto &buffer = code->GetBuffer();
        BOOST_CHECK_EQUAL(23, buffer.size());
        byte expected[23] = {
                0x55,
                0x48, 0x89, 0xe5,
                0x48, 0x89, 0x4d, 0x10,
                0x48, 0x89, 0x55, 0x18,
                0x4c, 0x89, 0x45, 0x20,
                0x4c, 0x89, 0x4d, 0x28,
                0x90,
                0x5d,
                0xc3};
        BOOST_CHECK(VerifyByteVector(buffer, expected, 23));
    }

    BOOST_AUTO_TEST_CASE(TEST06) {
        const std::string source = "func foo(a: double) {}";
        ParserDriver driver(source, "foo.hoo");
        auto module = driver.BuildModule();
        BOOST_ASSERT(module->Success());
        auto unit = module->GetUnit();
        auto func = (FunctionDefinition *) (*unit->GetItems().begin());
        BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
        WindowsX64Emitter emitter(unit);
        auto code = emitter.GenerateCode(func);
        BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
        BOOST_CHECK_EQUAL("_Z3food", code->GetName());
        const auto &buffer = code->GetBuffer();
        byte expected[12] = {
                0x55,
                0x48, 0x89, 0xe5,
                0xf2, 0x0f, 0x11, 0x45, 0x10,
                0x90,
                0x5d,
                0xc3};
        BOOST_CHECK(VerifyByteVector(buffer, expected, 12));
    }

    BOOST_AUTO_TEST_CASE(TEST07) {
        const std::string source = "func foo(a: double, b: double) {}";
        ParserDriver driver(source, "foo.hoo");
        auto module = driver.BuildModule();
        BOOST_ASSERT(module->Success());
        auto unit = module->GetUnit();
        auto func = (FunctionDefinition *) (*unit->GetItems().begin());
        BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
        WindowsX64Emitter emitter(unit);
        auto code = emitter.GenerateCode(func);
        BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
        BOOST_CHECK_EQUAL("_Z3foodd", code->GetName());
        const auto &buffer = code->GetBuffer();
        byte expected[17] = {
                0x55,
                0x48, 0x89, 0xe5,
                0xf2, 0x0f, 0x11, 0x45, 0x10,
                0xf2, 0x0f, 0x11, 0x4d, 0x18,
                0x90,
                0x5d,
                0xc3};
        BOOST_CHECK(VerifyByteVector(buffer, expected, 17));
    }

    BOOST_AUTO_TEST_CASE(TEST08) {
        const std::string source = "func foo(a: double, b: double, c: double) {}";
        ParserDriver driver(source, "foo.hoo");
        auto module = driver.BuildModule();
        BOOST_ASSERT(module->Success());
        auto unit = module->GetUnit();
        auto func = (FunctionDefinition *) (*unit->GetItems().begin());
        BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
        WindowsX64Emitter emitter(unit);
        auto code = emitter.GenerateCode(func);
        BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
        BOOST_CHECK_EQUAL("_Z3fooddd", code->GetName());
        const auto &buffer = code->GetBuffer();
        byte expected[22] = {
                0x55,
                0x48, 0x89, 0xe5,
                0xf2, 0x0f, 0x11, 0x45, 0x10,
                0xf2, 0x0f, 0x11, 0x4d, 0x18,
                0xf2, 0x0f, 0x11, 0x55, 0x20,
                0x90,
                0x5d,
                0xc3};
        BOOST_CHECK(VerifyByteVector(buffer, expected, 22));
    }

    BOOST_AUTO_TEST_CASE(TEST09) {
        const std::string source = "func foo(a: double, b: double, c: double, d:double) {}";
        ParserDriver driver(source, "foo.hoo");
        auto module = driver.BuildModule();
        BOOST_ASSERT(module->Success());
        auto unit = module->GetUnit();
        auto func = (FunctionDefinition *) (*unit->GetItems().begin());
        BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
        WindowsX64Emitter emitter(unit);
        auto code = emitter.GenerateCode(func);
        BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
        BOOST_CHECK_EQUAL("_Z3foodddd", code->GetName());
        const auto &buffer = code->GetBuffer();
        byte expected[27] = {
                0x55,
                0x48, 0x89, 0xe5,
                0xf2, 0x0f, 0x11, 0x45, 0x10,
                0xf2, 0x0f, 0x11, 0x4d, 0x18,
                0xf2, 0x0f, 0x11, 0x55, 0x20,
                0xf2, 0x0f, 0x11, 0x5d, 0x28,
                0x90,
                0x5d,
                0xc3};
        BOOST_CHECK(VerifyByteVector(buffer, expected, 27));
    }

    BOOST_AUTO_TEST_CASE(TEST10) {
        const std::string source = "func foo(a: int, b: double, c: int, d:double) {}";
        ParserDriver driver(source, "foo.hoo");
        auto module = driver.BuildModule();
        BOOST_ASSERT(module->Success());
        auto unit = module->GetUnit();
        auto func = (FunctionDefinition *) (*unit->GetItems().begin());
        BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
        WindowsX64Emitter emitter(unit);
        auto code = emitter.GenerateCode(func);
        BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
        BOOST_CHECK_EQUAL("_Z3fooxdxd", code->GetName());
        const auto &buffer = code->GetBuffer();
        byte expected[25] = {
                0x55,
                0x48, 0x89, 0xe5,
                0x48, 0x89, 0x4d, 0x10,
                0xf2, 0x0f, 0x11, 0x4d, 0x18,
                0x4c, 0x89, 0x45, 0x20,
                0xf2, 0x0f, 0x11, 0x5d, 0x28,
                0x90,
                0x5d,
                0xc3};
        BOOST_CHECK(VerifyByteVector(buffer, expected, 25));
    }

    BOOST_AUTO_TEST_CASE(TEST11) {
        const std::string source = "func foo(a: double, b: int, c: double, d:int) {}";
        ParserDriver driver(source, "foo.hoo");
        auto module = driver.BuildModule();
        BOOST_ASSERT(module->Success());
        auto unit = module->GetUnit();
        auto func = (FunctionDefinition *) (*unit->GetItems().begin());
        BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
        WindowsX64Emitter emitter(unit);
        auto code = emitter.GenerateCode(func);
        BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
        BOOST_CHECK_EQUAL("_Z3foodxdx", code->GetName());
        const auto &buffer = code->GetBuffer();
        byte expected[25] = {
                0x55,
                0x48, 0x89, 0xe5,
                0xf2, 0x0f, 0x11, 0x45, 0x10,
                0x48, 0x89, 0x55, 0x18,
                0xf2, 0x0f, 0x11, 0x55, 0x20,
                0x4c, 0x89, 0x4d, 0x28,
                0x90,
                0x5d,
                0xc3};
        BOOST_CHECK(VerifyByteVector(buffer, expected, 25));
    }

BOOST_AUTO_TEST_SUITE_END()