CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
CMAKE_POLICY(SET CMP0074 NEW)
PROJECT(hooemitter)

SET(HOO_EMITTER_HEADERS
    ${CMAKE_SOURCE_DIR}/hoo/emitter/UnitEmitter.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/EmitterException.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/EmitterBase.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/DefinitionEmitter.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/ClassDefinitionEmitter.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/FunctionDefinitionEmitter.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/EmitterUtils.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/HooJIT.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/CastEmitter.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/StatementEmitter.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/ExpressionEmitter.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/EmitterContext.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/BlockContext.hh)

SET(HOO_EMITTER_SOURCES
    ${CMAKE_SOURCE_DIR}/hoo/emitter/UnitEmitter.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/EmitterException.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/EmitterBase.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/DefinitionEmitter.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/ClassDefinitionEmitter.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/FunctionDefinitionEmitter.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/EmitterUtils.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/HooJIT.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/CastEmitter.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/StatementEmitter.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/ExpressionEmitter.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/EmitterContext.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/BlockContext.cpp)

ADD_LIBRARY(hooemitter STATIC
    ${HOO_EMITTER_HEADERS}
    ${HOO_EMITTER_SOURCES})

SET_TARGET_PROPERTIES(hooemitter
    PROPERTIES
    PUBLIC_HEADER
    "${HOO_EMITTER_HEADERS}")

ADD_DEPENDENCIES(hooemitter
    hooast
    hooparser)

TARGET_INCLUDE_DIRECTORIES(hooemitter PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${ANTLR4_INCLUDE_DIR}
    ${GENERATED_PARSER_DIR})

TARGET_LINK_LIBRARIES(hooemitter PRIVATE
    hooparser)

ADD_EXECUTABLE(AddMethodTest test/AddMethodTest.cpp)
TARGET_INCLUDE_DIRECTORIES(AddMethodTest PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${ANTLR4_INCLUDE_DIR}
    ${GENERATED_PARSER_DIR})
TARGET_LINK_LIBRARIES(AddMethodTest PRIVATE
    hootest
    hooparser
    hooemitter LLVM)
ADD_TEST(AddMethodTest AddMethodTest)

ADD_EXECUTABLE(SubMethodTest test/SubMethodTest.cpp)
TARGET_INCLUDE_DIRECTORIES(SubMethodTest PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${ANTLR4_INCLUDE_DIR}
    ${GENERATED_PARSER_DIR})
TARGET_LINK_LIBRARIES(SubMethodTest PRIVATE
    hootest
    hooparser
    hooemitter LLVM)
ADD_TEST(SubMethodTest SubMethodTest)
