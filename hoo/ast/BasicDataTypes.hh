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

#ifndef HOOLANG_BASICDATATYPES_HH
#define HOOLANG_BASICDATATYPES_HH

#include <string>

namespace hoo {
    namespace ast {
        typedef enum {
            BASIC_DATA_TYPE_INT,
            BASIC_DATA_TYPE_CHAR,
            BASIC_DATA_TYPE_STRING,
            BASIC_DATA_TYPE_BOOL,
            BASIC_DATA_TYPE_DOUBLE,
            BASIC_DATA_TYPE_BYTE,
            BASIC_DATA_TYPE_INVALID
        } BasicDataTypeType;

        extern const std::string NAME_INT;
        extern const std::string NAME_CHAR;
        extern const std::string NAME_STRING;
        extern const std::string NAME_BOOL;
        extern const std::string NAME_DOUBLE;
        extern const std::string NAME_BYTE;
        extern const std::string NAME_INVALID;

        extern const std::string& GetBasicDataTypeName(BasicDataTypeType type);
        extern const BasicDataTypeType GetBasicDataType(const std::string& text);
    }
}

#endif //HOOLANG_BASICDATATYPES_HH
