/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hcintops.h
 * Author: COMP
 *
 * Created on 1 March, 2018, 8:36 PM
 */

#ifndef HCINTOPS_H
#define HCINTOPS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
    
    int32_t __hc_op_add(int32_t value1, int32_t value2);
    int32_t __hc_op_sub(int32_t value1, int32_t value2);
    int32_t __hc_op_mul(int32_t value1, int32_t value2);
    int32_t __hc_op_div(int32_t value1, int32_t value2);
    int32_t __hc_op_mod(int32_t value1, int32_t value2);

#ifdef __cplusplus
}
#endif

#endif /* HCINTOPS_H */

