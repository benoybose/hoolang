/*
 * Copyright 2021 Benoy Bose
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

#ifndef EMITTER_EXCEPTION_HH
#define EMITTER_EXCEPTION_HH

#define ERR_POS(x) x->GetStart(), x->GetEnd()
#define ERR_EMITTER_UNSUPPORTED_UNIT_ITEM       "Unit item is not supported.", 1
#define ERR_EMITTER_UNSUPPORTED_DEFINITION      "Definition is not supported.", 2
#define ERR_EMITTER_UNSUPPORTED_CLS_ITEM        "Class item is not supported.", 3
#define ERR_EMITTER_UNSUPPORTED_STATEMENT       "Statement is not supported.", 4
#define ERR_EMITTER_EVAL_FAILED_EXPRESSION      "Expression is failed to evaluate.", 5
#define ERR_EMITTER_FAILED_LEFT_EXPRESSION      "Left expression is failed to evaluate.", 6
#define ERR_EMITTER_FAILED_RIGHT_EXPRESSION     "Right expression is failed to evaluate.", 7
#define ERR_EMITTER_BINARY_FAILED_EXPRESSION    "Binary expression evaluation failed.", 8
#define ERR_EMITTER_INVALID_CLASS_DEFINITION    "Invalid class definition.", 9
#define ERR_EMITTER_EXPLICIT_CAST_REQUIRED      "An explicit cast operation must be required here.", 10
#define ERR_EMITTER_SUB_OPERATION_UNSUPPORTED   "Subtraction operation is not supported yet", 11
#define ERR_EMITTER_NOT_IMPLEMENTED_EMITTING    "Emitting not implemented", 12
#define ERR_EMITTER_INVALID_RETURN              "Invaid return statement", 13
#define ERR_EMITTER_EXPLICIT_CONV_REQUIRED      "An explicit conversion must be required here", 14
#define ERR_EMITTER_INVALID_CAST                "Invalid cast operations", 15
#define ERR_EMITTER_INVALID_SUB                 "Invalid subtraction operation", 16


#include <hoo/ast/Position.hh>

#include <exception>
#include <string>
#include <memory>
#include <stdexcept>

using namespace hoo::ast;

namespace hoo
{
    namespace emitter
    {
        class EmitterException : virtual std::runtime_error
        {
        private:
            std::string _message;
            int _error_no;
            std::shared_ptr<Position> _start;
            std::shared_ptr<Position> _end;

        public:
            EmitterException(const std::string &message,
            int error_no,
            std::shared_ptr<Position> start = nullptr,
            std::shared_ptr<Position> end = nullptr);

        public:
            virtual ~EmitterException() throw() {}

        public:
            const std::string &GetMessage();
            const int GetErrorNo();
            const std::shared_ptr<Position> GetStart() const;
            const std::shared_ptr<Position> GetEnd() const;

        public:
            virtual const char *what() const throw();
        };
    }
}
#endif
