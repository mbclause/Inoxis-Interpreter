// rules for the lexer

lexer grammar lexRules;

WS: [ \n\r\t] -> skip;

ID: [a-zA-Z] [a-zA-Z0-9_]*;

COMMENT: '//' .*? '\n' -> skip;

INT: SIGN [0-9]+;

fragment SIGN: ('-')?;

