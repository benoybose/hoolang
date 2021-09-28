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

#ifndef STATEMENT_EMITTER_HH
#define STATEMENT_EMITTER_HH

#include <hoo/emitter/EmitterBase.hh>
#include <hoo/emitter/DefinitionEmitter.hh>
#include <hoo/ast/Statement.hh>
#include <hoo/ast/CompoundStatement.hh>
#include <hoo/ast/ExpressionStatement.hh>
#include <hoo/ast/ReturnStatement.hh>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>

#include <memory>
#include <stack>
#include <map>

using namespace hoo::ast;

namespace hoo
{
    namespace emitter
    {
        class StatementEmitter : EmitterBase
        {
            private:
            std::shared_ptr<Statement> _statement;

            public:
            StatementEmitter(const std::shared_ptr<Statement> &statement,
            const EmitterContext& emitter_context);

            public:
            void Emit(const std::shared_ptr<Statement> &statement);

            private:
            void EmitCompound(const std::shared_ptr<CompoundStatement> &statement);
            void EmitDeclaration(const std::shared_ptr<DeclarationStatement> &statement);
            void EmitExpression(const std::shared_ptr<ExpressionStatement> &expression_statement);
            void EmitReturn(const std::shared_ptr<ReturnStatement> &statement);
        };
    }
}

#endif