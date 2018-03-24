#include "hoonumop.h"
#include "hootype.h"

struct hoo_metaobject* __hoo_num_int32_int32_calc(int32_t value1, 
        int32_t value2, 
        enum HOO_NUM_OPERATORS op) {
    switch(op) {
        case HOO_NUM_OP_ADD:
            return hoo_metaobject_create_int32(value1 + value2);
        case HOO_NUM_OP_SUB:
            return hoo_metaobject_create_int32(value1 - value2);
        case HOO_NUM_OP_MUL:
            return hoo_metaobject_create_int32(value1 * value2);
        case HOO_NUM_OP_DIV:
            if(0 != value2) {
                return hoo_metaobject_create_int32(value1 / value2);
            }
            // TODO: Handle error for divide by zero
            break;
        case HOO_NUM_OP_MOD:
            if(0 != value2) {
                return hoo_metaobject_create_int32(value1 % value2);
            }
            // TODO: Handle error for divide by zero
            break;
            
    }
    return 0;
}

struct hoo_metaobject* __hoo_num_int32_calc(int32_t value, 
        struct hoo_metaobject* op2,
        enum HOO_NUM_OPERATORS op) {
    switch(op2->object_type) {
        case HOO_TYPE_INT32:
            break;
    }
    
    return 0;
}

struct hoo_metaobject* __hoo_num_calc(struct hoo_metaobject* op1, struct hoo_metaobject* op2,
        enum HOO_NUM_OPERATORS op) {
    switch(op1->object_type) {
        case HOO_TYPE_INT32:            
            return __hoo_num_int32_calc(op1->value._int32, op2, op);
    }
    
    return 0;
}

struct hoo_metaobject* __hoo_num_add(struct hoo_metaobject* op1,
		struct hoo_metaobject* op2) {
	return __hoo_num_calc(op1, op2, HOO_NUM_OP_ADD);
}

struct hoo_metaobject* __hoo_num_sub(struct hoo_metaobject* op1,
		struct hoo_metaobject* op2) {
	return __hoo_num_calc(op1, op2,HOO_NUM_OP_SUB);
}

struct hoo_metaobject* __hoo_num_div(struct hoo_metaobject* op1,
		struct hoo_metaobject* op2) {
	return __hoo_num_calc(op1, op2, HOO_NUM_OP_DIV);
}

struct hoo_metaobject* __hoo_num_mul(struct hoo_metaobject* op1,
		struct hoo_metaobject* op2) {
	return __hoo_num_calc(op1, op2, HOO_NUM_OP_MUL);
}

struct hoo_metaobject* __hoo_num_mod(struct hoo_metaobject* op1,
		struct hoo_metaobject* op2) {
	return __hoo_num_calc(op1, op2, HOO_NUM_OP_MOD);
}
