#include <stdint.h>
#include "hooint32type.h"
#include <string.h>

const char* HOO_INT32_MODULE_NAME = "sys";
const char* HOO_INT32_TYPE_NAME = "int32";

hoo_metaobject hoo_int32_create_from_text(char* text) {
    hoo_metaobject object = {0};
    strcpy(object.module_name, HOO_INT32_MODULE_NAME);
    strcpy(object.object_type, HOO_INT32_TYPE_NAME);
    object.size = sizeof(int32_t);
    object.object_type = HOO_TYPE_INT32;
}
hoo_metaobject hoo_int32_create_from_int32(int32_t value);