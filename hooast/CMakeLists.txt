CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
CMAKE_POLICY(SET CMP0074 NEW)
PROJECT(hooast)

SET (HOO_AST_HEADERS ArrayAccessExpression.hh
    ArrayDataTypeSpecification.hh
    BasicDataTypes.hh
    BasicDataTypeSpecification.hh
    BinaryExpression.hh
    ClassDefinition.hh
    CompoundStatement.hh
    Declaration.hh
    DeclarationStatement.hh
    Declarator.hh
    Definition.hh
    Expression.hh
    ExpressionStatement.hh
    FunctionDeclaration.hh
    FunctionDefinition.hh
    InvokeExpression.hh
    LiteralExpression.hh
    Node.hh
    NoopStatement.hh
    Operator.hh
    Position.hh
    ReferenceDataTypeSpecification.hh
    ReferenceExpression.hh
    ReturnStatement.hh
    Statement.hh
    TypeSpecification.hh
    Unit.hh
    UnitItem.hh
    VariableDeclaration.hh)

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
    VariableDeclaration.cpp)

    ADD_LIBRARY(hooast STATIC ${HOO_AST_HEADERS} ${HOO_AST_SOURCES})
    