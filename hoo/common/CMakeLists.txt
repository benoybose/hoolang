CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
CMAKE_POLICY(SET CMP0074 NEW)
PROJECT(hoocommon)

SET(HOO_COMMON_HEADER 
    Logger.hh
    Utility.hh
    NotImplementedException.hh)

SET(HOO_COMMON_SOURCE
    Logger.cpp
    Utility.cpp
    NotImplementedException.cpp)

ADD_LIBRARY(hoocommon STATIC ${HOO_COMMON_HEADER} ${HOO_COMMON_SOURCE})
TARGET_INCLUDE_DIRECTORIES(hoocommon PRIVATE ${CMAKE_SOURCE_DIR})

ADD_EXECUTABLE(utlitytest ./test/UtilityTest.cpp)
TARGET_INCLUDE_DIRECTORIES(utlitytest PRIVATE ${CMAKE_SOURCE_DIR})
TARGET_LINK_LIBRARIES(utlitytest hoocommon hootest)
ADD_TEST(UtlityTest utlitytest)
