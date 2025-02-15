// Define grammar for Inoxis language

grammar Inoxis;

import lexRules;

// the large program blocks
program: funcDecs main funcDefs EOF;

funcDecs: funcDec*;

main: 'int' 'main()' '{' statList return '}';

funcDefs: funcDef*;

statList: (statement)*;



// functions
funcDec: 'int' pointRef ID '(' param ')' ';';

funcDef: 'int' pointRef ID '(' param ')' '{' statList return '}';

funcCall: ID '(' arg ')' ';';

funcCallFactor: ID '(' arg ')';



// variable uses
param: 'int' pointRef mut ID subscript;

var: pointRef ID array;

varDec: 'int' pointRef mut ID array varDecRHS ';';

arg: INT | var;

index: INT | ID;


// statement types
statement: varDec | assign | while | ifElseBlock | funcCall;


// assignment
assign: var '=' assignRHS ';';


// return statement
return: 'return' retVal ';';

retVal: INT | var | expression;



// misc token types
mut: 'mut'?;

pointRef: ('*'|'&')?;

subscript: '[]'?;

array: ('[' index ']')?;

allocate: 'new' 'int' array;


// right hand side defs
varDecRHS: ('=' assignRHS)?;

assignRHS: expression | allocate;


// expressions
expression: expression '+' expression | expression '-' expression | factor;

factor: var | INT | '(' expression ')' | funcCallFactor;


// control flow blocks
while: 'while' '(' condition ')' '{' statList '}';

ifElseBlock: 'if' '(' condition ')' '{' statList '}' elif else;

elif: ('elif' '(' condition ')' '{' statList '}')*;

else: ('else' '(' condition ')' '{' statList '}')?;


// conditionals
condition: not ID condOp condRHS;

not: '!'?;

condOp: '<' | '>' | '==' | '<=' | '>=' | '!=';

condRHS: ID | INT;