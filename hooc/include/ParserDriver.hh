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

#ifndef PARSERDRIVER_HH
#define PARSERDRIVER_HH

#include "Unit.hh"

#include <string>

namespace hooc {
    class SyntaxError
    {
    private:
        size_t _lineno;
        size_t _columnno;
        std::string _message;

    public:
        SyntaxError(size_t lineno, size_t columnno, const std::string &message);

    public:
        int GetLineNumber() const;
        int GetColumnnNumber() const;
        const std::string &GetMessage() const;
    };

    class ParserDriver {
    private:
        std::string _source_code;
        std::string _file_path;
    public:
        ParserDriver(const std::string &source_code,
                const std::string &file_path);

    public:
        bool Compile(Unit* unit);
    };
}


#endif //PROJECT_PARSERDRIVER_HH
