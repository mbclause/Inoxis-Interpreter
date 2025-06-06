// Define grammar for Inoxis language

grammar Inoxis;

import lexRules;

// the large program blocks
program: funcDecs main funcDefs EOF;

funcDecs: funcDec*;

main: 'int' 'main' '(' ')' '{' statList return '}';

funcDefs: funcDef*;

statList: (statement)*;



// functions
funcDec: 'int' pointRef ID '(' param ')' ';';

funcDef: 'int' pointRef ID '(' param ')' '{' statList return '}';

funcCall: ID '(' arg ')' ';';

funcCallFactor: ID '(' arg ')';



// variable uses
param: 'int' pointRef mut ID paramArray;

var: pointRef ID array;

varDec: 'int' mut pointRef ID array varDecRHS ';';

arg: INT | var;

index: INT | ID;


// statement types
statement: varDec | assign | while | ifElseBlock | funcCall | print;


// assignment
assign: var '=' assignRHS ';';


// print
print: 'cout' '<<' printLiteral out ';';

out: ('<<' printLiteral)*;

printLiteral: (STRING_LITERAL | var | 'endl');


// return statement
return: 'return' retVal ';';

retVal: expression;



// misc token types
mut: 'mut'?;

pointRef: ('*'|'&')?;

subscript: '[]'?;

array: ('[' index ']')?;

paramArray: ('[' INT ']')?;

allocate: 'new' 'int' array;


// right hand side defs
varDecRHS: ('=' assignRHS)?;

assignRHS: rhsRef | expression | allocate;

rhsRef: '&' mut ID;


// expressions 
expression: 
expression '+' expression       # Add
| expression '-' expression     # Subtract
| var                           # VarLiteral
| INT                           # NumLiteral
| funcCallFactor                # funcCallExp                               
;


// control flow blocks
while: 'while' '(' condition ')' '{' statList '}';

ifElseBlock: 'if' '(' condition ')' '{' statList '}' elif else;

elif: ('elif' '(' condition ')' '{' statList '}')*;

else: ('else' '{' statList '}')?;


// conditionals
condition: not ID condOp condRHS;

not: '!'?;

condOp: '<' | '>' | '==' | '<=' | '>=' | '!=';

condRHS: ID | INT;