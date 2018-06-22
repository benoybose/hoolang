cmake_minimum_required(VERSION 3.10)
project(hooc CXX)

SET(CMAKE_CXX_STANDARD 11)
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src)

ADD_CUSTOM_COMMAND(
        OUTPUT ${PROJECT_SOURCE_DIR}/src/FlexScanner.cpp ${PROJECT_SOURCE_DIR}/include/FlexScanner.hh
        COMMAND flex
        ARGS    --header-file=${PROJECT_SOURCE_DIR}/include/FlexScanner.hh
                --outfile=${PROJECT_SOURCE_DIR}/src/FlexScanner.cpp
                ${PROJECT_SOURCE_DIR}/grammar/hclexer.ll
        DEPENDS ${PROJECT_SOURCE_DIR}/src/Parser.cpp
        COMMENT "Invoking flex to generate lexer files")

ADD_CUSTOM_COMMAND(OUTPUT ${PROJECT_SOURCE_DIR}/src/Parser.cpp ${PROJECT_SOURCE_DIR}/include/Parser.hh
        COMMAND bison
        ARGS    --output=${PROJECT_SOURCE_DIR}/src/Parser.cpp
                --defines=${PROJECT_SOURCE_DIR}/include/Parser.hh
                ${PROJECT_SOURCE_DIR}/grammar/hcparser.yy
        COMMENT "Invoking bison to generate grammar files")

SET(hooc_header_files include/Node.hh
        include/Operator.hh
        include/Expression.hh
        include/LiteralExpression.hh
        include/Logger.hh)

SET(hooc_source_files src/Operator.cpp
        src/Expression.cpp
        src/LiteralExpression.cpp
        src/Parser.cpp
        src/FlexScanner.cpp
        include/ParserDriver.hh
        src/ParserDriver.cpp
        src/Logger.cpp)
SET(hooc_link_libraries libPocoFoundation)

ADD_EXECUTABLE(hooc ${hooc_header_files} ${hooc_source_files} src/hcmain.cpp)
TARGET_LINK_LIBRARIES(hooc ${hooc_link_libraries})

ADD_EXECUTABLE(hooctest ${hooc_header_files} ${hooc_source_files}
        test/hooctest.cpp
        test/ArithmeticStmtTest.cpp
        test/ArithmeticStmtTest.hh)
TARGET_LINK_LIBRARIES(hooctest ${hooc_link_libraries} libcppunit)



