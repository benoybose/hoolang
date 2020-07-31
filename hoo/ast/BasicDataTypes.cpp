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

#include <hoo/ast/BasicDataTypes.hh>
#include <stdexcept>

namespace hoo
{
    namespace ast
    {
        const std::string NAME_INT = "int";
        const std::string NAME_CHAR = "char";
        const std::string NAME_STRING = "string";
        const std::string NAME_BOOL = "bool";
        const std::string NAME_DOUBLE = "double";
        const std::string NAME_BYTE = "byte";

        const std::string &GetBasicDataTypeName(BasicDataTypeType type)
        {
            switch (type)
            {
            case BASIC_DATA_TYPE_INT:
                return NAME_INT;
            case BASIC_DATA_TYPE_CHAR:
                return NAME_CHAR;
            case BASIC_DATA_TYPE_STRING:
                return NAME_STRING;
            case BASIC_DATA_TYPE_BOOL:
                return NAME_BOOL;
            case BASIC_DATA_TYPE_DOUBLE:
                return NAME_DOUBLE;
            case BASIC_DATA_TYPE_BYTE:
                return NAME_BYTE;
            default:
                throw std::runtime_error("Invalid basic data type.");
            }
        }

        const BasicDataTypeType GetBasicDataType(const std::string &text)
        {
            if (text == NAME_INT)
                return BASIC_DATA_TYPE_INT;
            if (text == NAME_CHAR)
                return BASIC_DATA_TYPE_CHAR;
            if (text == NAME_STRING)
                return BASIC_DATA_TYPE_STRING;
            if (text == NAME_BOOL)
                return BASIC_DATA_TYPE_BOOL;
            if (text == NAME_DOUBLE)
                return BASIC_DATA_TYPE_DOUBLE;
            if (text == NAME_BYTE)
                return BASIC_DATA_TYPE_BYTE;
            throw std::runtime_error("Invalid basic data type name.");
        }

        const BasicDataTypeType GetOperatedTypeByte(const OperatorType opr_type,
                                                    const BasicDataTypeType rtype)
        {
            switch (opr_type)
            {
            case OPERATOR_EQUAL:
            case OPERATOR_NOT_EQUAL:
            case OPERATOR_GREATER_THAN:
            case OPERATOR_LESS_THAN:
            case OPERATOR_GREATER_THAN_EQUAL:
            case OPERATOR_LESS_THAN_EQUAL:
            case OPERATOR_LOGICAL_AND:
            case OPERATOR_LOGICAL_OR:
                return BASIC_DATA_TYPE_BOOL;

            case OPERATOR_ADD:
            case OPERATOR_SUB:
            case OPERATOR_MUL:
            case OPERATOR_DIV:
            case OPERATOR_MOD:
                switch (rtype)
                {
                case BASIC_DATA_TYPE_INT:
                case BASIC_DATA_TYPE_BYTE:
                    return BASIC_DATA_TYPE_INT;

                case BASIC_DATA_TYPE_DOUBLE:
                    return BASIC_DATA_TYPE_DOUBLE;

                case BASIC_DATA_TYPE_INVALID:
                case BASIC_DATA_TYPE_CHAR:
                case BASIC_DATA_TYPE_STRING:
                case BASIC_DATA_TYPE_BOOL:
                    return BASIC_DATA_TYPE_INVALID;
                }
                break;

            case OPERATOR_BIT_OR:
            case OPERATOR_BIT_AND:
            case OPERATOR_BIT_XOR:
            case OPERATOR_BIT_NOT:
            case OPERATOR_BIT_SHIFT_RIGHT:
            case OPERATOR_BIT_SHIFT_LEFT:
            case OPERATOR_ASSIGN:
            case OPERATOR_ASSIGN_INC:
            case OPERATOR_ASSIGN_DEC:
            case OPERATOR_ASSIGN_DIV:
            case OPERATOR_ASSIGN_MUL:
                switch (rtype)
                {
                case BASIC_DATA_TYPE_INT:
                case BASIC_DATA_TYPE_BYTE:
                    return BASIC_DATA_TYPE_INT;

                case BASIC_DATA_TYPE_DOUBLE:
                case BASIC_DATA_TYPE_INVALID:
                case BASIC_DATA_TYPE_CHAR:
                case BASIC_DATA_TYPE_STRING:
                case BASIC_DATA_TYPE_BOOL:
                    return BASIC_DATA_TYPE_INVALID;
                }
                break;

            case OPERATOR_INVALID:
                return BASIC_DATA_TYPE_INVALID;
            }
        }

