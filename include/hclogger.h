/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hclogger.h
 * Author: COMP
 *
 * Created on 1 March, 2018, 12:55 PM
 */

#ifndef HCLOGGER_H
#define HCLOGGER_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    
 
    int hclog_print(const char* format, ...);
    void hclog_init(FILE* stream);
    void hclog_close();
    
    
#ifdef __cplusplus
}
#endif

#endif /* HCLOGGER_H */

