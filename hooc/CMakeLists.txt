cmake_minimum_required(VERSION 3.6)
SET(CMAKE_LEGACY_CYGWIN_WIN32 0)
SET (COMPILE_FLAGS "-m64")
SET (LINK_FLAGS "-m64")

PROJECT(hooc CXX)
SET(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include
		${CMAKE_HOME_DIRECTORY}/libs/antlr4-cpp-runtime/runtime/src
        ${CMAKE_HOME_DIRECTORY}/hoo/include
        ${PROJECT_SOURCE_DIR}/grammar/
        ${Boost_INCLUDE_DIRS})

ADD_CUSTOM_COMMAND(OUTPUT ${PROJECT_SOURCE_DIR}/grammar/HooParser.h
        ${PROJECT_SOURCE_DIR}/grammar/HooParser.cpp
        ${PROJECT_SOURCE_DIR}/grammar/HooLexer.h
        ${PROJECT_SOURCE_DIR}/grammar/HooLexer.cpp
        COMMAND ${Java_JAVA_EXECUTABLE}
        ARGS    -jar ${CMAKE_HOME_DIRECTORY}/tools/antlr4/antlr-4.7.1-complete.jar
                ${PROJECT_SOURCE_DIR}/grammar/Hoo.g4
                -o ${PROJECT_SOURCE_DIR}/grammar/
        COMMENT "Invoking ANTLR4")

SET(hooc_header_files
        ${PROJECT_SOURCE_DIR}/grammar/HooLexer.h
        ${PROJECT_SOURCE_DIR}/grammar/HooParser.h
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
        ${PROJECT_SOURCE_DIR}/grammar/HooLexer.cpp
        ${PROJECT_SOURCE_DIR}/grammar/HooParser.cpp
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
SET_TARGET_PROPERTIES(hooc PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY ${HOO_DIST}
		LIBRARY_OUTPUT_DIRECTORY ${HOO_DIST}
		RUNTIME_OUTPUT_DIRECTORY ${HOO_DIST})

SET(hooc_link_libraries hooc hoo boost_regex boost_filesystem boost_system)

ADD_EXECUTABLE(hooctest_arithmetictest tests/ArithmeticStmtTest.cpp)
TARGET_LINK_LIBRARIES(hooctest_arithmetictest ${hooc_link_libraries})


ADD_EXECUTABLE(hooctest_modulenametest tests/ModuleNameTest.cpp)
TARGET_LINK_LIBRARIES(hooctest_modulenametest ${hooc_link_libraries})

