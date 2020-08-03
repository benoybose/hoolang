#include <hoo/emitter/UnitEmitter.hh>

namespace hoo
{
    namespace emitter
    {
        UnitEmitter::UnitEmitter(std::shared_ptr<Unit> unit)
            : _unit(unit)
        {
        }
    } // namespace emitter
} // namespace hoo