/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hooutil.h
 * Author: COMP
 *
 * Created on 6 March, 2018, 11:18 AM
 */

#ifndef HOOUTIL_H
#define HOOUTIL_H

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct hoo_uint32_decoded {
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
        uint8_t byte4;
        uint32_t input;
    };
    
    struct hoo_uint32_decoded hoo_uint32_get_decoded(uint32_t value);


#ifdef __cplusplus
}
#endif

#endif /* HOOUTIL_H */

