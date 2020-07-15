/*
 * Copyright 2020 Benoy Bose
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

#ifndef HOOLANG_UTILITY_HH
#define HOOLANG_UTILITY_HH

#include <cstdint>
#include <vector>
#include <string>
#include <cstdint>

#define UTILITY_OFFSET8 8
#define UTILITY_OFFSET16 16
#define UTILITY_OFFSET24 24

namespace hoo
{
    namespace common
    {
        class Utility
        {
        public:
            static std::vector<std::uint8_t> GetBytes(std::uint64_t value);

            template<typename T>
            static void AppendTo(std::vector<T> &to, const std::vector<T> &from)
            {
                to.insert(to.end(), from.begin(), from.end());
            }

            static std::string ToHex(std::uint8_t byte);

            static constexpr std::uint64_t EncodeToUInt64(std::uint8_t b0, std::uint8_t b1)
            {
                std::uint64_t v0 = b0;
                std::uint64_t v1 = (uint64_t)b1 << (uint8_t)UTILITY_OFFSET8;
                return v1 | v0;
            }

            static constexpr std::uint64_t EncodeToUInt64(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2)
            {
                std::uint64_t v0 = b0;
                std::uint64_t v1 = (uint64_t)b1 << (uint8_t)UTILITY_OFFSET8;
                std::uint64_t v2 = (uint64_t)b2 << (uint8_t)UTILITY_OFFSET16;
                return v2 | v1 | v0;
            }

            static constexpr std::uint64_t EncodeToUInt64(std::uint8_t b0, std::uint8_t b1,
                                                          std::uint8_t b2, std::uint8_t b3)
            {
                std::uint64_t v0 = b0;
                std::uint64_t v1 = (uint64_t)b1 << (uint8_t)UTILITY_OFFSET8;
                std::uint64_t v2 = (uint64_t)b2 << (uint8_t)UTILITY_OFFSET16;
                std::uint64_t v3 = (uint64_t)b3 << (uint8_t)UTILITY_OFFSET24;
                return v3 | v2 | v1 | v0;
            }
        };
    } // namespace common
} // namespace hoo
#endif //HOOLANG_UTILITY_HH
