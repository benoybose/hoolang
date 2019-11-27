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
#include "helpers/ModuleTestHelper.hh"

#include <boost/test/unit_test.hpp>
#include <compiler/ParserDriver.hh>
#include <ast/FunctionDefinition.hh>
#include <emitter/CodeType.hh>
#include <emitter/x86/X86Instruction.hh>
#include <misc/Utility.hh>
#include <emitter/x86/X86FuncEmitter.hh>
#include <emitter/EmitterConfig.hh>
#include <ast/BasicDataTypes.hh>

using namespace hooc::emitter::x86;
using namespace hooc::compiler;
using namespace hooc::ast;
using namespace hooc::emitter;
using namespace hooc::misc;

BOOST_AUTO_TEST_SUITE(X86EmitterTest)

BOOST_AUTO_TEST_CASE(TEST01)
{
    const std::string source = "func foo() {}";
    ModuleTestHelper helper(source, "foo.hoo");
    auto func = helper.GetFunctionTestHelper(0);
    BOOST_CHECK(func.IsNamed("foo"));
    BOOST_CHECK(func.IsMangled("_Z3foov"));
    BOOST_CHECK(func.TestStack(0, 0));
    byte_vector expected_win64{0x55,
                               0x48, 0x89, 0xe5,
                               0x90,
                               0x5d,
                               0xc3};
    BOOST_CHECK(func.TestCodeWin64(expected_win64));
    byte_vector expected_linux{0x55,
                               0x48, 0x89, 0xE5,
                               0x90,
                               0x5D,
                               0xC3};
    BOOST_CHECK(func.TestCodeLinux64(expected_linux));
}

BOOST_AUTO_TEST_CASE(TEST02)
{
    const std::string source = "func foo(a:int) {}";
    ModuleTestHelper helper(source, "foo.hoo");
    auto func = helper.GetFunctionTestHelper(0);
    BOOST_CHECK(func.IsNamed("foo"));
    BOOST_CHECK(func.IsMangled("_Z3foox"));
    BOOST_CHECK(func.TestStack(0, 1));
    BOOST_CHECK(func.TestStackItem(0, "a", STACK_ITEM_ARGUMENT, TYPE_SPEC_BASIC, NAME_INT));
    byte_vector expected_win64{0x55,
                               0x48, 0x89, 0xe5,
                               0x48, 0x89, 0x4d, 0x10,
                               0x90,
                               0x5d,
                               0xc3};
    BOOST_CHECK(func.TestCodeWin64(expected_win64));
    byte_vector expected_linux64{0x55,
                                 0x48, 0x89, 0xe5,
                                 0x48, 0x89, 0x7d, 0xf8,
                                 0x90,
                                 0x5d,
                                 0xc3};
    BOOST_CHECK(func.TestCodeLinux64(expected_linux64));
}

BOOST_AUTO_TEST_CASE(TEST03)
{
    const std::string source = "func foo(a:int, b:int) {}";
    ModuleTestHelper helper(source, "foo.hoo");
    auto foo = helper.GetFunctionTestHelper(0);
    BOOST_CHECK(foo.IsNamed("foo"));
    BOOST_CHECK(foo.IsMangled("_Z3fooxx"));
    BOOST_CHECK(foo.TestStack(0, 2));
    BOOST_CHECK(foo.TestStackItem(0, "a", STACK_ITEM_ARGUMENT, TYPE_SPEC_BASIC, NAME_INT));
    BOOST_CHECK(foo.TestStackItem(1, "b", STACK_ITEM_ARGUMENT, TYPE_SPEC_BASIC, NAME_INT));
    foo.TestCodeWin64({0x55,
                       0x48, 0x89, 0xe5,
                       0x48, 0x89, 0x4d, 0x10,
                       0x48, 0x89, 0x55, 0x18,
                       0x90,
                       0x5d,
                       0xc3});
    foo.TestCodeLinux64({0x55,
                         0x48, 0x89, 0xe5,
                         0x48, 0x89, 0x7d, 0xf8,
                         0x48, 0x89, 0x75, 0xf0,
                         0x90,
                         0x5d,
                         0xc3});
}

