/*
 * Copyright 2023 Benoy Bose
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

#include <gtest/gtest.h>
#include <hoo/emitter/HooJIT.hh>

using namespace hoo::emitter;

TEST(AddIntegersTest, AddTwoIntegers) 
{
    const std::string source = R"source(
        public add(a:int, b:int) : int {
            return a + b;
        }
        )source";
        auto jit = std::move(*HooJIT::Create());
        jit->Evaluate(source, "test01");
        auto result = jit->Execute<int64_t, int64_t, int64_t> ("add", 321, 678);
        EXPECT_EQ(result, 999);
        result = jit->Execute<int64_t, int64_t, int64_t> ("add", 678, 321);
        EXPECT_EQ(result, 999);
}
