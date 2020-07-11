CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
CMAKE_POLICY(SET CMP0074 NEW)
PROJECT(hooparser)

ANTLR4_GENERATE(HooANTLR4
	${CMAKE_SOURCE_DIR}/hoo/parser/grammar/Hoo.g4
        BOTH FALSE TRUE)

MESSAGE("${ANTLR4_INCLUDE_DIR_HooANTLR4}")
        
SET(HOO_PARSER_HEADERS
        Module.hh
        SyntaxError.hh
        ParserDriver.hh
        CompilationContext.hh
        ErrorListener.hh
        BaseError.hh
        ParseError.hh
        UnitVisitor.hh)

SET(HOO_PARSER_SOURCES
        ${ANTLR4_SRC_FILES_HooANTLR4}
        Module.cpp
        SyntaxError.cpp
        ParserDriver.cpp
        CompilationContext.cpp
        ErrorListener.cpp
        BaseError.cpp
        ParseError.cpp
        UnitVisitor.cpp)

ADD_LIBRARY(hooparser STATIC ${HOO_PARSER_HEADERS} ${HOO_PARSER_SOURCES})
TARGET_INCLUDE_DIRECTORIES(hooparser PRIVATE 
        ${CMAKE_SOURCE_DIR}  
        ${Boost_INCLUDE_DIRS} 
        ${ANTLR4_INCLUDE_DIR}
        ${ANTLR4_INCLUDE_DIR_HooANTLR4})
