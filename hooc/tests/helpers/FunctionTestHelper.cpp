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

#include "FunctionTestHelper.hh"

#include <boost/test/unit_test.hpp>

FunctionTestHelper::FunctionTestHelper(FunctionDefinition *func) :
        _func(func),
        _mangler(),
        _emitter_win64(func, EMITTER_WIN64),
        _emitter_linux64(func, EMITTER_LINUX64),
        _code_win64(nullptr),
        _code_linux64(nullptr) {
    BOOST_CHECK_MESSAGE(nullptr != func, "Function definition must not be null.");
    if (nullptr != func) {
        this->_code_win64 = this->_emitter_win64.GenerateCode();
        this->_code_linux64 = this->_emitter_linux64.GenerateCode();
    }
}

void FunctionTestHelper::TestName(const std::string &name) {
    BOOST_CHECK_MESSAGE(this->_func->GetDeclaration()->GetName() == name,
                        "Name of the function doesn't match.");
}

void FunctionTestHelper::TestMangledName(const std::string &mangled_name) {
    BOOST_CHECK_MESSAGE(nullptr != _func, "Function definition must not be null.");
    if (nullptr != this->_func) {
        auto mangled = this->_mangler.Mangle(this->_func->GetDeclaration());
        BOOST_CHECK_MESSAGE(mangled == mangled_name, "Mangled name doesn't match.");
    }
}

bool FunctionTestHelper::TestCodeWin64(byte *code, size_t size) {
    return TestCode(this->_code_win64, code, size);
}

bool FunctionTestHelper::TestCodeLinux64(byte *code, size_t size) {
    return TestCode(this->_code_linux64, code, size);
}

bool FunctionTestHelper::TestCode(Code *code, byte *buffer, size_t size) {
    BOOST_CHECK_MESSAGE(code->GetSize() == size, "Size of generated code doesn't match.");
    if(size != code->GetSize()) {
        return false;
    }

    if (size == code->GetSize()) {
        auto code_buffer = code->GetBytes();
        for (size_t index = 0; index < size; index++) {
            BOOST_CHECK_MESSAGE(code_buffer[index] == buffer[index], "Byte at " << index << "doesn't match.");
            if(code_buffer[index] != buffer[index]) {
                return false;
            }
        }
    }

    return true;
}

bool FunctionTestHelper::TestStack(size_t depth, size_t count) {
    BOOST_CHECK_MESSAGE(nullptr != this->_func, "Function definition must not be null.");
    if(nullptr == this->_func) {
        return false;
    }

    auto context = this->_emitter_win64.GetFunctionContext();
    BOOST_CHECK_MESSAGE(nullptr != context, "Context is null.");
    if(nullptr == context) {
        return false;
    }

    BOOST_CHECK_MESSAGE(depth == context->GetDepth(), "Invalid stack depth for Win64");
    if(depth != context->GetDepth()) {
        return false;
    }
    BOOST_CHECK_MESSAGE(count == context->GetItems().size(), "Invalid stack item count for Win64");
    if(count != context->GetItems().size()) {
        return false;
    }

    context = this->_emitter_linux64.GetFunctionContext();
    BOOST_CHECK_MESSAGE(depth == context->GetDepth(), "Invalid stack depth for Linux64");
    if(depth != context->GetDepth()) {
        return false;
    }
    BOOST_CHECK_MESSAGE(count == context->GetItems().size(), "Invalid stack item count for Linux64");
    if(count != context->GetItems().size()) {
        return false;
    }
    return true;
}

bool FunctionTestHelper::TestStackItem(size_t index, const std::string& name) {
    BOOST_CHECK_MESSAGE(nullptr != this->_func, "Function definition must not be null.");
    if(nullptr == this->_func) {
        return false;
    }

    auto context = this->_emitter_win64.GetFunctionContext();
    BOOST_CHECK_MESSAGE(nullptr != context, "Context must not be null.");
    if(nullptr == context) {
        return false;
    }

    const auto &items = context->GetItems();
    BOOST_CHECK_MESSAGE(index < items.size(), "No item available at given index.");
    if(index >= items.size()) {
        return false;
    }

    auto item = GetStackItem(items, 0);
    const std::string& item_name = item.GetName();
    BOOST_CHECK_MESSAGE(name == item_name, "Invalid name of the stack item.");
    if(name != item_name) {
        return false;
    }

    return true;
}

FunctionTestHelper::~FunctionTestHelper() {
    delete this->_code_win64;
    delete this->_code_linux64;
}
