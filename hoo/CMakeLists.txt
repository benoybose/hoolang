CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
SET(CMAKE_LEGACY_CYGWIN_WIN32 0)
SET (COMPILE_FLAGS "-m64")
SET (LINK_FLAGS "-m64")

PROJECT(hoo CXX)

SET(HOO_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

INCLUDE_DIRECTORIES(
        ${HOO_INCLUDE_DIRS})
SET(HOO_HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/hootypes.hh
        ${PROJECT_SOURCE_DIR}/include/JIT.hh include/Module.hh include/Value.hh include/CharacterClass.hh include/Method.hh include/TypeSpec.hh)
SET(HOO_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/JIT.cpp src/Module.cpp src/Value.cpp include/Object.hh src/Object.cpp src/StringClass.cpp include/StringClass.hh src/CharacterClass.cpp src/Method.cpp src/TypeSpec.cpp)

ADD_LIBRARY(hoo STATIC
        ${HOO_HEADER_FILES}
        ${HOO_SOURCE_FILES})

SET(HOO_TEST_SOURCE_FILES tests/TypeTest.cpp
        tests/TypeTest.hh tests/HooTest.cpp tests/ValueTest.cpp tests/ValueTest.hh)

ADD_EXECUTABLE(hootest
        ${HOO_TEST_SOURCE_FILES})

TARGET_LINK_LIBRARIES(hootest libcppunit hoo)
