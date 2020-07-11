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

#include <hoo/parser/ParserDriver.hh>
#include <hoo/parser/ParserContext.hh>
#include <hoo/parser/ParseError.hh>
#include <hoo/parser/UnitVisitor.hh>
#include <hoo/parser/ParseException.hh>

#include <exception>

using namespace hoo;
using namespace hoo::ast;
using namespace antlr4;
using namespace antlr4::tree;

namespace hoo
{
    namespace parser
    {

        ParserDriver::ParserDriver(const std::string &source_code) : _source_code(source_code)
        {
        }

        const hoo::ast::Unit *ParserDriver::BuildModule() const
        {
            ParserContext context(this->_source_code);
            Unit *unit = nullptr;

            try
            {
                auto unitContext = context.GetUnit();
                if (nullptr == unitContext)
                {
                    throw std::runtime_error("Parsing failed because of unknown error.");
                }

                UnitVisitor visitor;
                unit = visitor.visit(unitContext).as<Unit *>();
            }
            catch (const std::bad_cast &ex)
            {
                std::string message(ex.what());
                auto error = new ParseError(ERROR_CODE_BAD_CAST_PARSING, message);
                context.AddCompilationError(error);
            }
            catch (const std::exception &ex)
            {
                std::string message(ex.what());
                auto error = new ParseError(ERROR_CODE_FAILED_PARSING, message);
                context.AddCompilationError(error);
            }

            auto errors = context.GetErrors();
            if (0 < errors.size())
            {
                throw ParseException(errors);
            }

            return unit;
        }
    } // namespace parser
} // namespace hoo
