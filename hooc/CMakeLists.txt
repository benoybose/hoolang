cmake_minimum_required(VERSION 3.10)
project(hooc, CXX)

SET(CMAKE_CXX_STANDARD 11)
include_directories(include)

ADD_CUSTOM_COMMAND(
        OUTPUT ${PROJECT_SOURCE_DIR}/src/hcparser.c
        COMMAND bison
        ARGS --output=${PROJECT_SOURCE_DIR}/src/hcparser.c
        --defines=${PROJECT_SOURCE_DIR}/include/hcparser.h
        ${PROJECT_SOURCE_DIR}/grammar/hcparser.y)

ADD_CUSTOM_COMMAND(
        OUTPUT ${PROJECT_SOURCE_DIR}/src/hclexer.c
        COMMAND flex
        ARGS --header-file=${PROJECT_SOURCE_DIR}/include/hclexer.h
        --outfile=${PROJECT_SOURCE_DIR}/src/hclexer.c
        ${PROJECT_SOURCE_DIR}/grammar/hclexer.l
        DEPENDS src/hcparser.c)

ADD_EXECUTABLE(hooc include/hcnode.hh
        include/hcoperator.hh
        include/hcbinaryexpr.hh
        include/hcexpr.hh
        include/hcexprstmt.hh
        include/hcliteralexpr.hh
        include/hclogger.hh
        include/hcprog.hh
        include/hcstmt.hh
        include/hcstmtlist.hh
        src/hclexer.c
        src/hcparser.c
        src/hcliteralexpr.cpp
        src/hclogger.cpp
        src/hccompiler.cpp
        src/hcoperator.cpp
        src/hcbinaryexpr.cpp
        src/hcexprstmt.cpp
        src/hcstmtlist.cpp
        src/hcprog.cpp
        src/hcbuffer.cpp
        src/hcmain.cpp
        src/hcexpr.cpp)


