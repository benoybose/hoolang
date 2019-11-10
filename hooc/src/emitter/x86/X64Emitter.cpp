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


#include <emitter/x86/X86Definitions.hh>
#include <emitter/x86/X64Emitter.hh>
#include <misc/Utility.hh>
#include <ast/BasicDataTypes.hh>
#include <ast/Definition.hh>
#include <ast/FunctionDefinition.hh>
#include <ast/CompoundStatement.hh>
#include <ast/BasicDataTypeSpecification.hh>
#include <emitter/x86/X64FunctionEmitter.hh>

using namespace std;
using namespace hooc::misc;

namespace hooc {
    namespace emitter {
        namespace x86 {
            X64Emitter::X64Emitter(const Unit *unit,
                    EmitterArchType arch,
                    EmitterOSType os):
                    EmitterBase(unit, arch, os) {
            }

            std::list<Code *> X64Emitter::GenerateCode() {
                std::list<Code *> codes;
                auto unit_items = this->GetUnit()
                        ->GetItems();
                for (auto unit_item: unit_items) {
                    try {
                        if (unit_item->GetUnitItemType() == UNIT_ITEM_DEFINITION) {
                            auto definition = (Definition *) unit_item;
                            if (DEFINITION_FUNCTION == definition->GetDefinitionType()) {
                                auto function_definition = (FunctionDefinition *) definition;
                                X64FunctionEmitter function_emitter(function_definition);
                                auto code = function_emitter.GenerateCode();
                                if (nullptr != code) {
                                    codes.push_back(code);
                                }
                            }
                        }
                    } catch (const std::exception &ex) {
                        // todo: Handle exception
                    }
                }
                return codes;
            }
        }
    }
}

