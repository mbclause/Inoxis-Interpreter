/*
File: myLexer.cpp
*/

#include "myLexer.h"





/*
Function: nextToken()

Returns: a unique pointer to the next token in the input stream

Description: This function is called by the TokenStream to get the next Token in the input stream. 
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
		text: 
	*/
}























size_t     myLexer::getLine() const
{

}




size_t     myLexer::getCharPositionInLine()
{

}



