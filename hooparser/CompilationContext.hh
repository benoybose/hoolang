/*
 * Copyright 2019 Benoy Bose
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

#ifndef COMPILATION_CONTECT_HH
#define COMPILATION_CONTECT_HH

#include "antlr4-runtime.h"
#include "HooParser.h"
#include "HooLexer.h"
#include "Module.hh"
#include "ErrorListener.hh"
#include "BaseError.hh"

#include <string>
#include <memory>

namespace hoo {
    namespace parser {
        class CompilationContext {
        private:
            antlr4::ANTLRInputStream *stream = nullptr;
            HooLexer *lexer = nullptr;
            antlr4::CommonTokenStream *tokens = nullptr;
            HooParser *parser = nullptr;
            HooParser::UnitContext *unitContext = nullptr;
            Module *unit = nullptr;
            ErrorListener* error_listener = nullptr;

        public:
            CompilationContext(std::string source_code);

        public:
            HooParser::UnitContext *GetUnit();
            void AddCompilationError(BaseError* error);
            const std::list<BaseError*>& GetErrors() const;

        public:
            ~CompilationContext();
        };
    }
}

#endif //COMPILATION_CONTECT_HH