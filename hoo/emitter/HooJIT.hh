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

#include "llvm/ADT/StringRef.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/Orc/TargetProcessControl.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/LLVMContext.h"

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
        std::unique_ptr<TargetProcessControl> _taregt_process_control;
        std::unique_ptr<ExecutionSession> _execution_session;

        DataLayout _data_layout;
        MangleAndInterner _mangle;

        RTDyldObjectLinkingLayer _object_layer;
        IRCompileLayer _ir_compile_layer;

        JITDylib &_main_lib;

        public:
        HooJIT(std::unique_ptr<TargetProcessControl> target_process_control,
        std::unique_ptr<ExecutionSession> execution_session,
        JITTargetMachineBuilder target_machine_builder, DataLayout data_layout);

        public:
        JITDylib &GetMainLib();
        static Expected<std::unique_ptr<HooJIT>> Create();
        void Evaluate(const std::string &source, const std::string &name, bool dump = false);

        private:
        Expected<JITEvaluatedSymbol> Lookup(const std::string &name);
        void Add(const std::string &ir, const std::string &name);
        Error Add(ThreadSafeModule thread_safe_module, ResourceTrackerSP resource_tracker = nullptr);
        Error Add(std::unique_ptr<llvm::Module> module, std::unique_ptr<LLVMContext> context, ResourceTrackerSP resource_tracker = nullptr);

        public:
        template <typename TReturn, typename TParam1, typename TParam2>
        TReturn Execute(const std::string &function_name, TParam1 param1, TParam2 param2)
        {
            auto symbol = Lookup(function_name);
            if (!symbol)
            {
                throw std::runtime_error("symbol not found " + function_name);
            }
            auto *function = (TReturn(*)(TParam1, TParam2))(*symbol).getAddress();
            auto result = function(param1, param2);
            return result;
        }

        public:
        ~HooJIT();
        };
    }
}
#endif