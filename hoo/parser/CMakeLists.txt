CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
CMAKE_POLICY(SET CMP0074 NEW)
PROJECT(hooparser)
ADD_DEFINITIONS(-DANTLR4CPP_STATIC)

ANTLR4_GENERATE(HooANTLR4
	${CMAKE_SOURCE_DIR}/hoo/parser/grammar/Hoo.g4
        BOTH FALSE TRUE)

MESSAGE("${ANTLR4_INCLUDE_DIR_HooANTLR4}")
        
SET(HOO_PARSER_HEADERS
        SyntaxError.hh
        ParserDriver.hh
        ParserContext.hh
        ErrorListener.hh
        BaseError.hh
        ParseError.hh
        UnitVisitor.hh
        ParseException.hh)

SET(HOO_PARSER_SOURCES
        ${ANTLR4_SRC_FILES_HooANTLR4}
        SyntaxError.cpp
        ParserDriver.cpp
        ParserContext.cpp
        ErrorListener.cpp
        BaseError.cpp
        ParseError.cpp
        UnitVisitor.cpp
        ParseException.cpp)

ADD_LIBRARY(hooparser STATIC ${HOO_PARSER_HEADERS} ${HOO_PARSER_SOURCES})
TARGET_INCLUDE_DIRECTORIES(hooparser PRIVATE 
        ${CMAKE_SOURCE_DIR}
        ${ANTLR4_INCLUDE_DIR}
        ${ANTLR4_INCLUDE_DIR_HooANTLR4})

ADD_EXECUTABLE(BasicClassDefinitionTest 
        test/BasicClassDefinitionTest.cpp)
TARGET_INCLUDE_DIRECTORIES(BasicClassDefinitionTest PRIVATE 
        ${CMAKE_SOURCE_DIR}
        ${ANTLR4_INCLUDE_DIR}
        ${ANTLR4_INCLUDE_DIR_HooANTLR4})

ADD_DEPENDENCIES(BasicClassDefinitionTest antlr4_static)
TARGET_LINK_LIBRARIES(BasicClassDefinitionTest PRIVATE
        antlr4_static
        hooast
        hootest
        hooparser)
ADD_TEST(BasicClassDefinitionTest BasicClassDefinitionTest)
