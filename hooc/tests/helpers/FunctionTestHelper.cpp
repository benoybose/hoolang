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
#include <misc/Utility.hh>
#include <ast/BasicDataTypes.hh>

#include <boost/test/unit_test.hpp>

using namespace hooc::misc;

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

bool FunctionTestHelper::HasNames(const std::string& name, const std::string& mangled_name) {
    BOOST_CHECK(IsNamed(name));
    if(!IsNamed(name)) {
        return false;
    }
    BOOST_CHECK(IsMangled(mangled_name));
    if(!IsMangled(mangled_name)) {
        return false;
    }
    return true;
}

bool FunctionTestHelper::IsNamed(const std::string &name) {
    auto name_original = this->_func->GetDeclaration()->GetName();
    BOOST_CHECK_MESSAGE(name_original == name,
                        "Name of the function doesn't match. (" << name_original << " != " << name << ")");
    return (name_original == name);
}

bool FunctionTestHelper::IsMangled(const std::string &mangled_name) {
    BOOST_CHECK_MESSAGE(nullptr != _func, "Function definition must not be null.");
    if (nullptr == _func){
        return false;
    }

    auto mangled = this->_mangler.Mangle(this->_func->GetDeclaration());
    BOOST_CHECK_MESSAGE(mangled == mangled_name,
                        "Mangled name doesn't match. (" << mangled << "!=" << mangled_name << ")");
    BOOST_CHECK_MESSAGE(nullptr != this->_code_win64,
                        "Win64 code must not be null.");
    if (nullptr == this->_code_win64){
        return false;
    }
    BOOST_CHECK_MESSAGE(this->_code_win64->GetName() == mangled,
                        "Mangled name doesn't match for Win64.");
    if (this->_code_win64->GetName() != mangled){
        return false;
    }
    BOOST_CHECK_MESSAGE(nullptr != this->_code_linux64,
                        "Linux64 code must not be null.");
    if (nullptr == this->_code_linux64){
        return false;
    }
    BOOST_CHECK_MESSAGE(this->_code_linux64->GetName() == mangled,
                        "Mangled name doesn't match for Linux64.");
    if (this->_code_linux64->GetName() != mangled){
        return false;
    }
    return true;
}

bool FunctionTestHelper::TestCodeWin64(byte_vector expected_win64) {
    return TestCode(this->_code_win64, expected_win64);
}

bool FunctionTestHelper::TestCodeLinux64(byte_vector expected_linux64) {
    return TestCode(this->_code_linux64, expected_linux64);
}

bool FunctionTestHelper::TestCode(Code *code, byte_vector buffer) {
    auto size = buffer.size();
    BOOST_CHECK_MESSAGE(code->GetSize() == size,
                        "Size of generated code doesn't match. (" << code->GetSize() << "!=" << size << ")");
    if(size != code->GetSize()) {
        return false;
    }

    if (size == code->GetSize()) {
        auto code_buffer = code->GetBytes();
        for (size_t index = 0; index < size; index++) {
            BOOST_CHECK_MESSAGE(code_buffer[index] == buffer[index],
                                "Byte at (" << index << ") doesn't match. ("
                                            << Utility::ToHex(code_buffer[index]) << " != " 
                                            << Utility::ToHex(buffer[index]) << ")");
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

    BOOST_CHECK_MESSAGE(depth == context->GetDepth(),
                        "Invalid stack depth for Win64. (" << depth << "!=" << context->GetDepth() << ")");
    if(depth != context->GetDepth()) {
        return false;
    }
    BOOST_CHECK_MESSAGE(count == context->GetItems().size(), 
                        "Invalid stack item count for Win64. (" << count << "!=" << context->GetItems().size() << ")");
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

bool FunctionTestHelper::TestStackItem(const FuncEmitterContext* context, 
                                size_t index, const std::string& name, 
                                int64_t position, 
                                const StackItemType stack_item_type,
                                const TypeSpecificationType type_specification_type,
                                const std::string &type_name) {
    BOOST_CHECK_MESSAGE(nullptr != context, "Context must not be null.");
    if(nullptr == context) {
        return false;
    }

    const auto &items = context->GetItems();
    BOOST_CHECK_MESSAGE(index < items.size(), "No item available at given index.");
    if(index >= items.size()) {
        return false;
    }

    auto item = GetStackItem(items, index);
    const std::string& item_name = item.GetName();
    BOOST_CHECK_MESSAGE(name == item_name, "Invalid name of the stack item.");
    if(name != item_name) {
        return false;
    }

    const auto item_position = item.GetPosition();
    BOOST_CHECK_MESSAGE(position == item_position, 
        "Invalid position of the stack item. (position=" << position << ")");
    if(position != item_position) {
        return false;
    }

    const auto item_stack_item_type = item.GetStakcItemType();
    BOOST_CHECK_MESSAGE(stack_item_type == item_stack_item_type, "Stack item type doesn't match.");
    if(stack_item_type != item_stack_item_type) {
        return false;
    }

    const auto item_type_Specification_type = item.GetTypeSpecification()->GetType();
    BOOST_CHECK_MESSAGE(type_specification_type == item_type_Specification_type, "Type specific type doesn't match.");
    if(type_specification_type != item_type_Specification_type) {
        return false;
    }

    const auto &item_type_name = item.GetTypeSpecification()->GetName();
    BOOST_CHECK_MESSAGE(type_name == item_type_name, "Type name doesn't match.");
    if(type_name != item_type_name) {
        return false;
    }

    return true;
}

bool FunctionTestHelper::TestIntItem(size_t index, const std::string &name, const int offset) {
    // return TestStackItem(index, name, STACK_ITEM_ARGUMENT, TYPE_SPEC_BASIC, NAME_INT);
    return false;
}

bool FunctionTestHelper::TestDoubleItem(size_t index, const std::string &name, const int offset) {
    // return TestStackItem(index, name, STACK_ITEM_ARGUMENT, TYPE_SPEC_BASIC, NAME_DOUBLE);
    return false;
}

bool FunctionTestHelper::TestCode(byte_vector expected_win64, byte_vector expected_linux64) {
    if(!TestCodeWin64(expected_win64)) {
        BOOST_CHECK_MESSAGE(false, "Windows 64 code doesn't match.");
        return false;
    }
    if(!TestCodeLinux64(expected_linux64)) {
        BOOST_CHECK_MESSAGE(false, "Linux 64 code doesn't match.");
        return false;
    }
    return true;
}

FunctionTestHelper::~FunctionTestHelper() {
    delete this->_code_win64;
    delete this->_code_linux64;
}