BOOST_AUTO_TEST_CASE(TEST04)
{
    // const std::string source = "func foo(a:int, b:int, c:int) {}";
    // ParserDriver driver(source, "foo.hoo");
    // auto module = driver.BuildModule();
    // BOOST_ASSERT(module->Success());
    // auto unit = module->GetUnit();
    // auto func = (FunctionDefinition *)(*unit->GetItems().begin());
    // BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
    // X86FuncEmitter emitter(func, EMITTER_WIN64);
    // auto code = emitter.GenerateCode();
    // BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
    // BOOST_CHECK_EQUAL("_Z3fooxxx", code->GetName());
    // BOOST_CHECK_EQUAL(19, code->GetSize());
    // const auto &buffer = code->GetBuffer();
    // BOOST_CHECK_EQUAL(19, buffer.size());
    // byte expected[19] = {
    //     0x55,
    //     0x48, 0x89, 0xe5,
    //     0x48, 0x89, 0x4d, 0x10,
    //     0x48, 0x89, 0x55, 0x18,
    //     0x4c, 0x89, 0x45, 0x20,
    //     0x90,
    //     0x5d,
    //     0xc3};
    // BOOST_CHECK(VerifyByteVector(buffer, expected, 19));
}

BOOST_AUTO_TEST_CASE(TEST05)
{
    // const std::string source = "func foo(a:int, b:int, c:int, d:int) {}";
    // ParserDriver driver(source, "foo.hoo");
    // auto module = driver.BuildModule();
    // BOOST_ASSERT(module->Success());
    // auto unit = module->GetUnit();
    // auto func = (FunctionDefinition *)(*unit->GetItems().begin());
    // BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
    // X86FuncEmitter emitter(func, EMITTER_WIN64);
    // auto code = emitter.GenerateCode();
    // BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
    // BOOST_CHECK_EQUAL("_Z3fooxxxx", code->GetName());
    // BOOST_CHECK_EQUAL(23, code->GetSize());
    // const auto &buffer = code->GetBuffer();
    // BOOST_CHECK_EQUAL(23, buffer.size());
    // byte expected[23] = {
    //     0x55,
    //     0x48, 0x89, 0xe5,
    //     0x48, 0x89, 0x4d, 0x10,
    //     0x48, 0x89, 0x55, 0x18,
    //     0x4c, 0x89, 0x45, 0x20,
    //     0x4c, 0x89, 0x4d, 0x28,
    //     0x90,
    //     0x5d,
    //     0xc3};
    // BOOST_CHECK(VerifyByteVector(buffer, expected, 23));
}

BOOST_AUTO_TEST_CASE(TEST06)
{
    // const std::string source = "func foo(a: double) {}";
    // ParserDriver driver(source, "foo.hoo");
    // auto module = driver.BuildModule();
    // BOOST_ASSERT(module->Success());
    // auto unit = module->GetUnit();
    // auto func = (FunctionDefinition *)(*unit->GetItems().begin());
    // BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
    // X86FuncEmitter emitter(func, EMITTER_WIN64);
    // auto code = emitter.GenerateCode();
    // BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
    // BOOST_CHECK_EQUAL("_Z3food", code->GetName());
    // const auto &buffer = code->GetBuffer();
    // byte expected[12] = {
    //     0x55,
    //     0x48, 0x89, 0xe5,
    //     0xf2, 0x0f, 0x11, 0x45, 0x10,
    //     0x90,
    //     0x5d,
    //     0xc3};
    // BOOST_CHECK(VerifyByteVector(buffer, expected, 12));
}

BOOST_AUTO_TEST_CASE(TEST07)
{
    // const std::string source = "func foo(a: double, b: double) {}";
    // ParserDriver driver(source, "foo.hoo");
    // auto module = driver.BuildModule();
    // BOOST_ASSERT(module->Success());
    // auto unit = module->GetUnit();
    // auto func = (FunctionDefinition *)(*unit->GetItems().begin());
    // BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
    // X86FuncEmitter emitter(func, EMITTER_WIN64);
    // auto code = emitter.GenerateCode();
    // BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
    // BOOST_CHECK_EQUAL("_Z3foodd", code->GetName());
    // const auto &buffer = code->GetBuffer();
    // byte expected[17] = {
    //     0x55,
    //     0x48, 0x89, 0xe5,
    //     0xf2, 0x0f, 0x11, 0x45, 0x10,
    //     0xf2, 0x0f, 0x11, 0x4d, 0x18,
    //     0x90,
    //     0x5d,
    //     0xc3};
    // BOOST_CHECK(VerifyByteVector(buffer, expected, 17));
}

