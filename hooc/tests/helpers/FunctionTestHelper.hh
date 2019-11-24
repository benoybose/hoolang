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

#ifndef HOOLANG_FUNCTIONTESTHELPER_HH
#define HOOLANG_FUNCTIONTESTHELPER_HH

#include <ast/FunctionDefinition.hh>
#include <emitter/NameMangler.hh>
#include <emitter/x86/X86FuncEmitter.hh>
#include <emitter/EmitterDefinitions.hh>
#include <cstdint>

using namespace hooc::ast;
using namespace hooc::emitter;
using namespace hooc::emitter::x86;
using namespace std;

class FunctionTestHelper {
public:
    explicit FunctionTestHelper(FunctionDefinition *func);

private:
    FunctionDefinition *_func;
    NameMangler _mangler;
    X86FuncEmitter _emitter_win64;
    X86FuncEmitter _emitter_linux64;
    Code *_code_win64;
    Code *_code_linux64;

public:
    void TestName(const std::string &name);

    void TestMangledName(const std::string &mangled_name);

    bool TestCodeWin64(byte *code, size_t size);

    bool TestCodeLinux64(byte *code, size_t size);

    bool TestStack(size_t depth, size_t count);

public:
    static bool TestCode(Code *code, byte *buffer, size_t size);

public:
    virtual ~FunctionTestHelper();

public:

};


#endif //HOOLANG_FUNCTIONTESTHELPER_HH
