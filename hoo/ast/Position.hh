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

#ifndef HOOLANG_POSITION_HH
#define HOOLANG_POSITION_HH

#include <cstdlib>

using namespace std;

namespace hoo
{
    namespace ast
    {
        class Position
        {
        public:
            /**
             * @brief Construct a new Position object
             * 
             * @param line_number Line number of the position
             * @param character_position Position of character in the line
             */
            Position(size_t line_number, size_t character_position);
            /**
             * @brief Copy
             * 
             * @param Source position
             * */
            Position(const Position& position);
            /**
             * @brief Default constructor
             */
            Position();

            /**
             * @brief Get the line number object
             * 
             * @return size_t 
             */
            size_t GetLineNumber() const;

            /**
             * @brief Get the character position object
             * 
             * @return size_t 
             */
            size_t GetCharacterPosition() const;

        private:
            size_t _line;
            size_t _char_pos;
        };
    } // namespace ast
} // namespace hoo

#endif //HOOLANG_POSITION_HH
