#include <hoo/emitter/UnitEmitter.hh>
#include <hoo/emitter/EmitterException.hh>
#include <hoo/ast/Definition.hh>
#include <hoo/ast/DeclarationStatement.hh>
#include <hoo/emitter/EmitterBase.hh>
#include <hoo/emitter/DefinitionEmitter.hh>

#include <list>

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

        void UnitEmitter::Emit(const std::shared_ptr<UnitItem>& unitItem)
        {
            auto const unitItemType = unitItem->GetUnitItemType();
            switch (unitItemType)
            {
                case UNIT_ITEM_DEFINITION:
                {
                    auto const& definition = dynamic_pointer_cast<Definition>(unitItem);
                    DefinitionEmitter emitter(definition, *this, nullptr);
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
                    throw EmitterException(EMITTER_ERR_01MSG, EMITTER_ERR_01);
                }
            }
        }
    } // namespace emitter
} // namespace hoo