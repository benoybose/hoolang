CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
CMAKE_POLICY(SET CMP0074 NEW)
PROJECT(hoocommon)

SET(HOO_COMMON_HEADERS
    ${CMAKE_SOURCE_DIR}/hoo/common/Logger.hh
    ${CMAKE_SOURCE_DIR}/hoo/common/Utility.hh
    ${CMAKE_SOURCE_DIR}/hoo/common/NotImplementedException.hh)

SET(HOO_COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/hoo/common/Logger.cpp
    ${CMAKE_SOURCE_DIR}/hoo/common/Utility.cpp
    ${CMAKE_SOURCE_DIR}/hoo/common/NotImplementedException.cpp)

ADD_LIBRARY(hoocommon STATIC
    ${HOO_COMMON_HEADERS}
    ${HOO_COMMON_SOURCES})

SET_TARGET_PROPERTIES(hoocommon
    PROPERTIES
    PUBLIC_HEADER "${HOO_COMMON_HEADERS}")

TARGET_INCLUDE_DIRECTORIES(hoocommon PRIVATE ${CMAKE_SOURCE_DIR})

ADD_EXECUTABLE(utlitytest ./test/UtilityTest.cpp)
TARGET_INCLUDE_DIRECTORIES(utlitytest PRIVATE ${CMAKE_SOURCE_DIR})
TARGET_LINK_LIBRARIES(utlitytest hoocommon hootest)
ADD_TEST(UtlityTest utlitytest)
