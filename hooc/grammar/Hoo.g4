/*
 * Copyright 2018 Benoy Bose
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

primaryExpression
    :   Identifier
    |   Constant
    |   StringLiteral+
    |   primaryExpression '.' Identifier
    |   primaryExpression '[' Constant? ']'
    ;

expression
    :   primaryExpression
    |   invokeExpression
    |   expression binaryOperator expression
    |   '(' expression ')'
    ;

binaryOperator
    :   arithmeticOperator
    |   relationalOperator
    |   assignmentOperator
    ;

arithmeticOperator
    : ('+' | '-' | '*' | '/' | '%' )
    ;

relationalOperator
    : ( '==' | '!=' | '>' | '<' | '>=' | '<=' | '&&' | '||')
    ;

assignmentOperator
    : ( '=' | '+=' | '-=' | '/=' | '*=' )
    ;

typeSepecifier
    :   Identifier
    |   typeSepecifier '.' Identifier
    |   typeSepecifier '[' (Constant)? ']'
    ;

declaration
    :   Identifier (':' typeSepecifier (initializer)?)?
    ;

paramList
    :   declaration
    |   paramList ( ',' declaration )+
    ;

initializer
    :   '=' expression
    ;

invokeExpression
    : primaryExpression '(' expressionList? ')'
    ;

expressionList
    :
    expression ( ',' expression )*
    ;


functionDefintion
    :   'func' ( ':' typeSepecifier )? '(' paramList? ')' Identifier statement
    ;

statement
    :   ';'
    |   compoundStatement
    |   returnStatement
    |   assignmentStatement
    |   variableDeclaraionStatement
    |   invokeStatement
    ;

invokeStatement
    : invokeExpression ';'
    ;

variableDeclaraionStatement
    :   'var' declaration ';'
    ;

assignmentStatement
    : primaryExpression '=' expression
    ;

compoundStatement
    : '{' statement* '}'
    ;

returnStatement
    :   'return' expression
    ;

classDefinition
    : 'class' Identifier ( '(' typeSepecifier+ ')' )? classBody
    ;

classBody
    :
        '{'
            classBodyItem*
        '}'
    ;

classBodyItem
    : method
    | field
    ;

method
    : AccessSpecifier? functionDefintion
    ;

field
    : AccessSpecifier? declaration
    ;

AccessSpecifier
    : 'private' | 'public' | 'protected'
    ;


namespaceDeclaraion
    :   'namespace' Identifier ( '.' Identifier)* ';'
    ;

useSpecifier
    :   'use' typeSepecifier ('as' Identifier) ';'
    ;

module
    :
        namespaceDeclaraion?
        useSpecifier*
        classDefinition
        EOF
    ;
