cmake_minimum_required(VERSION 3.6)
SET(CMAKE_LEGACY_CYGWIN_WIN32 0)
SET (COMPILE_FLAGS "-m64")
SET (LINK_FLAGS "-m64")

PROJECT(hooc CXX)
SET(CMAKE_CXX_STANDARD 11)

LINK_DIRECTORIES(${HOO_DIST} ${Boost_LIBRARY_DIRS})
ADD_DEFINITIONS(-DANTLR4CPP_STATIC)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include
		${CMAKE_HOME_DIRECTORY}/libs/antlr4-cpp-runtime/runtime/src
        ${CMAKE_HOME_DIRECTORY}/hoo/include
        ${PROJECT_SOURCE_DIR}/grammar/
        ${Boost_INCLUDE_DIRS})

ADD_CUSTOM_COMMAND(OUTPUT ${PROJECT_SOURCE_DIR}/grammar/HooParser.h
        ${PROJECT_SOURCE_DIR}/grammar/HooParser.cpp
        ${PROJECT_SOURCE_DIR}/grammar/HooLexer.h
        ${PROJECT_SOURCE_DIR}/grammar/HooLexer.cpp
		MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/grammar/Hoo.g4
		DEPENDS ${PROJECT_SOURCE_DIR}/grammar/Terminals.g4
        COMMAND ${Java_JAVA_EXECUTABLE}
        ARGS    -jar ${CMAKE_HOME_DIRECTORY}/tools/antlr4/antlr-4.7.1-complete.jar
                ${PROJECT_SOURCE_DIR}/grammar/Hoo.g4
                -o ${PROJECT_SOURCE_DIR}/grammar/
				-no-listener
				-visitor
        COMMENT "Invoking ANTLR4")

SET(hooc_header_files
        ${PROJECT_SOURCE_DIR}/grammar/HooLexer.h
        ${PROJECT_SOURCE_DIR}/grammar/HooParser.h
		src/Node.hh
		src/Operator.hh
		src/Expression.hh
		src/LiteralExpression.hh
		src/Logger.hh
		src/BinaryExpression.hh
		src/Statement.hh
		src/ExpressionStatement.hh
		src/StatementList.hh
		src/CompilationUnit.hh
		grammar/HooLexer.h
		grammar/HooParser.h
		grammar/HooBaseVisitor.h
		grammar/HooVisitor.h
		src/CompilationError.hh
		src/ParserDriver.hh
		src/ParseContext.hh
		src/Class.hh src/AccessSpecifier.hh)

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
        src/CompilationUnit.cpp
		grammar/HooLexer.cpp
		grammar/HooParser.cpp
		grammar/HooBaseVisitor.cpp
		grammar/HooVisitor.cpp
		src/CompilationError.cpp
		src/ParserDriver.cpp
		src/ParseContext.cpp
		src/Class.cpp src/visitors/TypeSpecifierVisitor.cpp src/visitors/TypeSpecifierVisitor.hh)

ADD_LIBRARY(hooc STATIC ${hooc_header_files} ${hooc_source_files})
#SET_TARGET_PROPERTIES(hooc PROPERTIES
#		ARCHIVE_OUTPUT_DIRECTORY ${HOO_DIST}
#		LIBRARY_OUTPUT_DIRECTORY ${HOO_DIST}
#		RUNTIME_OUTPUT_DIRECTORY ${HOO_DIST})

SET(hooc_link_libraries hooc hoo ${Boost_LIBRARIES})

ADD_EXECUTABLE(grammar_test tests/GrammarTest.cpp)
TARGET_LINK_LIBRARIES(grammar_test ${hooc_link_libraries} antlr4-runtime${static_lib_suffix})
#SET_TARGET_PROPERTIES(grammar_test PROPERTIES
#		ARCHIVE_OUTPUT_DIRECTORY ${HOO_DIST}
#		LIBRARY_OUTPUT_DIRECTORY ${HOO_DIST}
#		RUNTIME_OUTPUT_DIRECTORY ${HOO_DIST})
#
#ADD_EXECUTABLE(hooctest_modulenametest tests/ModuleNameTest.cpp)
#TARGET_LINK_LIBRARIES(hooctest_modulenametest ${hooc_link_libraries})
