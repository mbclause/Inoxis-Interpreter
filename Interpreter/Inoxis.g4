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
param: 'int' pointRef mut ID subscript;

var: pointRef ID array;

varDec: 'int' pointRef mut ID array varDecRHS ';';

arg: INT | var;

index: INT | ID;


// statement types
statement: varDec | assign | while | ifElseBlock | funcCall | print;


// assignment
assign: var '=' assignRHS ';';


// print
print: 'cout' '<<' (STRING_LITERAL | var | 'endl') out ';';

out: ('<<' (STRING_LITERAL | var | 'endl'))*;


// return statement
return: 'return' retVal ';';

retVal: expression;



// misc token types
mut: 'mut'?;

pointRef: ('*'|'&')?;

subscript: '[]'?;

array: ('[' index ']')?;

allocate: 'new' 'int' array;


// right hand side defs
varDecRHS: ('=' assignRHS)?;

assignRHS: rhsRef | expression | allocate;

rhsRef: '&' mut ID;


// expressions 
expression: 
expression '+' expression       # Add
| expression '-' expression     # Subtract
| factor                        # factorSubRule               
;

factor: 
var                 # VarLiteral          
| INT               # NumLiteral
| funcCallFactor    # funcCallSubRule
;


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