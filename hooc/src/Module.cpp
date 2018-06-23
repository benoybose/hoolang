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
 * File: hcprog.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "hcnode.h"
#include "hcprog.h"
#include "hcstmt.h"
#include "hcstmtlist.h"
#include "hcexprstmt.h"
#include "hcbuffer.h"

struct hc_node_prog* hc_node_prog_create(const char* source_file) {
    struct hc_node_prog* prog = (struct hc_node_prog*)
    malloc(sizeof(struct hc_node_prog));
    prog->node_type = HC_NODE_PROG;
    size_t file_name_length = strlen(source_file) + 1;
    prog->source_file = malloc(sizeof(char) * file_name_length);
    memset(prog->source_file, 0, file_name_length);
    strcpy(prog->source_file, source_file);
    prog->stmt_list = 0;
    return prog;
}

void hc_node_prog_serialize(struct hc_node_prog* prog, 
        struct hc_buffer* buffer) {
    hc_buffer_printf(buffer, "<prog file-path=\"%s\">", prog->source_file);
    if(0 != prog->stmt_list) {
        for(size_t index = 0; index < prog->stmt_list->stmts_count; index++) {
            struct hc_node_stmt* stmt = prog->stmt_list->stmts[index];
            switch(stmt->stmt_type) {
                case HC_STMT_EXPR: {
                    struct hc_node_expr_stmt* expr_stmt = (struct hc_node_expr_stmt*) stmt;
                    hc_node_expr_stmt_serialize(expr_stmt, buffer);
                    break;
                }
            }
        }
    }
    hc_buffer_printf(buffer, "</prog>");
}