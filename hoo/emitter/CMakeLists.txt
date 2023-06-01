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
    ${CMAKE_SOURCE_DIR}/hoo/emitter/BlockContext.hh
    ${CMAKE_SOURCE_DIR}/hoo/emitter/BinaryExpressionEmitter.hh)

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
    ${CMAKE_SOURCE_DIR}/hoo/emitter/BlockContext.cpp
    ${CMAKE_SOURCE_DIR}/hoo/emitter/BinaryExpressionEmitter.cpp)

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

ADD_EXECUTABLE(emitter-test
    test/AddIntegersTest.cpp
    test/EmitterTest.cpp)
TARGET_INCLUDE_DIRECTORIES(emitter-test PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${ANTLR4_INCLUDE_DIR}
    ${GENERATED_PARSER_DIR})
TARGET_LINK_LIBRARIES(emitter-test PRIVATE
    hootest
    hooparser
    hooemitter
    LLVM
    gtest)
ADD_TEST(emitter-test)

