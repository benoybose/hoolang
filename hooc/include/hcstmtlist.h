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
 * File: hcstmtlist.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 31, March 2018
 */

#include <stdlib.h>

#include "hcnode.h"
#include "hcstmt.h"

#ifndef INCLUDE_NODES_HCSTMTLIST_H_
#define INCLUDE_NODES_HCSTMTLIST_H_

struct hc_node_stmt_list {
	enum HC_TYPE_NODE node_type;
	size_t stmts_count;
	struct hc_node_stmt** stmts;

};

struct hc_node_stmt_list* hc_node_stmt_list_create();
size_t hc_node_stlt_list_add(struct hc_node_stmt_list* list,
		struct hc_node_stmt* stmt);


#endif /* INCLUDE_NODES_HCSTMTLIST_H_ */
