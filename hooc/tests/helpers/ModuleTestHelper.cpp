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

#include "ModuleTestHelper.hh"
#include <boost/test/unit_test.hpp>

ModuleTestHelper::ModuleTestHelper(const std::string &source, const std::string &source_file) :
        _driver(source, source_file), _module(_driver.BuildModule()) {
    if (!_module->Success()) {
        delete this->_module;
        this->_module = nullptr;
        this->_unit = nullptr;
    } else {
        this->_unit = this->_module->GetUnit();
        auto items = this->_unit->GetItems();
        this->_items.insert(this->_items.begin(), items.begin(), items.end());
    }
}

const Unit *ModuleTestHelper::GetUnit() const {
    BOOST_CHECK_MESSAGE(nullptr != this->_module, "Building module is failed.");
    BOOST_CHECK_MESSAGE(nullptr != this->_unit, "Unit is not available since module building is failed.");
    return _unit;
}

size_t ModuleTestHelper::GetUnitItemsCount() const {
    BOOST_CHECK_MESSAGE(nullptr != this->_module, "Building module is failed.");
    BOOST_CHECK_MESSAGE(nullptr != this->_unit, "Unit is not available since module building is failed.");
    const auto &items = this->_unit->GetItems();
    return items.size();
}

UnitItem *ModuleTestHelper::GetUnitItem(size_t index) {
    BOOST_CHECK_MESSAGE(index < this->_items.size(), "There is not enough unit item.");
    if (index < this->_items.size()) {
        return this->_items[index];
    }
    return nullptr;
}

Definition *ModuleTestHelper::GetDefinition(size_t index) {
    auto item = this->GetUnitItem(index);
    if (nullptr != item) {
        BOOST_CHECK_MESSAGE(UNIT_ITEM_DEFINITION == item->GetUnitItemType(), "Unit item is not a definition.");
        if (item->GetUnitItemType() == UNIT_ITEM_DEFINITION) {
            return (Definition *) item;
        }
    }
    return nullptr;
}

FunctionDefinition *ModuleTestHelper::GetFunctionDefinition(size_t index) {
    auto def = this->GetDefinition(index);
    if (nullptr != def) {
        BOOST_CHECK_MESSAGE(DEFINITION_FUNCTION == def->GetDefinitionType(),
                            "Definition is not a function definition.");
        if (def->GetDefinitionType() == DEFINITION_FUNCTION) {
            return (FunctionDefinition *) def;
        }
    }
    return nullptr;
}

FunctionTestHelper ModuleTestHelper::GetFunctionTestHelper(size_t index) {
    auto func = this->GetFunctionDefinition(index);
    BOOST_CHECK(nullptr != func);
    return FunctionTestHelper(func);
}

ModuleTestHelper::~ModuleTestHelper() {
    delete this->_module;
}
