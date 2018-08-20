CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
SET(CMAKE_LEGACY_CYGWIN_WIN32 0)
SET (COMPILE_FLAGS "-m64")
SET (LINK_FLAGS "-m64")

PROJECT(hoo CXX)

IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Windows)
    MESSAGE("Platform is Windows")
    SET(${HOO_PLATFORM_WINDOWS} "Windows")
    CONFIGURE_FILE(hooconfig.hh.in ${PROJECT_SOURCE_DIR}/include/hooconfig.hh @ONLY)
ENDIF()

IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Linux)
    MESSAGE("Platform is linux")
    SET(${HOO_PLATFORM_LINUX} "Linux")
    CONFIGURE_FILE(hooconfig.hh.in ${PROJECT_SOURCE_DIR}/include/hooconfig.hh @ONLY)
ENDIF()


SET(HOO_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
INCLUDE(../cmake/Findcppunit.cmake)

INCLUDE_DIRECTORIES(${HOO_INCLUDE_DIRS} ${CPPUNIT_INCLUDE_DIR})
SET(HOO_HEADER_FILES
        include/HooTypes.hh
        include/JIT.hh
        include/Module.hh
        include/Value.hh
        include/Object.hh
        include/StringClass.hh
        include/CharacterClass.hh
        include/Method.hh
        include/TypeSpec.hh
        include/JITException.hh include/MethodParam.hh include/StackItem.hh include/StackScope.hh)

SET(HOO_SOURCE_FILES
        src/JIT.cpp
        src/Module.cpp
        src/Value.cpp
        src/Object.cpp
        src/StringClass.cpp
        src/CharacterClass.cpp
        src/Method.cpp
        src/TypeSpec.cpp
        src/JITException.cpp src/MethodParam.cpp src/StackItem.cpp src/StackScope.cpp)

ADD_LIBRARY(hoo STATIC ${HOO_HEADER_FILES} ${HOO_SOURCE_FILES})
SET_PROPERTY(TARGET hoo PROPERTY CXX_STANDARD 11)

SET(HOO_TEST_SOURCE_FILES tests/TypeTest.cpp
        tests/TypeTest.hh
        tests/HooTest.cpp
        tests/ValueTest.cpp
        tests/ValueTest.hh
        tests/JITBasicTest.hh
        tests/JITBasicTest.cpp tests/MethodBasicTest.cpp tests/MethodBasicTest.hh)

ADD_EXECUTABLE(hootest ${HOO_TEST_SOURCE_FILES})
SET_PROPERTY(TARGET hootest PROPERTY CXX_STANDARD 11)
TARGET_LINK_LIBRARIES(hootest ${CPPUNIT_LIBRARY} hoo)
