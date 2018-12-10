cmake_minimum_required(VERSION 3.6)
SET(CMAKE_LEGACY_CYGWIN_WIN32 0)
SET (COMPILE_FLAGS "-m64")
SET (LINK_FLAGS "-m64")

PROJECT(hooc CXX)
SET(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/../hoo/include
        ${Boost_INCLUDE_DIRS})

SET(hooc_header_files
        include/TokenDescriptor.hh
        include/Token.hh
        include/LexerError.hh
        include/Lexer.hh
        include/Node.hh
        include/Operator.hh
        include/Expression.hh
        include/LiteralExpression.hh
        include/Logger.hh
        include/BinaryExpression.hh
        include/Statement.hh
        include/ExpressionStatement.hh
        include/StatementList.hh
        include/Module.hh)

SET(hooc_source_files
        src/TokenDescriptor.cpp
        src/Token.cpp
        src/LexerError.cpp
        src/Lexer.cpp
        src/Node.cpp
        src/Operator.cpp
        src/Expression.cpp
        src/LiteralExpression.cpp
        src/Logger.cpp
        src/BinaryExpression.cpp
        src/Statement.cpp
        src/ExpressionStatement.cpp
        src/StatementList.cpp
        src/Module.cpp)
ADD_LIBRARY(hooc STATIC ${hooc_header_files} ${hooc_source_files})

SET(hooc_link_libraries hooc hoo boost_regex boost_filesystem boost_system)

ADD_EXECUTABLE(hooctest_arithmetictest tests/ArithmeticStmtTest.cpp)
TARGET_LINK_LIBRARIES(hooctest_arithmetictest ${hooc_link_libraries})


ADD_EXECUTABLE(hooctest_modulenametest tests/ModuleNameTest.cpp)
TARGET_LINK_LIBRARIES(hooctest_modulenametest ${hooc_link_libraries})

ADD_EXECUTABLE(hooctest_lexertest tests/LexerTest.cpp)
TARGET_LINK_LIBRARIES(hooctest_lexertest ${hooc_link_libraries})
