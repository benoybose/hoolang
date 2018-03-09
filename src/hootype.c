#include "hootype.h"
#include "hoomem.h"
#include <memory.h>

struct hoo_metaobject* hoo_metaobject_create(enum hoo_type type,
            uint32_t type_id,
            size_t size) {
    struct hoo_metaobject* metaobject = (struct hoo_metaobject*)
    HOOALLOC(sizeof(struct hoo_metaobject));
    memset(metaobject, 0, sizeof(struct hoo_metaobject));
    metaobject->object_type = type;
    metaobject->size = size;
    metaobject->type_id = type_id;
    metaobject->value._int64 = 0;
    return metaobject;
}

struct hoo_metaobject* hoo_metaobject_create_sbyte(int8_t value) {
    struct hoo_metaobject* metaobject = hoo_metaobject_create(
            HOO_TYPE_SBYTE, 
            0, 
            sizeof(int8_t));
    metaobject->value._sbyte = value;
    return metaobject;
}

struct hoo_metaobject* hoo_metaobject_create_byte(uint8_t value) {
    struct hoo_metaobject* metaobject = hoo_metaobject_create(HOO_TYPE_BYTE,
            0, sizeof(int8_t));
    metaobject->value._byte = value;
    return metaobject;
}

struct hoo_metaobject* hoo_metaobject_create_int32(int32_t value) {
    struct hoo_metaobject* metaobject = hoo_metaobject_create(HOO_TYPE_INT32,
            0, sizeof(int32_t));
    metaobject->value._int32 = value;
    return metaobject;
}

struct hoo_metaobject* hoo_metaobject_create_int64(int64_t value) {
    struct hoo_metaobject* metaobject = hoo_metaobject_create(HOO_TYPE_INT64,
            0, sizeof(int32_t));
    metaobject->value._int64 = value;
    return metaobject;
}

struct hoo_metaobject* hoo_metaobject_create_float(float value) {
    struct hoo_metaobject* metaobject = hoo_metaobject_create(HOO_TYPE_FLOAT,
            0, sizeof(float));
    metaobject->value._float = value;
    return metaobject;
}

struct hoo_metaobject* hoo_metaobject_create_double(double value) {
    struct hoo_metaobject* metaobject = hoo_metaobject_create(HOO_TYPE_DOUBLE,
            0, sizeof(double));
    metaobject->value._double = value;
    return metaobject;
}

struct hoo_metaobject* hoo_metaobject_create_bool(uint8_t value) {
    struct hoo_metaobject* metaobject = hoo_metaobject_create(HOO_TYPE_BOOL,
            0, sizeof(uint8_t));
    metaobject->value._bool = value;
    return metaobject;    
}

struct hoo_metaobject* hoo_metaobject_create_string(struct hoo_string* value) {
    struct hoo_metaobject* metaobject = hoo_metaobject_create(HOO_TYPE_STRING,
            0, value->length);
    metaobject->value._string = value;
    return metaobject;
}

struct hoo_metaobject* hoo_metaobject_create_time(struct hoo_datetime* value) {
    struct hoo_metaobject* metaobject = hoo_metaobject_create(HOO_TYPE_DATETIME,
            0, sizeof(struct hoo_datetime));
    metaobject->value._datetime = value;
    return metaobject;
}

struct hoo_metaobject* hoo_metaobject_create_array(struct hoo_array* value) {
    struct hoo_metaobject* metaobject = hoo_metaobject_create(HOO_TYPE_ARRAY,
            0, value->size);
    metaobject->value._array = value;
    return metaobject;
}

struct hoo_metaobject* hoo_metaobject_create_object(struct hoo_object* value) {
    struct hoo_metaobject* metaobject = hoo_metaobject_create(HOO_TYPE_OBJECT,
            0, -1);
    metaobject->value._object = value;
    return metaobject;
}
