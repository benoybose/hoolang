cmake_minimum_required(VERSION 3.6)
SET(CMAKE_LEGACY_CYGWIN_WIN32 0)
SET (COMPILE_FLAGS "-m64")
SET (LINK_FLAGS "-m64")

PROJECT(hooc CXX)
SET(CMAKE_CXX_STANDARD 11)
INCLUDE(../cmake/Findcppunit.cmake)
INCLUDE(../cmake/FindPoco.cmake)
find_package(Poco)

ENABLE_TESTING()

INCLUDE_DIRECTORIES(
        ${CPPUNIT_INCLUDE_DIR}
        ${Poco_Foundation_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/../hoo/include
        ${PROJECT_SOURCE_DIR}/src)

ADD_CUSTOM_COMMAND(
        OUTPUT ${PROJECT_SOURCE_DIR}/src/FlexScanner.cpp ${PROJECT_SOURCE_DIR}/include/FlexScanner.hh
        COMMAND flex
        ARGS    --header-file=${PROJECT_SOURCE_DIR}/include/FlexScanner.hh
                --outfile=${PROJECT_SOURCE_DIR}/src/FlexScanner.cpp
                ${PROJECT_SOURCE_DIR}/grammar/Lexer.l
        DEPENDS ${PROJECT_SOURCE_DIR}/src/Parser.cpp
        MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/grammar/Lexer.l
        COMMENT "Invoking flex to generate lexer files")

ADD_CUSTOM_COMMAND(OUTPUT ${PROJECT_SOURCE_DIR}/src/Parser.cpp ${PROJECT_SOURCE_DIR}/include/Parser.hh
        COMMAND bison
        ARGS    --output=${PROJECT_SOURCE_DIR}/src/Parser.cpp
                --defines=${PROJECT_SOURCE_DIR}/include/Parser.hh
                ${PROJECT_SOURCE_DIR}/grammar/Parser.y
        MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/grammar/Parser.y
        COMMENT "Invoking bison to generate grammar files")

SET(hooc_header_files include/Node.hh
        include/Operator.hh
        include/Expression.hh
        include/LiteralExpression.hh
        include/Logger.hh
        include/BinaryExpression.hh
        include/Statement.hh
        include/ExpressionStatement.hh
        include/StatementList.hh
        include/Module.hh)

SET(hooc_source_files src/Node.cpp
        src/Operator.cpp
        src/Expression.cpp
        src/LiteralExpression.cpp
        src/Parser.cpp
        src/FlexScanner.cpp
        include/ParserDriver.hh
        src/ParserDriver.cpp
        src/Logger.cpp
        src/BinaryExpression.cpp
        src/Statement.cpp
        src/ExpressionStatement.cpp
        src/StatementList.cpp
        src/Module.cpp)
SET(hooc_link_libraries hoo ${Poco_Foundation_LIBRARY})

ADD_EXECUTABLE(hooc ${hooc_header_files} ${hooc_source_files} src/hcmain.cpp)
TARGET_LINK_LIBRARIES(hooc ${hooc_link_libraries})

ADD_EXECUTABLE(hooctest ${hooc_header_files} ${hooc_source_files}
        tests/hooctest.cpp
        tests/ModuleNameTest.cpp
        tests/ModuleNameTest.hh
        tests/TestHelper.cpp
        tests/TestHelper.hh)
TARGET_LINK_LIBRARIES(hooctest ${hooc_link_libraries} ${CPPUNIT_LIBRARY})



ADD_EXECUTABLE(hooctest_arithmetictest
        ${hooc_header_files}
        ${hooc_source_files}
        tests/ArithmeticStmtTest.cpp)
TARGET_LINK_LIBRARIES(hooctest_arithmetictest ${hooc_link_libraries})
ADD_TEST(NAME test_arithmeticstmt COMMAND hooctest_arithmetictest)