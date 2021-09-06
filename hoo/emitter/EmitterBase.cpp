#include <memory>

#include <hoo/emitter/EmitterBase.hh>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

namespace hoo
{
    namespace emitter
    {
        EmitterBase::EmitterBase(const std::string& unit_name) :
            _unit_name(unit_name),
            _context(std::make_shared<llvm::LLVMContext>()),
            _module(std::make_shared<llvm::Module>(unit_name, *_context)),
            _builder(std::make_shared<llvm::IRBuilder<>>(*_context))
        {
        }

        EmitterBase::EmitterBase(const EmitterBase& emitter_base) :
            _unit_name(emitter_base._unit_name),
            _context(emitter_base._context),
            _module(emitter_base._module),
            _builder(emitter_base._builder)
        {
        }

        std::shared_ptr<LLVMContext> EmitterBase::GetContext()
        {
            return _context;
        }
        
        std::shared_ptr<Module> EmitterBase::GetModule()
        {
            return _module;
        }
        
        std::shared_ptr<IRBuilder<>> EmitterBase::GetBuilder()
        {
            return _builder;
        }
        
        const std::string& EmitterBase::GetUnitName()
        {
            return _unit_name;
        }
    }
}