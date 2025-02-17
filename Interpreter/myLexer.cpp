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
	pair<TokenSource*, antlr4::CharStream*> source(this, &input);
	/*
	CommonToken data fields for constructor:

		source: pair<TokenSource *, CharStream *> source(&this, &intput)
		type:
		channel: Token::DEFAULT_CHANNEL
		start: the char index of the first character of the token (index into the stream), (just set it to input.index())
		stop: the char index of the last character of the token

	Then need to use setter methods to set:

		line: lineNum
		charPositionInLine: the index in the line of the first char of the token (use charPosInLine)
		text: 
	*/

	//							**ALGORITHM**
	
	// c = current char in input stream
	string c = input.getText(antlr4::misc::Interval(input.index(), input.index()));

	while (input.LA(1) != input.EOF)
	{
		// consume comments (47 = '/')
		if (input.LA(1) == 47)
		{
			// consume the comment until we hit a new line
			while (input.LA(1) != 10)
			{
				input.consume();
			}

			// consume new line
			input.consume();
		}

		// skip whitespace
		else if(input.LA(1) == 32 || input.LA(1) == 9 || input.LA(1) == 13)
		{
			input.consume();
		}

		// skip new line char and call newLine to update fields
		else if (input.LA(1) == 10)
		{
			newLine();

			input.consume();
		}


		else
		{
			c = input.getText(antlr4::misc::Interval(input.index(), input.index()));

			input.consume();

			cout << c;
		}
	}

	// while c is skippable (whitespace, comment, new line):
		// if c is new line
			// call newLine()
		// consume()


	// start = stop = index()
			

	// switch(c):
		// EASY SINGLE CHAR TOKENS {,},(,),;,*,&,],+
			// use another switch for type
			// start = stop = input.index()
			// 
		// could be single or double : =, [, !, <, >, ==, [], !=, <=, >=
			// use another switch for type
			// check next char to see if this is single or double token
			// if single
				// start = stop = input.index()
			// if double
				// start = input.index()
				// stop = input.index() + 1
		// -
			// check previous char, if it's a number, then it's subtraction, anything else it's negative
			// if negative
				// set start
				// consume until you get whole number
				// set stop
				// get text for interval(start,stop)
			// if subtraction
				// start = stop = input.index()
		// number
			// get whole number from stream
			// set stop
			// type = number
			// getText for interval(start,stop)
		// letter
			// get whole word from stream
			// set stop
			// use switch to check if it's a reserved word
				// if not, it's an ID
			// getText for interval(start,stop)

	// consume characters until stop is reached
	// increment charPosInLine by (stop-start)

	// initialize token with the parameters

	// return unique pointer to token

	return NULL;
	
}




/*
Function: type constructor
*/
myLexer::myLexer(antlr4::ANTLRInputStream in)
{
	input = in; 
	
	factory = antlr4::CommonTokenFactory::DEFAULT.get(); 
	
	lineNum = 1; 
	
	charPosInLine = 0;
}
























