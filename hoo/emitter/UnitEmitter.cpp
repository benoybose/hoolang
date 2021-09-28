#include <hoo/emitter/UnitEmitter.hh>
#include <hoo/emitter/EmitterException.hh>
#include <hoo/ast/Definition.hh>
#include <hoo/ast/DeclarationStatement.hh>
#include <hoo/emitter/EmitterBase.hh>
#include <hoo/emitter/DefinitionEmitter.hh>
#include <llvm/Support/raw_ostream.h>

#include <list>
#include <string>

using namespace llvm;

namespace hoo
{
    namespace emitter
    {
        UnitEmitter::UnitEmitter(std::shared_ptr<Unit> unit)
            : _unit(unit), EmitterBase(unit->GetName())
        {
        }

        void UnitEmitter::Emit()
        {
            auto items = this->_unit->GetItems();
            if (!items.empty()) {
                for (auto const& item : items) {
                    this->Emit(item);
                }
            }
        }

        std::string UnitEmitter::GetCode()
        {
            auto current_module = _emitter_context.GetModule();
            std::string module_code;
            raw_string_ostream ostream(module_code);
            current_module->print(ostream, nullptr);
            return module_code;
        }

        void UnitEmitter::Emit(const std::shared_ptr<UnitItem>& unitItem)
        {
            auto const unitItemType = unitItem->GetUnitItemType();
            switch (unitItemType)
            {
                case UNIT_ITEM_DEFINITION:
                {
                    auto const& definition = dynamic_pointer_cast<Definition>(unitItem);
                    DefinitionEmitter emitter(definition, _emitter_context);
                    emitter.Emit();
                    break;
                }
                case UNIT_ITEM_STATEMENT:
                {
                    // todo:  implement  statement emission at unit level
                    break;
                }
                default:
                {
                    throw EmitterException(ERR_EMITTER_UNSUPPORTED_UNIT_ITEM);
                }
            }
        }
    } // namespace emitter
} // namespace hoo