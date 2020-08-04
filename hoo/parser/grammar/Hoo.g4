/*
 * Copyright 2020 Benoy Bose
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

literalExpression
    :   ByteLiteral
    |   IntegerLiteral
    |   DoubleLiteral
    |   CharLiteral
    |   BooleanLiteral
    ;

stringExpression
    : StringLiteral
    ;

identifierExpression
    : Identifier
    ;

primaryExpression
    :   literalExpression
    |   stringExpression
    |   identifierExpression
    ;

expression
    :   primaryExpression #simpleExpression
    |   container=expression '[' accessIndex=expression ']' #arrayAccessExpression
    |   receiver=expression '(' arguments=expressionList? ')' #invokeExpression
    |   parent=expression '.' name=Identifier #nestedExpression
    |   lvalue=expression opr=('|' | '&' | '^' | '~' | '<<' | '>>') rvalue=expression #binaryBitExpression
    |   lvalue=expression opr=( '+' | '-' ) rvalue=expression #binaryAddExpression
    |   lvalue=expression opr=( '*' | '/' | '%') rvalue=expression #binaryMultiplicateExpression
    |   lvalue=expression opr=( '==' | '!=' | '>' | '<' | '>=' | '<=' ) rvalue=expression #binaryCompareExpression
    |   lvalue=expression opr=( '&&' | '||' ) rvalue=expression #binaryLogicExpression
    |   lvalue=expression opr=( '=' | '+=' | '-=' | '/=' | '*=' ) rvalue=expression #binaryAssignmentExpression
    |   '(' expression ')' #groupedExpression
    ;

typeSpecifier
    :   BasicDataType #basicDataTypeSpecifier
    |   Identifier  #identifierTypeSpecifier
    |   typeSpecifier '.' Identifier #nestedTypeSpecifier
    |   typeSpecifier '[' ']' #arrayTypeSpecifier
    ;

expressionList
    :
    expression ( ',' expression )*
    ;

statement
    :   declarationStatement
    |   operativeStatement
    |   noOpStatement
    ;

noOpStatement
    : ';'
    ;

operativeStatement
    :   compoundStatement
    |   returnStatement
    |   expressionStatement
    ;

expressionStatement
    :   expression ';'
    ;

declarationStatement
    :   variableDeclaration ';'
    |   functionDeclaration ';'
    ;

compoundStatement
    : '{' statement* '}'
    ;

returnStatement
    :   'return' (returnValue=expression)? ';'
    ;

classDefinition
    :   'class' className=Identifier ( ':' baseEntities=typeList  )? classBody
    ;

typeList
    : typeSpecifier ( ',' typeSpecifier)*
    ;

classBody
    :
        '{'
            classBodyItem*
        '}'
    ;

classBodyItem
    :   defenition
    |   declarationStatement
    ;

functionDefinition
    :   functionDeclaration function_body=operativeStatement
    ;

functionDeclaration
    :   Declarator? 'func' ( ':' returnType=typeSpecifier )? name=Identifier '(' paramList? ')'
    ;

variableDeclaration
    :   type=( 'let' | 'const' ) decl=storageItem
    ;

storageItem
    :   typedStorageItem
    |   name=Identifier '=' init=primaryExpression
    ;

typedStorageItem
    :   name=Identifier ':' declared_type=typeSpecifier
    |   name=Identifier ':' declared_type=typeSpecifier '=' init=expression
    ;

paramList
    : typedStorageItem ( ',' typedStorageItem)+
    ;

Declarator
    :   'private' | 'public' | 'protected' | 'var'
    ;

defenition
    :   classDefinition
    |   functionDefinition
    ;

unitItem
    :   defenition
    |   statement
    ;

unit
    :   unitItem* EOF
    ;

ExtraSymbolCharacters: ( '#' | '@' | '$' | '`' | '?' )
    ;
