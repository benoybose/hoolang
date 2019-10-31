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

#include "NameMangler.hh"
#include <ast/BasicDataTypes.hh>
#include <ast/BasicDataTypeSpecification.hh>

#include <string>

namespace hooc {
    namespace emitter {
        NameMangler::NameMangler(){
        }

        std::string NameMangler::Mangle(FunctionDeclaration *decl) const {
            std::string mangled = "_Z";
            auto name = decl->GetName();
            auto length = name.length();
            mangled += std::to_string(length);
            mangled += name;

            auto args = decl->GetParamList();
            if (args.empty()) {
                mangled += "v";
            } else {
                bool pointer_started = false;
                for (auto arg: args) {
                    auto type = arg->GetDelcaredType();
                    if ((TYPE_SPEC_BASIC != type->GetType()) ||
                        ((TYPE_SPEC_BASIC == type->GetType()) &&
                         ((NAME_STRING == type->GetName()) ||
                          (NAME_CHAR == type->GetName())))) {
                        if (!pointer_started) {
                            mangled += "Pv";
                            pointer_started = true;
                        } else {
                            mangled += "S_";
                        }
                    } else {
                        auto basic_type = (BasicDataTypeSpecification *) type;
                        switch (basic_type->GetDataType()) {
                            case BASIC_DATA_TYPE_INT:
                                mangled += "x";
                                break;
                            case BASIC_DATA_TYPE_BYTE:
                                mangled += "h";
                                break;
                            case BASIC_DATA_TYPE_DOUBLE:
                                mangled += "d";
                                break;
                            case BASIC_DATA_TYPE_BOOL:
                                mangled += "b";
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            return mangled;
        }
    }
}