        const BasicDataTypeType GetOperatedTypeInt(const OperatorType opr_type,
                                                   const BasicDataTypeType rtype)
        {
            switch (opr_type)
            {
            case OPERATOR_EQUAL:
            case OPERATOR_NOT_EQUAL:
            case OPERATOR_GREATER_THAN:
            case OPERATOR_LESS_THAN:
            case OPERATOR_GREATER_THAN_EQUAL:
            case OPERATOR_LESS_THAN_EQUAL:
            case OPERATOR_LOGICAL_AND:
            case OPERATOR_LOGICAL_OR:
                return BASIC_DATA_TYPE_BOOL;

            case OPERATOR_ADD:
            case OPERATOR_SUB:
            case OPERATOR_MUL:
            case OPERATOR_DIV:
            case OPERATOR_MOD:
                switch (rtype)
                {
                case BASIC_DATA_TYPE_INT:
                case BASIC_DATA_TYPE_BYTE:
                    return BASIC_DATA_TYPE_INT;
                case BASIC_DATA_TYPE_DOUBLE:
                    return BASIC_DATA_TYPE_DOUBLE;
                case BASIC_DATA_TYPE_INVALID:
                case BASIC_DATA_TYPE_CHAR:
                case BASIC_DATA_TYPE_STRING:
                case BASIC_DATA_TYPE_BOOL:
                    return BASIC_DATA_TYPE_INVALID;
                }
                break;

            case OPERATOR_BIT_OR:
            case OPERATOR_BIT_AND:
            case OPERATOR_BIT_XOR:
            case OPERATOR_BIT_NOT:
            case OPERATOR_BIT_SHIFT_RIGHT:
            case OPERATOR_BIT_SHIFT_LEFT:
            case OPERATOR_ASSIGN:
            case OPERATOR_ASSIGN_INC:
            case OPERATOR_ASSIGN_DEC:
            case OPERATOR_ASSIGN_DIV:
            case OPERATOR_ASSIGN_MUL:
                switch (rtype)
                {
                case BASIC_DATA_TYPE_INT:
                case BASIC_DATA_TYPE_BYTE:
                    return BASIC_DATA_TYPE_INT;

                case BASIC_DATA_TYPE_DOUBLE:
                case BASIC_DATA_TYPE_INVALID:
                case BASIC_DATA_TYPE_CHAR:
                case BASIC_DATA_TYPE_STRING:
                case BASIC_DATA_TYPE_BOOL:
                    return BASIC_DATA_TYPE_INVALID;
                }
                break;

            case OPERATOR_INVALID:
                return BASIC_DATA_TYPE_INVALID;
            }
        }

        const BasicDataTypeType GetOperatedTypeDouble(const OperatorType opr_type,
                                                      const BasicDataTypeType rtype)
        {
            switch (opr_type)
            {
            case OPERATOR_EQUAL:
            case OPERATOR_NOT_EQUAL:
            case OPERATOR_GREATER_THAN:
            case OPERATOR_LESS_THAN:
            case OPERATOR_GREATER_THAN_EQUAL:
            case OPERATOR_LESS_THAN_EQUAL:
            case OPERATOR_LOGICAL_AND:
            case OPERATOR_LOGICAL_OR:
                return BASIC_DATA_TYPE_BOOL;

            case OPERATOR_ADD:
            case OPERATOR_SUB:
            case OPERATOR_MUL:
            case OPERATOR_DIV:
            case OPERATOR_MOD:
                switch (rtype)
                {
                case BASIC_DATA_TYPE_INT:
                case BASIC_DATA_TYPE_BYTE:
                case BASIC_DATA_TYPE_DOUBLE:
                    return BASIC_DATA_TYPE_DOUBLE;

                case BASIC_DATA_TYPE_INVALID:
                case BASIC_DATA_TYPE_CHAR:
                case BASIC_DATA_TYPE_STRING:
                case BASIC_DATA_TYPE_BOOL:
                    return BASIC_DATA_TYPE_INVALID;
                }
                break;

            case OPERATOR_BIT_OR:
            case OPERATOR_BIT_AND:
            case OPERATOR_BIT_XOR:
            case OPERATOR_BIT_NOT:
            case OPERATOR_BIT_SHIFT_RIGHT:
            case OPERATOR_BIT_SHIFT_LEFT:
                return BASIC_DATA_TYPE_INVALID;

            case OPERATOR_ASSIGN:
            case OPERATOR_ASSIGN_INC:
            case OPERATOR_ASSIGN_DEC:
            case OPERATOR_ASSIGN_DIV:
            case OPERATOR_ASSIGN_MUL:
                switch (rtype)
                {
                case BASIC_DATA_TYPE_INT:
                case BASIC_DATA_TYPE_BYTE:
                case BASIC_DATA_TYPE_DOUBLE:
                    return BASIC_DATA_TYPE_DOUBLE;

                case BASIC_DATA_TYPE_INVALID:
                case BASIC_DATA_TYPE_CHAR:
                case BASIC_DATA_TYPE_STRING:
                case BASIC_DATA_TYPE_BOOL:
                    return BASIC_DATA_TYPE_INVALID;
                }
                break;

            case OPERATOR_INVALID:
                return BASIC_DATA_TYPE_INVALID;
            }
        }

