/*
File: myLexer.cpp
*/

#include "myLexer.h"

// helper function declarations
bool is_digits(const std::string& str);

bool is_letter(const std::string& str);




/*
Function: type constructor
*/
myLexer::myLexer(antlr4::ANTLRInputStream in)
{
	input = in;

	factory = antlr4::CommonTokenFactory::DEFAULT.get();

	lineNum = 1;

	_charPosInLine = 0;

	hitEndOfFile = false;
} // end type ctor



/*
Function: nextToken()

Description: This function is called by the TokenStream to get the next Token in the input stream.
After skipping any white space, determine the tokens type and position. Then, initialize a CommonToken object
with this data and return a unique pointer to it.

Params: None

Returns: a unique pointer to the next token in the input stream
*/
std::unique_ptr<antlr4::Token> myLexer::nextToken()
{

	TOKEN_TYPE type = WS;

	size_t returnedType = antlr4::Token::EOF;

	size_t start = 0;

	size_t stop = 0;

	string text = "";

	pair<TokenSource*, antlr4::CharStream*> newSource(this, &input);

	size_t channel = antlr4::Token::DEFAULT_CHANNEL;

	size_t charPositionInLine = 0;

	size_t line = 0;

	size_t initCharPos = 0;

	// if we've reached the end of the input, toggle the EOF switch, and keep EOF as the token type
	if (input.LA(1) == input.EOF)
	{
		hitEndOfFile = true;
	}

	// if we have not reached end of file...
	else
	{
		// skip all whitespace so we can get the next token
		while (input.LA(1) == 47 || input.LA(1) == 32 || input.LA(1) == 9 || input.LA(1) == 13 || input.LA(1) == 10)
		{
			// consume comments (47 = '/')
			if (input.LA(1) == 47)
			{
				// consume the comment until we hit a new line
				while (input.LA(1) != 10)
				{
					outerConsume();
				}

				// consume new line
				outerConsume();

				// update line number and char pos
				newLine();
			}

			// skip whitespace
			else if (input.LA(1) == 32 || input.LA(1) == 9 || input.LA(1) == 13)
			{
				outerConsume();
			}

			// skip new line char and call newLine to update fields
			else if (input.LA(1) == 10)
			{
				outerConsume();

				newLine();
			}
		} // end while

		// now we can get the next token
		// get the current character in stream
		string c = input.getText(antlr4::misc::Interval(input.index(), input.index()));

		// convert to char for switch stmnt
		char* c1 = c.data();

		// initialize start and stop indices
		start = stop = input.index();

		// save initial char pos in line
		initCharPos = _charPosInLine;

		// EASY SINGLE CHAR TOKENS {,},(,),;,*,&,],+
		if (c == "{" || c == "}" || c == "(" || c == ")" || c == ";" || c == "*" || c == "&" || c == "]" || c == "+")
		{
			// now determine the token type
			switch (*c1)
			{
			case '{':
				type = L_CURLY;
				break;

			case '}':
				type = R_CURLY;
				break;

			case '(':
				type = L_PAREN;
				break;

			case ')':
				type = R_PAREN;
				break;

			case ';':
				type = SEMI_COLON;
				break;

			case '*':
				type = POINTER;
				break;

			case '&':
				type = REFERENCE;
				break;

			case ']':
				type = R_BRACKET;
				break;

			case '+':
				type = PLUS;
				break;

			default:
				cerr << "invalid type\n";
				break;

			} // end switch

			// consume the character
			outerConsume();

			// save token text
			text = c;
		} // end if

		// could be single or double : =, [, !, <, >, ==, [], !=, <=, >=
		// check next char to see if it's single or double token
		else if (c == "=" || c == "[" || c == "!" || c == "<" || c == ">")
		{
			char nextChar = char(input.LA(2));

			bool isDouble = false;

			switch (*c1)
			{
			case '=':
				if (nextChar == '=')
				{
					isDouble = true;

					text = "==";

					type = DOUBLE_EQUALS;
				}

				else
				{
					type = SINGLE_EQUALS;
				}

				break;

			case '[':
				if (nextChar == ']')
				{
					isDouble = true;

					text = "[]";

					type = DOUBLE_BRACKETS;
				}

				else
				{
					type = L_BRACKET;
				}

				break;

			case '!':
				if (nextChar == '=')
				{
					isDouble = true;
					
					text = "!=";

					type = NOT_EQUAL;
				}

				else
				{
					type = NOT;
				}

				break;

			case '<':
				if (nextChar == '=')
				{
					isDouble = true;

					text = "<=";

					type = LESS_EQUAL;
				}

				else
				{
					type = LESS;
				}
				break;

			case '>':
				if (nextChar == '=')
				{
					isDouble = true;

					text = ">=";

					type = GREATER_EQUAL;
				}

				else
				{
					type = GREATER;
				}
				break;

			default:
				cerr << "invalid token\n";
				break;

			} // end switch

			// if the token has two chars
			if (isDouble)
			{
				// set stop index
				stop = input.index() + 1;

				// consume second char
				outerConsume();
			}

			// single char token
			else
			{
				text = c;
			}

			// consume first char
			outerConsume();
		} // end else if

		// determine if token is negative number or subtraction operator
		else if (c == "-")
		{
			char prevChar = char(input.LA(-1));

			// check previous char, if it's a number, then it's subtraction, anything else it's negative
			if (isdigit(prevChar))
			{
				type = MINUS;

				outerConsume();
			}

			else
			{
				// consume negative sign
				outerConsume();

				// consume rest of the number
				while (isdigit(char(input.LA(1))))
					outerConsume();

				// set stop
				stop = input.index() - 1;

				// get text for interval(start,stop)
				text = input.getText(antlr4::misc::Interval(start, stop));

				type = NUMBER;
			}
		} // end else if

		// next token is a word, either a reserved word or an ID
		else if (is_letter(c))
		{
			// consume word
			while (isalnum(char(input.LA(1))) || input.LA(1) == 95)
				outerConsume();

			// set stop
			stop = input.index() - 1;

			//get word text
			text = input.getText(antlr4::misc::Interval(start, stop));

			// now check if it's a reserved word
			if (text == "int")
			{
				type = INT_TYPE;
			}

			else if (text == "main")
			{
				type = MAIN;
			}

			else if (text == "return")
			{
				type = RETURN;
			}

			else if (text == "mut")
			{
				type = MUT;
			}

			else if (text == "new")
			{
				type = NEW;
			}

			else if (text == "while")
			{
				type = WHILE;
			}

			else if (text == "if")
			{
				type = IF;
			}

			else if (text == "elif")
			{
				type = ELIF;
			}

			else if (text == "else")
			{
				type = ELSE;
			}

			else
			{
				type = ID;
			}
		} // end else if

		// if token starts with digit, it's a number
		else if (is_digits(c))
		{
			// consume number
			while (isdigit(char(input.LA(1))))
				outerConsume();

			// set stop
			stop = input.index() - 1;

			//get number text
			text = input.getText(antlr4::misc::Interval(start, stop));

			type = NUMBER;
		}

		else
		{
			cerr << "invalid input to lexer \n";
		}

		// convert token type from enum to size_t
		returnedType = type;

	} // end else

	// initialize token unique pointer with the parameters
	// CommonToken data fields for constructor (source, type,channel, start, stop)
	// this code is taken from antlr c++ source files
	std::unique_ptr<antlr4::CommonToken>
		newToken(new antlr4::CommonToken(newSource, returnedType, channel, start, stop));

	// Then need to use setter methods to set (line, charPosinLine, text)
	newToken->setLine(line);

	newToken->setCharPositionInLine(initCharPos);

	newToken->setText(text);

	// return unique pointer to token
	return move(newToken);
} // end nextToken



/*
helper functions to determine if a string object is a number or a letter,
code taken from StackOverflow user Blastfurnace
*/
bool is_digits(const std::string& str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

bool is_letter(const std::string& str)
{
	return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
}
























