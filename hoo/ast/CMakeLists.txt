CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
CMAKE_POLICY(SET CMP0074 NEW)
PROJECT(hooast)

SET (HOO_AST_HEADERS 
    ${CMAKE_SOURCE_DIR}/hoo/ast/ArrayAccessExpression.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ArrayDataTypeSpecification.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/BasicDataTypes.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/BasicDataTypeSpecification.hh
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
    ${CMAKE_SOURCE_DIR}/hoo/ast/ReferenceDataTypeSpecification.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ReferenceExpression.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ReturnStatement.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/Statement.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/TypeSpecification.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/Unit.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/UnitItem.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/VariableDeclaration.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ClassBodyItem.hh
    ${CMAKE_SOURCE_DIR}/hoo/ast/ClassBody.hh)

SET (HOO_AST_SOURCES ArrayAccessExpression.cpp
    ArrayDataTypeSpecification.cpp
    BasicDataTypes.cpp
    BasicDataTypeSpecification.cpp
    BinaryExpression.cpp
    ClassDefinition.cpp
    CompoundStatement.cpp
    Declaration.cpp
    DeclarationStatement.cpp
    Definition.cpp
    Expression.cpp
    ExpressionStatement.cpp
    FunctionDeclaration.cpp
    FunctionDefinition.cpp
    InvokeExpression.cpp
    LiteralExpression.cpp
    Node.cpp
    NoopStatement.cpp
    Operator.cpp
    Position.cpp
    ReferenceDataTypeSpecification.cpp
    ReferenceExpression.cpp
    ReturnStatement.cpp
    Statement.cpp
    TypeSpecification.cpp
    Unit.cpp
    UnitItem.cpp
    VariableDeclaration.cpp
    ClassBodyItem.cpp
    ClassBody.cpp)

ADD_LIBRARY(hooast STATIC ${HOO_AST_HEADERS} ${HOO_AST_SOURCES})
SET_TARGET_PROPERTIES(hooast 
    PROPERTIES
    PUBLIC_HEADER "${HOO_AST_HEADERS}")
TARGET_INCLUDE_DIRECTORIES(hooast 
    PRIVATE ${CMAKE_SOURCE_DIR})
