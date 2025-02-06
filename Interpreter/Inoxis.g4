// Define grammar for Inoxis language

grammar Inoxis;

import lexRules;

program: funcDecs main funcDefs EOF;

funcDecs: funcDec*;

main: 'int' 'main()' '{' statList 'return 0;' '}';

funcDefs: funcDef*;

statList: (statement';')*;




funcDec: 'int' pointRef ID '(' param ')' ';';

funcDef: 'int' pointRef ID '(' param ')' '{' statList return '}';

funcCall: ID '(' arg ')';




param: 'int' pointRef mut ID subscript;

var: pointRef ID array;

varDec: 'int' pointRef mut ID array varDecRHS;

arg: INT | var;



statement: varDec | assign | while | ifElseBlock | funcCall;



assign: var '=' assignRHS;



return: 'return' retVal ';';

retVal: INT | var | expression;




mut: 'mut'?;

pointRef: ('*'|'&')?;

subscript: '[]'?;

array: ('[' INT ']')?;

allocate: 'new' 'int' array;



varDecRHS: ('=' assignRHS)?;

assignRHS: expression | allocate;



expression: expression + expression | expression - expression | factor;

factor: var | INT | '(' expression ')' | funcCall;



while: 'while' '(' condition ')' '{' statList '}';

ifElseBlock: 'if' '(' condition ')' '{' statList '}' elif else;

elif: ('elif' '(' condition ')' '{' statList '}')*;

else: ('else' '(' condition ')' '{' statList '}')?;



condition: not ID condOp condRHS;

not: '!'?;

condOp: '<' | '>' | '==' | '<=' | '>=';

condRHS: ID | INT;