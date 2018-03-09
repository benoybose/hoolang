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

#include <stdint.h>
#include "hooint32type.h"
#include "hootype.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    hoo_metaobject hoo_int32_create_from_text(char* text);
    hoo_metaobject hoo_int32_create_from_int32(int32_t value);

#ifdef __cplusplus
}
#endif

#endif /* HCINTOPS_H */