        const BasicDataTypeType GetOperatedTypeBool(const OperatorType opr_type,
                                                    const BasicDataTypeType rtype)
        {
            switch (opr_type)
            {
            case OPERATOR_EQUAL:
            case OPERATOR_NOT_EQUAL:
            case OPERATOR_GREATER_THAN:
            case OPERATOR_LESS_THAN:
            case OPERATOR_GREATER_THAN_EQUAL:
            case OPERATOR_LESS_THAN_EQUAL:
            case OPERATOR_LOGICAL_AND:
            case OPERATOR_LOGICAL_OR:
                return BASIC_DATA_TYPE_BOOL;

            case OPERATOR_ADD:
            case OPERATOR_SUB:
            case OPERATOR_MUL:
            case OPERATOR_DIV:
            case OPERATOR_MOD:
            case OPERATOR_BIT_OR:
            case OPERATOR_BIT_AND:
            case OPERATOR_BIT_XOR:
            case OPERATOR_BIT_NOT:
            case OPERATOR_BIT_SHIFT_RIGHT:
            case OPERATOR_BIT_SHIFT_LEFT:
                return BASIC_DATA_TYPE_INVALID;

            case OPERATOR_ASSIGN:
                switch (rtype)
                {
                case BASIC_DATA_TYPE_BOOL:
                    return BASIC_DATA_TYPE_BOOL;
                case BASIC_DATA_TYPE_INVALID:
                case BASIC_DATA_TYPE_INT:
                case BASIC_DATA_TYPE_BYTE:
                case BASIC_DATA_TYPE_DOUBLE:
                case BASIC_DATA_TYPE_STRING:
                case BASIC_DATA_TYPE_CHAR:
                    return BASIC_DATA_TYPE_INVALID;
                }
                break;

            case OPERATOR_ASSIGN_INC:
            case OPERATOR_ASSIGN_DEC:
            case OPERATOR_ASSIGN_DIV:
            case OPERATOR_ASSIGN_MUL:
            case OPERATOR_INVALID:
                return BASIC_DATA_TYPE_INVALID;
            }
        }

        const BasicDataTypeType GetOperatedTypeChar(const OperatorType opr_type,
                                                    const BasicDataTypeType rtype)
        {
            switch (opr_type)
            {
            case OPERATOR_EQUAL:
            case OPERATOR_NOT_EQUAL:
                return BASIC_DATA_TYPE_BOOL;

            case OPERATOR_GREATER_THAN:
            case OPERATOR_LESS_THAN:
            case OPERATOR_GREATER_THAN_EQUAL:
            case OPERATOR_LESS_THAN_EQUAL:
                return BASIC_DATA_TYPE_INVALID;

            case OPERATOR_LOGICAL_AND:
            case OPERATOR_LOGICAL_OR:
                return BASIC_DATA_TYPE_BOOL;

            case OPERATOR_ADD:
                switch (rtype)
                {
                case BASIC_DATA_TYPE_CHAR:
                case BASIC_DATA_TYPE_STRING:
                    return BASIC_DATA_TYPE_STRING;
                case BASIC_DATA_TYPE_BYTE:
                case BASIC_DATA_TYPE_BOOL:
                case BASIC_DATA_TYPE_DOUBLE:
                case BASIC_DATA_TYPE_INT:
                case BASIC_DATA_TYPE_INVALID:
                    return BASIC_DATA_TYPE_INVALID;
                }
                break;

            case OPERATOR_SUB:
            case OPERATOR_MUL:
            case OPERATOR_DIV:
            case OPERATOR_MOD:
                return BASIC_DATA_TYPE_INVALID;

            case OPERATOR_BIT_OR:
            case OPERATOR_BIT_AND:
            case OPERATOR_BIT_XOR:
            case OPERATOR_BIT_NOT:
            case OPERATOR_BIT_SHIFT_RIGHT:
            case OPERATOR_BIT_SHIFT_LEFT:
                return BASIC_DATA_TYPE_INVALID;

            case OPERATOR_ASSIGN:
                switch (rtype)
                {
                case BASIC_DATA_TYPE_INVALID:
                case BASIC_DATA_TYPE_INT:
                case BASIC_DATA_TYPE_BYTE:
                case BASIC_DATA_TYPE_DOUBLE:
                case BASIC_DATA_TYPE_STRING:
                case BASIC_DATA_TYPE_BOOL:
                    return BASIC_DATA_TYPE_INVALID;
                case BASIC_DATA_TYPE_CHAR:
                    return BASIC_DATA_TYPE_CHAR;
                }
                break;

            case OPERATOR_ASSIGN_INC:
            case OPERATOR_ASSIGN_DEC:
            case OPERATOR_ASSIGN_DIV:
            case OPERATOR_ASSIGN_MUL:
            case OPERATOR_INVALID:
                return BASIC_DATA_TYPE_INVALID;
            }
        }

