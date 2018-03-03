#include <stdint.h>
#include "hcintops.h"

int32_t __hc_op_add(int32_t value1, int32_t value2) { return value1 + value2; }
int32_t __hc_op_sub(int32_t value1, int32_t value2) { return value1 - value2; }
int32_t __hc_op_mul(int32_t value1, int32_t value2) { return value1 * value2; }
int32_t __hc_op_div(int32_t value1, int32_t value2) { return value1 / value2; }
int32_t __hc_op_mod(int32_t value1, int32_t value2) { return value1 % value2; }