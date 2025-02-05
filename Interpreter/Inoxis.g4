// Define grammar for Inoxis language

grammar Inoxis;

program: funcDecs main funcDefs EOF;

funcDecs: funcDec*;





// placeholders so the grammar compiles
main: 'main';

funcDefs: 'temp';

funcDec: 'temp';