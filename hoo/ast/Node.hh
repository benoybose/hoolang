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

#ifndef HOOLANG_NODE_HH
#define HOOLANG_NODE_HH

#include <hoo/ast/Position.hh>

#include <string>

namespace hoo
{
    namespace ast
    {
        class Node
        {
        private:
            std::string _file_name;
            Position *_start;
            Position *_end;

        public:
            /**
             * @brief Construct a new Node object
             * 
             */
            Node();

            /**
             * @brief Get the file name
             * 
             * @return const std::string& 
             */
            const std::string &GetFileName() const;

            /**
             * @brief Get the start position
             * 
             * @return Position* 
             */
            Position *GetStart() const;

            /**
             * @brief Get the end position
             * 
             * @return Position* 
             */
            Position *GetEnd() const;

            /**
             * @brief Set the start position
             * 
             * @param start 
             */
            void SetStart(Position* start);

            /**
             * @brief Set the end position
             * 
             * @param end 
             */
            void SetEnd(Position* end);

        public:
            virtual ~Node();
        };
    } // namespace ast
} // namespace hoo

#endif // HOOLANG_NODE_HH
