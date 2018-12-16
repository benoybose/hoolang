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

#include "ParserDriver.hh"
#include "Listener.hh"
#include "antlr4-runtime.h"
#include "HooLexer.h"
#include "HooParser.h"

using namespace hooc;
using namespace antlr4;
using namespace antlr4::tree;

namespace hooc
{
    ParserDriver::ParserDriver(const std::string &source_code): _source_code(source_code) {
        auto stream = new ANTLRInputStream("name");
        auto lexer = new HooLexer(stream);
        auto tokens = new CommonTokenStream(lexer);
        auto parser = new HooParser(tokens);
        auto tree = parser->primaryExpression();
        auto walker = new ParseTreeWalker();
        auto listener = new Listener();
        walker->walk(listener, tree);
    }
}