BOOST_AUTO_TEST_CASE(TEST08)
{
    // const std::string source = "func foo(a: double, b: double, c: double) {}";
    // ParserDriver driver(source, "foo.hoo");
    // auto module = driver.BuildModule();
    // BOOST_ASSERT(module->Success());
    // auto unit = module->GetUnit();
    // auto func = (FunctionDefinition *)(*unit->GetItems().begin());
    // BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
    // X86FuncEmitter emitter(func, EMITTER_WIN64);
    // auto code = emitter.GenerateCode();
    // BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
    // BOOST_CHECK_EQUAL("_Z3fooddd", code->GetName());
    // const auto &buffer = code->GetBuffer();
    // byte expected[22] = {
    //     0x55,
    //     0x48, 0x89, 0xe5,
    //     0xf2, 0x0f, 0x11, 0x45, 0x10,
    //     0xf2, 0x0f, 0x11, 0x4d, 0x18,
    //     0xf2, 0x0f, 0x11, 0x55, 0x20,
    //     0x90,
    //     0x5d,
    //     0xc3};
    // BOOST_CHECK(VerifyByteVector(buffer, expected, 22));
}

BOOST_AUTO_TEST_CASE(TEST09)
{
    // const std::string source = "func foo(a: double, b: double, c: double, d:double) {}";
    // ParserDriver driver(source, "foo.hoo");
    // auto module = driver.BuildModule();
    // BOOST_ASSERT(module->Success());
    // auto unit = module->GetUnit();
    // auto func = (FunctionDefinition *)(*unit->GetItems().begin());
    // BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
    // X86FuncEmitter emitter(func, EMITTER_WIN64);
    // auto code = emitter.GenerateCode();
    // BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
    // BOOST_CHECK_EQUAL("_Z3foodddd", code->GetName());
    // const auto &buffer = code->GetBuffer();
    // byte expected[27] = {
    //     0x55,
    //     0x48, 0x89, 0xe5,
    //     0xf2, 0x0f, 0x11, 0x45, 0x10,
    //     0xf2, 0x0f, 0x11, 0x4d, 0x18,
    //     0xf2, 0x0f, 0x11, 0x55, 0x20,
    //     0xf2, 0x0f, 0x11, 0x5d, 0x28,
    //     0x90,
    //     0x5d,
    //     0xc3};
    // BOOST_CHECK(VerifyByteVector(buffer, expected, 27));
}

BOOST_AUTO_TEST_CASE(TEST10)
{
    // const std::string source = "func foo(a: int, b: double, c: int, d:double) {}";
    // ParserDriver driver(source, "foo.hoo");
    // auto module = driver.BuildModule();
    // BOOST_ASSERT(module->Success());
    // auto unit = module->GetUnit();
    // auto func = (FunctionDefinition *)(*unit->GetItems().begin());
    // BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
    // X86FuncEmitter emitter(func, EMITTER_WIN64);
    // auto code = emitter.GenerateCode();
    // BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
    // BOOST_CHECK_EQUAL("_Z3fooxdxd", code->GetName());
    // const auto &buffer = code->GetBuffer();
    // byte expected[25] = {
    //     0x55,
    //     0x48, 0x89, 0xe5,
    //     0x48, 0x89, 0x4d, 0x10,
    //     0xf2, 0x0f, 0x11, 0x4d, 0x18,
    //     0x4c, 0x89, 0x45, 0x20,
    //     0xf2, 0x0f, 0x11, 0x5d, 0x28,
    //     0x90,
    //     0x5d,
    //     0xc3};
    // BOOST_CHECK(VerifyByteVector(buffer, expected, 25));
}

BOOST_AUTO_TEST_CASE(TEST11)
{
    // const std::string source = "func foo(a: double, b: int, c: double, d:int) {}";
    // ParserDriver driver(source, "foo.hoo");
    // auto module = driver.BuildModule();
    // BOOST_ASSERT(module->Success());
    // auto unit = module->GetUnit();
    // auto func = (FunctionDefinition *)(*unit->GetItems().begin());
    // BOOST_ASSERT("foo" == func->GetDeclaration()->GetName());
    // X86FuncEmitter emitter(func, EMITTER_WIN64);
    // auto code = emitter.GenerateCode();
    // BOOST_CHECK_EQUAL(CODE_TYPE_FUNCTION, code->GetType());
    // BOOST_CHECK_EQUAL("_Z3foodxdx", code->GetName());
    // const auto &buffer = code->GetBuffer();
    // byte expected[25] = {
    //     0x55,
    //     0x48, 0x89, 0xe5,
    //     0xf2, 0x0f, 0x11, 0x45, 0x10,
    //     0x48, 0x89, 0x55, 0x18,
    //     0xf2, 0x0f, 0x11, 0x55, 0x20,
    //     0x4c, 0x89, 0x4d, 0x28,
    //     0x90,
    //     0x5d,
    //     0xc3};
    // BOOST_CHECK(VerifyByteVector(buffer, expected, 25));
}

BOOST_AUTO_TEST_SUITE_END()