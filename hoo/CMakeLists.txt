CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
SET(CMAKE_LEGACY_CYGWIN_WIN32 ON)
SET(CMAKE_VERBOSE_MAKEFILE ON)

SET (COMPILE_FLAGS "-m64")
SET (LINK_FLAGS "-m64")

PROJECT(hoo CXX)

MATH(EXPR HOO_ARCH "${CMAKE_SIZEOF_VOID_P} * 8")
IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL CYGWIN)
    SET(HOO_PLATFORM WIN)
ENDIF()

IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Linux)
    SET(HOO_PLATFORM LINUX)
ENDIF()

#MESSAGE("Processor ${CMAKE_HOST_SYSTEM_PROCESSOR}")

SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost)
MESSAGE("Boost Include Directories: ${Boost_INCLUDE_DIRS}")

CONFIGURE_FILE(HooConfig.hh.in ${PROJECT_SOURCE_DIR}/include/HooConfig.hh)
SET(HOO_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

INCLUDE_DIRECTORIES(${HOO_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
SET(HOO_HEADER_FILES
        include/HooConfig.hh
        include/HooTypes.hh
        include/JIT.hh
        include/Module.hh
        include/Value.hh
        include/Object.hh
        include/String.hh
        include/Character.hh
        include/Method.hh
        include/TypeSpec.hh
        include/JITException.hh
        include/MethodParam.hh
        include/StackItem.hh
        include/StackScope.hh
        include/ICodeGeneratable.hh
        include/CodeBuffer.hh
        include/ICodeEngine.hh
        include/CodeEngineFactory.hh include/CodeEnginex86_64.hh)

SET(HOO_SOURCE_FILES
        src/JIT.cpp
        src/Module.cpp
        src/Value.cpp
        src/Object.cpp
        src/String.cpp
        src/Character.cpp
        src/Method.cpp
        src/TypeSpec.cpp
        src/JITException.cpp
        src/MethodParam.cpp
        src/StackItem.cpp
        src/StackScope.cpp
        src/ICodeGeneratable.cpp
        src/CodeBuffer.cpp
        src/CodeEngineFactory.cpp)

ADD_LIBRARY(hoo STATIC ${HOO_HEADER_FILES} ${HOO_SOURCE_FILES})
SET_PROPERTY(TARGET hoo PROPERTY CXX_STANDARD 11)

ADD_EXECUTABLE(hootest_type tests/TypeTest.cpp)
TARGET_LINK_LIBRARIES(hootest_type hoo)
SET_PROPERTY(TARGET hootest_type PROPERTY CXX_STANDARD 11)

ADD_EXECUTABLE(hootest_value tests/ValueTest.cpp)
TARGET_LINK_LIBRARIES(hootest_value hoo)
SET_PROPERTY(TARGET hootest_value PROPERTY CXX_STANDARD 11)

ADD_EXECUTABLE(hootest_jitbasic tests/JITBasicTest.cpp)
TARGET_LINK_LIBRARIES(hootest_jitbasic hoo)
SET_PROPERTY(TARGET hootest_jitbasic PROPERTY CXX_STANDARD 11)

ADD_EXECUTABLE(hootest_methodbasic tests/MethodBasicTest.cpp)
TARGET_LINK_LIBRARIES(hootest_methodbasic hoo)
SET_PROPERTY(TARGET hootest_methodbasic PROPERTY CXX_STANDARD 11)

ADD_EXECUTABLE(hootest_codebuffer tests/CodeBufferTest.cpp)
TARGET_LINK_LIBRARIES(hootest_codebuffer hoo)
SET_PROPERTY(TARGET hootest_codebuffer PROPERTY CXX_STANDARD 11)