        const BasicDataTypeType GetOperatedTypeString(const OperatorType opr_type,
                                                      const BasicDataTypeType rtype)
        {
            switch (opr_type)
            {
            case OPERATOR_EQUAL:
            case OPERATOR_NOT_EQUAL:
                return BASIC_DATA_TYPE_BOOL;

            case OPERATOR_GREATER_THAN:
            case OPERATOR_LESS_THAN:
            case OPERATOR_GREATER_THAN_EQUAL:
            case OPERATOR_LESS_THAN_EQUAL:
                return BASIC_DATA_TYPE_INVALID;

            case OPERATOR_LOGICAL_AND:
            case OPERATOR_LOGICAL_OR:
                return BASIC_DATA_TYPE_BOOL;

            case OPERATOR_ADD:
                switch (rtype)
                {
                case BASIC_DATA_TYPE_CHAR:
                case BASIC_DATA_TYPE_STRING:
                    return BASIC_DATA_TYPE_STRING;

                case BASIC_DATA_TYPE_BYTE:
                case BASIC_DATA_TYPE_BOOL:
                case BASIC_DATA_TYPE_DOUBLE:
                case BASIC_DATA_TYPE_INT:
                case BASIC_DATA_TYPE_INVALID:
                    return BASIC_DATA_TYPE_INVALID;
                }
                break;

            case OPERATOR_SUB:
            case OPERATOR_MUL:
            case OPERATOR_DIV:
            case OPERATOR_MOD:
                return BASIC_DATA_TYPE_INVALID;

            case OPERATOR_BIT_OR:
            case OPERATOR_BIT_AND:
            case OPERATOR_BIT_XOR:
            case OPERATOR_BIT_NOT:
            case OPERATOR_BIT_SHIFT_RIGHT:
            case OPERATOR_BIT_SHIFT_LEFT:
                return BASIC_DATA_TYPE_INVALID;

            case OPERATOR_ASSIGN:
                switch (rtype)
                {
                case BASIC_DATA_TYPE_INVALID:
                case BASIC_DATA_TYPE_INT:
                case BASIC_DATA_TYPE_BYTE:
                case BASIC_DATA_TYPE_DOUBLE:
                case BASIC_DATA_TYPE_BOOL:
                    return BASIC_DATA_TYPE_INVALID;
                case BASIC_DATA_TYPE_CHAR:
                case BASIC_DATA_TYPE_STRING:
                    return BASIC_DATA_TYPE_STRING;
                }
                break;

            case OPERATOR_ASSIGN_INC:
                switch (rtype)
                {
                case BASIC_DATA_TYPE_CHAR:
                case BASIC_DATA_TYPE_STRING:
                    return BASIC_DATA_TYPE_STRING;

                case BASIC_DATA_TYPE_BYTE:
                case BASIC_DATA_TYPE_BOOL:
                case BASIC_DATA_TYPE_DOUBLE:
                case BASIC_DATA_TYPE_INT:
                case BASIC_DATA_TYPE_INVALID:
                    return BASIC_DATA_TYPE_INVALID;
                }
                break;

            case OPERATOR_ASSIGN_DEC:
            case OPERATOR_ASSIGN_DIV:
            case OPERATOR_ASSIGN_MUL:
            case OPERATOR_INVALID:
                return BASIC_DATA_TYPE_INVALID;
            }
        }
    } // namespace ast
} // namespace hoo