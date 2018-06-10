cmake_minimum_required(VERSION 3.10)
project(hooc, CXX)

SET(CMAKE_CXX_STANDARD 11)
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src)

ADD_CUSTOM_COMMAND(
        OUTPUT ${PROJECT_SOURCE_DIR}/src/FlexScanner.cpp
        COMMAND flex
        ARGS    --header-file=${PROJECT_SOURCE_DIR}/include/FlexScanner.hh
                --outfile=${PROJECT_SOURCE_DIR}/src/FlexScanner.cpp
                ${PROJECT_SOURCE_DIR}/grammar/hclexer.ll
        DEPENDS ${PROJECT_SOURCE_DIR}/src/Parser.cpp)

ADD_CUSTOM_COMMAND(OUTPUT ${PROJECT_SOURCE_DIR}/src/Parser.cpp
        COMMAND bison
        ARGS    --output=${PROJECT_SOURCE_DIR}/src/Parser.cpp
                --defines=${PROJECT_SOURCE_DIR}/include/Parser.hh
                ${PROJECT_SOURCE_DIR}/grammar/hcparser.yy
        COMMENT "Invoking bison")

ADD_EXECUTABLE(hooc src/Parser.cpp
        src/FlexScanner.cpp
        src/hcmain.cpp include/ParserDriver.hh src/ParserDriver.cpp)


