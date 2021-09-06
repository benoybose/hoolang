/*
 * Copyright 2018 Benoy Bose
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

#ifndef HOOLANG_BASICTYPESPEC_HH
#define HOOLANG_BASICTYPESPEC_HH

#include <hoo/ast/TypeSpecification.hh>
#include <hoo/ast/BasicDataTypes.hh>

namespace hoo
{
    namespace ast
    {

        class BasicTypeSpec : public TypeSpecification
        {
        private:
            BasicDataTypeType _data_type;

        public:
        explicit BasicTypeSpec(BasicDataTypeType data_type);

        public:
            BasicDataTypeType GetDataType() const;

        public:
            const std::string &GetName() const override;
            virtual const bool Equals(const TypeSpecification &other) override;

        public:
            virtual ~BasicTypeSpec();
        };
    } // namespace ast
} // namespace hoo

#endif //HOOLANG_BasicTypeSpec_HH
