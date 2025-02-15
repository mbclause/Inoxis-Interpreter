/*
File: myLexer.cpp
*/

#include "myLexer.h"





/*
Function: nextToken()

Returns: a unique pointer to the next token in the input stream

Description: This function is called by the TokenStream to get the next Token in the input stream. 
The function will initialize the token, and will determine all of the data fields other than type.

Token type will be determined with a large switch statement, organized by number of chars in token.
White space and comments will be skipped (the program will do nothing).
*/
std::unique_ptr<antlr4::Token> myLexer::nextToken()
{
	/*
	CommonToken data fields for constructor:

		source:
		type:
		channel:
		start: the char index of the first character of the token (index into the stream)
		stop: the char index of the last character of the token

	Then need to use setter methods to set:

		line: 
		charPositionInLine: the index in the line of the first char of the token
		text: */

	return NULL;
	
}























size_t     myLexer::getLine() const
{
	return 1;
}




size_t     myLexer::getCharPositionInLine()
{
	return 1;
}



