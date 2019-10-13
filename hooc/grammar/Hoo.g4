/*
 * Copyright 2019 Benoy Bose
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

grammar Hoo;

import Terminals;

options {
    language=Cpp;
}

constant
    : IntegerConstant #constantInteger
    | FloatingConstant #constantFloating
    | CharacterConstant #constantCharacter
    | BooleanConstant #booleanConstant
    | ByteContant #byteConstant
    ;

primaryExpression
    :   Identifier #primaryRefExpr
    |   constant #primaryConstantExpr
    |   StringLiteral #primaryStringExpr
    |   parent=primaryExpression '.' name=Identifier #primaryNestedRefExpr
    |   container=primaryExpression '[' accessIndex=expression ']' #primaryArrayAccessExpr
    ;

expression
    :   primaryExpression #exprPrimary
    |   invocationExpression #exprInvoke
    |   lvalue=expression opr=('|' | '&' | '^' | '~' | '<<' | '>>') rvalue=expression #exprBitwise
    |   lvalue=expression opr=( '+' | '-' ) rvalue=expression #exprAdditive
    |   lvalue=expression opr=( '*' | '/' | '%') rvalue=expression #exprMultiplicative
    |   lvalue=expression opr=( '==' | '!=' | '>' | '<' | '>=' | '<=' ) rvalue=expression #exprComparison
    |   lvalue=expression opr=( '&&' | '||' ) rvalue=expression #exprLogical
    |   lvalue=expression opr=( '=' | '+=' | '-=' | '/=' | '*=' ) rvalue=expression #expAssignment
    |   '(' expression ')' #exprGrouped
    ;

typeSpecifier
    :   Identifier
    |   typeSpecifier '.' Identifier
    |   typeSpecifier '[' ']'
    ;

invocationExpression
    : receiver=primaryExpression '(' arguments=expressionList? ')'
    ;

expressionList
    :
    expression ( ',' expression )*
    ;

statement
    :   ';' #stmtNoop
    |   compoundStatement #stmtCompound
    |   returnStatement #stmtReturn
    |   declarationStatement #stmtDeclaration
    |   expressionStatement #stmtExpression
    ;

expressionStatement
    :   expression ';'
    ;

declarationStatement
    :   declaration ';'
    ;

compoundStatement
    : '{' statement* '}'
    ;

returnStatement
    :   'return' (returnValue=expression)? ';'
    ;

classDefinition
    :   namespaceDeclaration?
        useSpecifier*
        'class' Identifier ( '(' typeSpecifier+ ')' )? classBody
    ;

classBody
    :
        '{'
            classBodyItem*
        '}'
    ;

classBodyItem
    :   functionDefinition
    |   declarationStatement
    ;

functionDefinition
    :   Declarator? 'func' ( ':' returnType=typeSpecifier )? '(' paramList? ')' name=Identifier compoundStatement
    ;

declaration
    :   Declarator? name=Identifier ':' declared_type=typeSpecifier ( '=' init=expression)?
    ;

paramList
    :   declaration #singleItemParamList
    |   paramList ( ',' decl=declaration )+ #multipleItemParamList
    ;

Declarator
    :   'private' | 'public' | 'protected' | 'var'
    ;

namespaceDeclaration
    :   'namespace' Identifier ( '.' Identifier)* ';'
    ;

useSpecifier
    :   'use' Identifier ( '.' Identifier)* ('as' Identifier) ';'
    ;

unitItem
    :   classDefinition #classDefinitionUnitItem
    |   statement #statementUnitItem
    ;

unit
    :   unitItem* EOF
    ;

ExtraSymbolCharacters: ( '#' | '@' | '$' | '`' | '?' )
    ;
