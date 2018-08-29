CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
SET(CMAKE_LEGACY_CYGWIN_WIN32 ON)
SET(CMAKE_VERBOSE_MAKEFILE ON)

SET (COMPILE_FLAGS "-m64")
SET (LINK_FLAGS "-m64")

ENABLE_TESTING()

PROJECT(hoo CXX)

MATH(EXPR HOO_ARCH "${CMAKE_SIZEOF_VOID_P} * 8")
IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL CYGWIN)
    SET(HOO_PLATFORM WIN)
ENDIF()

IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Linux)
    SET(HOO_PLATFORM LINUX)
ENDIF()

SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost 1.66)
MESSAGE("Boost Include Directories: ${Boost_INCLUDE_DIRS}")

CONFIGURE_FILE(HooConfig.hh.in ${PROJECT_SOURCE_DIR}/include/HooConfig.hh)
SET(HOO_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
INCLUDE(../cmake/Findcppunit.cmake)

INCLUDE_DIRECTORIES(${HOO_INCLUDE_DIRS} ${CPPUNIT_INCLUDE_DIR}, ${Boost_INCLUDE_DIRS})
SET(HOO_HEADER_FILES
        include/HooConfig.hh
        include/HooTypes.hh
        include/JIT.hh
        include/Module.hh
        include/Value.hh
        include/Object.hh
        include/StringClass.hh
        include/CharacterClass.hh
        include/Method.hh
        include/TypeSpec.hh
        include/JITException.hh
        include/MethodParam.hh
        include/StackItem.hh
        include/StackScope.hh
        include/ICodeGeneratable.hh
        include/CodeBuffer.hh)

SET(HOO_SOURCE_FILES
        src/JIT.cpp
        src/Module.cpp
        src/Value.cpp
        src/Object.cpp
        src/StringClass.cpp
        src/CharacterClass.cpp
        src/Method.cpp
        src/TypeSpec.cpp
        src/JITException.cpp
        src/MethodParam.cpp
        src/StackItem.cpp
        src/StackScope.cpp
        src/ICodeGeneratable.cpp src/CodeBuffer.cpp)

ADD_LIBRARY(hoo STATIC ${HOO_HEADER_FILES} ${HOO_SOURCE_FILES})
SET_PROPERTY(TARGET hoo PROPERTY CXX_STANDARD 11)

SET(HOO_TEST_SOURCE_FILES
        tests/HooTest.cpp
        tests/MethodBasicTest.cpp
        tests/CodeBufferTest.cpp
        tests/CodeBufferTest.hh)

ADD_EXECUTABLE(hootest ${HOO_TEST_SOURCE_FILES})
SET_PROPERTY(TARGET hootest PROPERTY CXX_STANDARD 11)
TARGET_LINK_LIBRARIES(hootest ${CPPUNIT_LIBRARY} ${Boost_LLIBRARIES} hoo)

ADD_EXECUTABLE(hootest_value tests/ValueTest.cpp)
TARGET_LINK_LIBRARIES(hootest_value hoo)

ADD_EXECUTABLE(hootest_type tests/TypeTest.cpp)
TARGET_LINK_LIBRARIES(hootest_type hoo)

ADD_EXECUTABLE(hootest_jitbasic tests/JITBasicTest.cpp)
TARGET_LINK_LIBRARIES(hootest_jitbasic hoo)

ADD_EXECUTABLE(hootest_methodbasictest tests/MethodBasicTest.cpp)
TARGET_LINK_LIBRARIES(hootest_methodbasictest hoo)

ADD_TEST(NAME test_value COMMAND hootest_value)
