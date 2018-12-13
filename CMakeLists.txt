cmake_minimum_required(VERSION 3.6)
SET (CMAKE_LEGACY_CYGWIN_WIN32 0)
SET (CMAKE_VERBOSE_MAKEFILE OFF)

FIND_PACKAGE(Java REQUIRED)
MESSAGE("Java Executable: ${Java_JAVA_EXECUTABLE}")
SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost)
MESSAGE("Boost Include Directories: ${Boost_INCLUDE_DIRS}")

add_subdirectory(${CMAKE_HOME_DIRECTORY}/libs/antlr4-cpp-runtime)
add_subdirectory(./hoo)
add_subdirectory(./hooc)

ENABLE_TESTING()

ADD_TEST(NAME test_type COMMAND hoo/hootest_type)
ADD_TEST(NAME test_value COMMAND hoo/hootest_value)
ADD_TEST(NAME test_jitbasic COMMAND hoo/hootest_jitbasic)
ADD_TEST(NAME test_methodbasic COMMAND hoo/hootest_methodbasic)
ADD_TEST(NAME test_codebuffer COMMAND hoo/hootest_codebuffer)
ADD_TEST(NAME test_arithmeticstmt COMMAND hooc/hooctest_arithmetictest)
ADD_TEST(NAME test_modulenametest COMMAND hooc/hooctest_modulenametest)