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

#include <hoo/common/Logger.hh>

#include <iostream>
#include <istream>
#include <sstream>
#include <mutex>
#include <iomanip>
#include <time.h>

namespace hoo
{
    namespace common
    {
        std::ofstream *Logger::_stream = nullptr;
        std::mutex Logger::_write_lock;

        void Logger::Init(std::string fileName)
        {
            if (fileName.empty())
            {
                Logger::_stream = nullptr;
            }
            else
            {
                Logger::_stream = new std::ofstream(fileName, std::ios_base::out);
            }
        }

        void Logger::Close()
        {
            if (nullptr != Logger::_stream)
            {
                Logger::_stream->close();
                delete Logger::_stream;
            }
        }

        void Logger::Log(LogLevel logLevel, std::string message)
        {
            std::lock_guard<std::mutex> guard(Logger::_write_lock);
            std::ostringstream text;
            
            auto time = std::localtime(nullptr);
            text << "[" << std::put_time(time, "%c %Z") << "] ["
                 << Logger::GetLogLevelName(logLevel)
                 << "] " << message << std::endl;
            text.flush();
            std::string content = text.str();
            if (nullptr != Logger::_stream)
            {
                *Logger::_stream << content;
            }
            else
            {
                std::cout << content;
            }
        }

        void Logger::Info(std::string message)
        {
            Logger::Log(LogLevel::info, message);
        }

        void Logger::Warning(std::string message)
        {
            Logger::Log(LogLevel::warning, message);
        }

        void Logger::Error(std::string message)
        {
            Logger::Log(LogLevel::error, message);
        }

        const std::string Logger::GetLogLevelName(LogLevel logLevel)
        {
            switch (logLevel)
            {
            case Logger::error:
                return std::string("Error");
            case Logger::warning:
                return std::string("Warning");
            case Logger::info:
                return std::string("Information");
            default:
                return std::string("Verbose");
            }
        }
    } // namespace common
} // namespace hooc