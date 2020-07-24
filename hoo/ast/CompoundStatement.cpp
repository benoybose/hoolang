/*
 * Copyright 2020 Benoy Bose
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

#include <hoo/ast/CompoundStatement.hh>

namespace hoo
{
    namespace ast
    {
        CompoundStatement::CompoundStatement(std::list<std::shared_ptr<Statement>> statements,
                                             std::shared_ptr<TypeSpecification> return_type)
            : Statement(STMT_COMPOUND),
              _statements(statements),
              _return_type(return_type)
        {
        }

        std::list<std::shared_ptr<Statement>> CompoundStatement::GetStatements()
        {
            return this->_statements;
        }

        std::shared_ptr<TypeSpecification> CompoundStatement::GetReturnType()
        {
            return this->_return_type;
        }

        CompoundStatement::~CompoundStatement()
        {
        }
    } // namespace ast
} // namespace hoo
