cmake_minimum_required(VERSION 3.10)
project(hooc)

SET(CMAKE_CXX_STANDARD 11)
include_directories(include)

ADD_CUSTOM_COMMAND(
    OUTPUT ${PROJECT_SOURCE_DIR}/src/hcparser.c
    COMMAND bison
    ARGS    --output=${PROJECT_SOURCE_DIR}/src/hcparser.c
            --defines=${PROJECT_SOURCE_DIR}/include/hcparser.h
            ${PROJECT_SOURCE_DIR}/grammar/hcparser.y)

ADD_CUSTOM_COMMAND(
    OUTPUT ${PROJECT_SOURCE_DIR}/src/hclexer.c
    COMMAND flex
    ARGS    --header-file=${PROJECT_SOURCE_DIR}/include/hclexer.h
            --outfile=${PROJECT_SOURCE_DIR}/src/hclexer.c
            ${PROJECT_SOURCE_DIR}/grammar/hclexer.l
    DEPENDS src/hcparser.c)

ADD_EXECUTABLE(hooc src/hclexer.c
                    src/hcparser.c
                    src/hcliteralexpr.c
                    src/hclogger.c
                    src/hccompiler.c
                    src/hcoperator.c
                    src/hcbinaryexpr.c
                    src/hcexprstmt.c
                    src/hcstmtlist.c
                    src/hcprog.c
                    src/hcbuffer.c
                    src/hcmain.c)


