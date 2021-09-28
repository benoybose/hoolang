CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
CMAKE_POLICY(SET CMP0074 NEW)
PROJECT(hooast)

SET (HOO_AST_HEADERS 
    ${CMAKE_SOURCE_DIR}/hoo/ast/ArrayAccessExpression.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ArrayTypeSpec.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/BasicDataTypes.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/BasicTypeSpec.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/BinaryExpression.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ClassDefinition.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/CompoundStatement.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/Declaration.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/DeclarationStatement.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/Declarator.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/Definition.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/Expression.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ExpressionStatement.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/FunctionDeclaration.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/FunctionDefinition.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/InvokeExpression.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/LiteralExpression.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/Node.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/NoopStatement.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/Operator.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/Position.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/RefTypeSpec.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ReferenceExpression.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ReturnStatement.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/Statement.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/TypeSpecification.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/Unit.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/UnitItem.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ItemDeclaration.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ClassBodyItem.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ClassBody.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/StorageItem.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/Param.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/CastExpression.hh)

SET (HOO_AST_SOURCES
    ${CMAKE_SOURCE_DIR}/hoo/ast/ArrayAccessExpression.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/ArrayTypeSpec.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/BasicDataTypes.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/BasicTypeSpec.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/BinaryExpression.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/ClassDefinition.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/CompoundStatement.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/Declaration.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/DeclarationStatement.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/Definition.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/Expression.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/ExpressionStatement.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/FunctionDeclaration.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/FunctionDefinition.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/InvokeExpression.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/LiteralExpression.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/Node.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/NoopStatement.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/Operator.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/Position.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/RefTypeSpec.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/ReferenceExpression.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/ReturnStatement.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/Statement.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/TypeSpecification.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/Unit.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/UnitItem.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/ItemDeclaration.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/ClassBodyItem.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/ClassBody.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/StorageItem.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/Param.cpp
    ${CMAKE_SOURCE_DIR}/hoo/ast/CastExpression.cpp)

ADD_LIBRARY(hooast STATIC ${HOO_AST_HEADERS} ${HOO_AST_SOURCES})
SET_TARGET_PROPERTIES(hooast 
    PROPERTIES
    PUBLIC_HEADER "${HOO_AST_HEADERS}")
TARGET_INCLUDE_DIRECTORIES(hooast 
    PRIVATE ${CMAKE_SOURCE_DIR})
