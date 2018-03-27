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
 * File: hcnode.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 27, March 2018
 */

#ifndef HCNODE_H
#define HCNODE_H

#ifdef __cplusplus
extern "C" {
#endif
    
    enum HC_TYPE_NODE {
        HC_NODE_LITERAL,
        HC_NODE_OPERATOR,
        HC_NODE_EXPRESSION,
        HC_NODE_BASE_EXPRESSION,
        HC_NODE_BINARY_EXPRESSION
    };
    
    struct hc_node {
        enum HC_TYPE_NODE node_type;
    };



#ifdef __cplusplus
}
#endif

#endif /* HCNODE_H */

