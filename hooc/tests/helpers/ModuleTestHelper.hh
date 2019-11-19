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

#ifndef HOOLANG_MODULETESTHELPER_HH
#define HOOLANG_MODULETESTHELPER_HH

#include "FunctionTestHelper.hh"

#include <compiler/ParserDriver.hh>
#include <ast/UnitItem.hh>
#include <vector>
#include <ast/Definition.hh>
#include <ast/FunctionDefinition.hh>

using namespace hooc::compiler;
using namespace hooc::ast;

class ModuleTestHelper {
public:
    ModuleTestHelper(const std::string &source, const std::string &source_file);

private:
    ParserDriver _driver;
    Module *_module;
    const Unit *_unit;
    std::vector<UnitItem*> _items;

public:
    const Unit *GetUnit() const;
    size_t GetUnitItemsCount() const;
    UnitItem* GetUnitItem(size_t index);
    Definition* GetDefinition(size_t index);
    FunctionDefinition* GetFunctionDefinition(size_t index);
    FunctionTestHelper GetFunctionTestHelper(size_t index);


public:
    virtual ~ModuleTestHelper();


};


#endif //HOOLANG_MODULETESTHELPER_HH
