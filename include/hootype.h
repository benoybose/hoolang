/*
 * Copyright 2018 Benoy Bose
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

/**
 * File: hootype.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#ifndef HOOTYPE_H
#define HOOTYPE_H

#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    enum hoo_type{
        HOO_TYPE_SBYTE,
        HOO_TYPE_BYTE,
        HOO_TYPE_INT32,
        HOO_TYPE_INT64,
        HOO_TYPE_FLOAT,
        HOO_TYPE_DOUBLE,
        HOO_TYPE_BOOL,
        HOO_TYPE_STRING,
        HOO_TYPE_DATETIME,
        HOO_TYPE_ARRAY,
        HOO_TYPE_OBJECT
    };
    
    struct hoo_type_register {
    };
    
    struct hoo_object {        
    };
    
    struct hoo_char {
        union {
            uint8_t bytes[4];
            uint32_t unicode;
        } value;
    };
    
    struct hoo_string {
        size_t length;
        struct hoo_char* characters;
    };
    
    struct hoo_datetime {
        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minutes;
        uint8_t seconds;
        uint16_t milliseconds;
        uint16_t timezone;
    };
    
    struct hoo_metaobject;
    
    struct hoo_array {
        size_t size;
        struct hoo_metaobject* _items;
    };
    
    union hoo_value_type{
            int8_t _sbyte;
            uint8_t _byte;
            int32_t _int32;
            int64_t _int64;
            float _float;
            double _double;
            uint8_t _bool;
            struct hoo_string* _string;
            struct hoo_datetime* _datetime;
            struct hoo_array* _array;
            struct hoo_object* _object;
        };
 
    struct hoo_metaobject {
        enum hoo_type object_type;
        uint32_t type_id;
        size_t size;
        union hoo_value_type value;
    };
    
    struct hoo_metaobject* hoo_metaobject_create(enum hoo_type type,
            uint32_t type_id,
            size_t size);
    
    struct hoo_metaobject* hoo_metaobject_create_sbyte(int8_t value);
    struct hoo_metaobject* hoo_metaobject_create_byte(uint8_t value);
    struct hoo_metaobject* hoo_metaobject_create_int32(int32_t value);
    struct hoo_metaobject* hoo_metaobject_create_int64(int64_t value);
    struct hoo_metaobject* hoo_metaobject_create_float(float value);
    struct hoo_metaobject* hoo_metaobject_create_double(double value);
    struct hoo_metaobject* hoo_metaobject_create_bool(uint8_t value);
    struct hoo_metaobject* hoo_metaobject_create_string(struct hoo_string* value);
    struct hoo_metaobject* hoo_metaobject_create_time(struct hoo_datetime* value);
    struct hoo_metaobject* hoo_metaobject_create_array(struct hoo_array* value);
    struct hoo_metaobject* hoo_metaobject_create_object(struct hoo_object* value);
    

#ifdef __cplusplus
}
#endif

#endif /* HOOTYPE_H */

