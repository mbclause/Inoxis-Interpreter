// rules for the lexer

lexer grammar lexRules;

WS: [ \n\r] -> skip;

ID: [a-zA-Z] [a-zA-A0-9]*;

INT: SIGN [0-9]+;

fragment SIGN: ('-')?;

