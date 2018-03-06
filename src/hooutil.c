#include "hooutil.h"

struct hoo_int32_decoded hoo_int32_get_decoded(uint32_t value){
    struct hoo_int32_decoded decoded = {0};
    decoded.byte1 = (uint8_t) (value & 0x000000FF);
    decoded.byte2 = (uint8_t) ((value & 0x0000FF00) >> 8);
    decoded.byte3 = (uint8_t) ((value & 0x00FF0000) >> 16);
    decoded.byte4 = (uint8_t) ((value & 0xFF000000) >> 24);
    decoded.input = value;
    return decoded;
}