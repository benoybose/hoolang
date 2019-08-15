cmake_minimum_required(VERSION 3.6)
PROJECT(hooc CXX)


LINK_DIRECTORIES(${HOO_DIST} ${Boost_LIBRARY_DIRS})
ADD_DEFINITIONS(-DANTLR4CPP_STATIC)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src
		${CMAKE_HOME_DIRECTORY}/libs/antlr4-cpp-runtime/runtime/src
        ${CMAKE_HOME_DIRECTORY}/hoo/include
        ${PROJECT_SOURCE_DIR}/grammar/
        ${Boost_INCLUDE_DIRS})

ADD_CUSTOM_COMMAND(OUTPUT ${PROJECT_SOURCE_DIR}/grammar/HooParser.h
        ${PROJECT_SOURCE_DIR}/grammar/HooParser.cpp
        ${PROJECT_SOURCE_DIR}/grammar/HooLexer.h
        ${PROJECT_SOURCE_DIR}/grammar/HooLexer.cpp
		${PROJECT_SOURCE_DIR}/grammar/HooBaseVisitor.h
		${PROJECT_SOURCE_DIR}/grammar/HooBaseVisitor.cpp
		${PROJECT_SOURCE_DIR}/grammar/HooVisitor.h
		${PROJECT_SOURCE_DIR}/grammar/HooVisitor.cpp
		MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/grammar/Hoo.g4
		DEPENDS ${PROJECT_SOURCE_DIR}/grammar/Terminals.g4
        COMMAND ${Java_JAVA_EXECUTABLE}
        ARGS    -jar ${CMAKE_HOME_DIRECTORY}/tools/antlr4/antlr-4.7.1-complete.jar
                ${PROJECT_SOURCE_DIR}/grammar/Hoo.g4
                -o ${PROJECT_SOURCE_DIR}/grammar/
				-no-listener
				-visitor
        COMMENT "Invoking ANTLR4")

SET(hooc_header_files
		grammar/HooLexer.h
		grammar/HooParser.h
		grammar/HooBaseVisitor.h
		grammar/HooVisitor.h
		src/Node.hh
		src/ast/Operator.hh
		src/ast/Expression.hh
        src/ast/LiteralExpression.hh
		src/Logger.hh
        src/ast/BinaryExpression.hh
		src/ast/Statement.hh
        src/StatementList.hh
		src/compiler/CompilationUnit.hh
        src/compiler/CompilationError.hh
        src/compiler/ParserDriver.hh
		src/compiler/CompilationContext.hh
		src/Class.hh src/AccessSpecifier.hh
		src/ast/TypeSpecification.hh
		src/ast/RootStatement.hh
		src/visitors/UnitVisitor.hh)

SET(hooc_source_files
        grammar/HooLexer.cpp
        grammar/HooParser.cpp
		grammar/HooBaseVisitor.cpp
		grammar/HooVisitor.cpp
        src/Node.cpp
		src/ast/Operator.cpp
		src/ast/Expression.cpp
        src/ast/LiteralExpression.cpp
        src/Logger.cpp
        src/ast/BinaryExpression.cpp
		src/ast/Statement.cpp
        src/StatementList.cpp
		src/compiler/CompilationUnit.cpp
        src/compiler/CompilationError.cpp
        src/compiler/ParserDriver.cpp
		src/compiler/CompilationContext.cpp
		src/Class.cpp
		src/ast/TypeSpecification.cpp
		src/ast/RootStatement.cpp
		src/visitors/UnitVisitor.cpp
		src/ast/FunctionDefinition.cpp
		src/ast/FunctionDefinition.hh
		src/ast/Declaration.cpp src/ast/Declaration.hh src/ast/ReferenceExpression.cpp src/ast/ReferenceExpression.hh src/ast/ArrayAccessExpression.cpp src/ast/ArrayAccessExpression.hh src/ast/InvokeExpression.cpp src/ast/InvokeExpression.h src/ast/UnitItem.cpp src/ast/UnitItem.hh src/ast/ClassDefinition.cpp src/ast/ClassDefinition.hh src/ast/Unit.cpp src/ast/Unit.h src/compiler/CompilationErrorListener.cpp src/compiler/CompilationErrorListener.hh)

ADD_LIBRARY(hooc STATIC ${hooc_header_files} ${hooc_source_files})
SET(hooc_link_libraries hooc hoo ${Boost_LIBRARIES})

ADD_EXECUTABLE(
		hooc_test tests/HoocTest.cpp
		tests/VariableDeclaration.cpp tests/IntegerLiteral.cpp tests/DecimalLiteral.cpp tests/CharacterLiteral.cpp tests/BooleanLiteral.cpp)
ADD_DEPENDENCIES(hooc_test antlr4_static)
TARGET_LINK_LIBRARIES(hooc_test ${hooc_link_libraries} antlr4-runtime${static_lib_suffix})

