cmake_minimum_required(VERSION 3.6)
PROJECT(hooc CXX)

LINK_DIRECTORIES(${HOO_DIST} ${Boost_LIBRARY_DIRS})
ADD_DEFINITIONS(-DANTLR4CPP_STATIC)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src
        ${CMAKE_HOME_DIRECTORY}/hoo/include
        ${Boost_INCLUDE_DIRS})

ANTLR4_GENERATE(HooANTLR4
		${PROJECT_SOURCE_DIR}/grammar/Hoo.g4
		BOTH FALSE TRUE)

INCLUDE_DIRECTORIES( ${ANTLR4_INCLUDE_DIR}
		${ANTLR4_INCLUDE_DIR_HooANTLR4})

SET(hooc_header_files
		src/ast/Operator.hh
		src/ast/Expression.hh
        src/ast/LiteralExpression.hh
		src/Logger.hh
        src/ast/BinaryExpression.hh
		src/ast/Statement.hh
        src/compiler/Module.hh
		src/compiler/SyntaxError.hh
        src/compiler/ParserDriver.hh
		src/compiler/CompilationContext.hh
		src/ast/TypeSpecification.hh
		src/visitors/UnitVisitor.hh
		src/ast/FunctionDefinition.hh
		src/ast/VariableDeclaration.hh
		src/ast/ReferenceExpression.hh
		src/ast/ArrayAccessExpression.hh
        src/ast/InvokeExpression.hh
		src/ast/UnitItem.hh
		src/ast/ClassDefinition.hh
        src/ast/Unit.hh
		src/compiler/ErrorListener.hh
		src/ast/NoopStatement.hh
		src/ast/CompoundStatement.hh
		src/ast/ExpressionStatement.hh
		src/ast/ReturnStatement.hh
		src/ast/Definition.hh
		src/ast/Declaration.hh
		src/ast/FunctionDeclaration.hh
		src/ast/Declarator.hh
		src/ast/DeclarationStatement.hh
		src/ast/BasicDataTypes.hh
		src/ast/ReferenceDataTypeSpecification.hh
		src/ast/ArrayDataTypeSpecification.hh
		src/compiler/BaseError.hh
		src/compiler/ParseError.hh
		src/ast/Node.hh
		src/emitter/Emitter.hh
		src/emitter/EmitterFactory.hh
		src/emitter/EmitterOSTypes.hh
		src/emitter/Code.hh)

SET(hooc_source_files
		${ANTLR4_SRC_FILES_HooANTLR4}
		src/ast/Operator.cpp
		src/ast/Expression.cpp
        src/ast/LiteralExpression.cpp
        src/Logger.cpp
        src/ast/BinaryExpression.cpp
		src/ast/Statement.cpp
        src/compiler/Module.cpp
		src/compiler/SyntaxError.cpp
        src/compiler/ParserDriver.cpp
		src/compiler/CompilationContext.cpp
		src/ast/TypeSpecification.cpp
		src/visitors/UnitVisitor.cpp
		src/ast/FunctionDefinition.cpp
		src/ast/VariableDeclaration.cpp
		src/ast/ReferenceExpression.cpp
		src/ast/ArrayAccessExpression.cpp
		src/ast/InvokeExpression.cpp
		src/ast/UnitItem.cpp
		src/ast/ClassDefinition.cpp
		src/ast/Unit.cpp
		src/compiler/ErrorListener.cpp
		src/ast/NoopStatement.cpp
		src/ast/CompoundStatement.cpp
		src/ast/ExpressionStatement.cpp
		src/ast/ReturnStatement.cpp
		src/ast/DeclarationStatement.cpp
		src/ast/Definition.cpp
		src/ast/Declaration.cpp
		src/ast/FunctionDeclaration.cpp
		src/ast/BasicDataTypeSpecification.cpp
		src/ast/BasicDataTypeSpecification.hh
		src/ast/BasicDataTypes.cpp
		src/ast/ReferenceDataTypeSpecification.cpp
		src/ast/ArrayDataTypeSpecification.cpp
		src/compiler/BaseError.cpp
		src/compiler/ParseError.cpp
		src/ast/Node.cpp
		src/ast/Position.cpp
		src/ast/Position.hh
		src/emitter/Emitter.cpp
		src/emitter/EmitterFactory.cpp
		src/emitter/EmitterArchTypes.hh
		src/emitter/Code.cpp src/emitter/x86/WindowsAmd64CodeEmitter.cpp src/emitter/x86/WindowsAmd64CodeEmitter.hh src/emitter/CodeType.hh src/emitter/x86/AMDRegisters.hh src/emitter/x86/OpcodePrefixes.hh src/emitter/x86/Encoder.cpp src/emitter/x86/Encoder.hh)

ADD_LIBRARY(hooc STATIC ${hooc_header_files} ${hooc_source_files})

SET(hooc_link_libraries hooc ${Boost_LIBRARIES})

ADD_EXECUTABLE(
		hooc_test tests/HoocTest.cpp
		tests/VariableDeclaration.cpp
		tests/IntegerLiteral.cpp
		tests/DecimalLiteral.cpp
		tests/CharacterLiteral.cpp
		tests/BooleanLiteral.cpp
		tests/StringLiteral.cpp tests/PrimaryExpression.cpp
		tests/InvocationExpression.cpp
		tests/BinaryExpression.cpp
		tests/HoocTestHelper.hh
		tests/ReturnStatement.cpp
		tests/Function001.cpp
		tests/FunctionDeclaration.cpp)

ADD_DEPENDENCIES(hooc_test antlr4_static)
TARGET_LINK_LIBRARIES(hooc_test ${hooc_link_libraries} antlr4_static)

