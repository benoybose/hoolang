CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
CMAKE_POLICY(SET CMP0074 NEW)
PROJECT(hooparser)
INCLUDE(extras.cmake)

ADD_DEFINITIONS(-DANTLR4CPP_STATIC)

ANTLR4_GENERATE(HooANTLR4
	${CMAKE_SOURCE_DIR}/hoo/parser/grammar/Hoo.g4
        BOTH FALSE TRUE)

MESSAGE("${ANTLR4_INCLUDE_DIR_HooANTLR4}")
        
SET(HOO_PARSER_HEADERS
        ${CMAKE_SOURCE_DIR}/hoo/parser/SyntaxError.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/ParserDriver.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/ParserContext.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/ErrorListener.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/BaseError.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/ParseError.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/ParseException.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/UnitVisitor.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/DefinitionVisitor.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/ClassDefinitionVisitor.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/StatementVisitor.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/VisitorHelper.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/FunctionDefinitionVisitor.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/TypeSpecificationVisitor.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/VariableDeclarationVisitor.hh
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/ExpressionVisitor.hh)

SET(HOO_PARSER_SOURCES
        ${ANTLR4_SRC_FILES_HooANTLR4}
        ${CMAKE_SOURCE_DIR}/hoo/parser/SyntaxError.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/ParserDriver.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/ParserContext.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/ErrorListener.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/BaseError.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/ParseError.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/ParseException.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/UnitVisitor.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/DefinitionVisitor.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/ClassDefinitionVisitor.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/StatementVisitor.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/VisitorHelper.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/FunctionDefinitionVisitor.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/TypeSpecificationVisitor.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/VariableDeclarationVisitor.cpp
        ${CMAKE_SOURCE_DIR}/hoo/parser/visitors/ExpressionVisitor.cpp)

ADD_LIBRARY(hooparser STATIC ${HOO_PARSER_HEADERS} ${HOO_PARSER_SOURCES})

SET_TARGET_PROPERTIES(hooparser
        PROPERTIES
        PUBLIC_HEADER
        "${HOO_PARSER_HEADERS}")

ADD_DEPENDENCIES(hooparser antlr4_static)
TARGET_LINK_LIBRARIES(hooparser PRIVATE
        hooast
        antlr4_static)
TARGET_INCLUDE_DIRECTORIES(hooparser PRIVATE 
        ${CMAKE_SOURCE_DIR}
        ${ANTLR4_INCLUDE_DIR}
        ${ANTLR4_INCLUDE_DIR_HooANTLR4})

ADD_EXECUTABLE(BasicClassDefinitionTest 
        test/BasicClassDefinitionTest.cpp)
ADD_HOO_PARSER_TEST(BasicClassDefinitionTest)

ADD_EXECUTABLE(ClassMethodTest01
        test/ClassMethodTest01.cpp)
ADD_HOO_PARSER_TEST(ClassMethodTest01)
