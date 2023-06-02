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

#include <list>
#include <cstdint>

using namespace hoo::emitter;

std::list<std::int64_t> GetSpecimen()
{
    std::int64_t max64 = INT64_MAX;
    std::int64_t min64 = INT64_MIN;
    std::list<std::int64_t> divisors = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    std::list<std::int64_t> specimen;

    specimen.insert(specimen.end(), divisors.begin(), divisors.end());
    for (const std::int64_t& divisor : divisors) {
        auto outcome = max64 / divisor;
        specimen.push_back(outcome);
    }

    std::list<std::int64_t> negative_specimen;
    for (auto item: specimen) {
        negative_specimen.push_back(item * -1);        
    }
    specimen.insert(specimen.end(), negative_specimen.begin(), negative_specimen.end());
    for (auto item: specimen) {
        std::cout << item << std::endl;
    }
    return specimen;
}


TEST(IntegerArithmeticTest, AddTwoIntegers) 
{
    const std::string source = R"source(
        public add(a:int, b:int) : int {
            return a + b;
        }
        )source";
        auto jit = std::move(*HooJIT::Create());
        jit->Evaluate(source, "test01");
        auto specimen = GetSpecimen();
        for (auto left: specimen) {
            for (auto right: specimen) {
                auto outcome = left + right;
                auto result = jit->Execute<int64_t, int64_t, int64_t> ("add", left, right);
                EXPECT_EQ(outcome, result) << left << "+"
                    << right << "=" << "expected: " << outcome
                    << "resulted:" << result;
            }
        }
}
