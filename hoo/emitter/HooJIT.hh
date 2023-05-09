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

#ifndef HOO_JIT_HH
#define HOO_JIT_HH

#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/Support/Errno.h>
#include <memory>
#include <string>
#include <map>
#include <exception>

using namespace llvm;
using namespace orc;

namespace hoo
{
    namespace emitter
    {
        class HooJIT
        {
        private:
        // std::unique_ptr<ExecutionSession> _session;
        // RTDyldObjectLinkingLayer _object_layer;
        // IRCompileLayer _compiler_layer;
        // DataLayout _layout;
        // MangleAndInterner _mangler;
        // JITDylib &_main_lib;
        ExitOnError ExitOnErr;
        std::unique_ptr<llvm::orc::LLJIT> _jit;

        public:
        // HooJIT(std::unique_ptr<ExecutionSession> session, JITTargetMachineBuilder builder, DataLayout layout);
        HooJIT();

        public:
        JITDylib &GetMainLib();
        void Evaluate(const std::string &source, const std::string &name, bool dump = false);

        private:
        Expected<ExecutorAddr> Lookup(const std::string &name);
        void Add(const std::string &ir, const std::string &name);
        Error Add(ThreadSafeModule thread_safe_module);
        Error Add(std::unique_ptr<llvm::Module> module, std::unique_ptr<LLVMContext> context);

        public:
        template <typename TReturn, typename TParam1, typename TParam2>
        TReturn Execute(const std::string &function_name, TParam1 param1, TParam2 param2)
        {
            auto symbol = Lookup(function_name);
            if (!symbol)
            {
                throw std::runtime_error("symbol not found " + function_name);
            }


            TReturn (*function)(TParam1, TParam2) = symbol->toPtr<TReturn(TParam1, TParam2)>();
            // auto *function = (TReturn(*)(TParam1, TParam2))(*symbol).getAddress();
            auto result = function(param1, param2);
            return result;
        }

        public:
        ~HooJIT();
        };
    }
}
#endif