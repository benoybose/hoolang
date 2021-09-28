#include <memory>

#include <hoo/emitter/EmitterBase.hh>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

namespace hoo
{
    namespace emitter
    {
        EmitterBase::EmitterBase(const std::string &unit_name)
        : _emitter_context(unit_name)
        {
        }

        EmitterBase::EmitterBase(const EmitterContext &emitter_context)
        : _emitter_context(emitter_context)
        {
        }
    }
}