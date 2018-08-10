//
// Created by COMP on 29-06-2018.
//

#ifndef PROJECT_TYPESPEC_HH
#define PROJECT_TYPESPEC_HH

#include <string>
#include <memory>

namespace hoo {
    namespace jit {
        class TypeSpec {
        private:
            std::string _typeName;
            std::size_t _size;
            bool _is_value;
        public:
            TypeSpec(const std::string &_typeName, size_t _size, bool _is_value);

        public:
            const std::string &GetTypeName() const;

            std::size_t GetSize();

            bool IsValueType();
        };

        typedef std::shared_ptr<TypeSpec> TypeSpecPtr;
    }
}

#endif //PROJECT_TYPESPEC_HH
