/*
 * Copyright 2019 Benoy Bose
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

#ifndef HCLOGGER_H
#define HCLOGGER_H

#include <fstream>
#include <string>
#include <mutex>

namespace hoo
{
    namespace common
    {
        class Logger
        {
        public:
            typedef enum
            {
                info,
                warning,
                error
            } LogLevel;

        private:
            static std::ofstream *_stream;
            static std::mutex _write_lock;

        public:
            static void Init(std::string fileName);
            static void Log(LogLevel logLevel, std::string message);
            static void Info(std::string message);
            static void Warning(std::string message);
            static void Error(std::string message);
            static void Close();

        private:
            static const std::string GetLogLevelName(LogLevel logLevel);
        };
    } // namespace common
} // namespace hoo

#endif /* HCLOGGER_H */
