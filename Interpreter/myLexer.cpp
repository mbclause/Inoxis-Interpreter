/*
File: myLexer.cpp
*/

#include "myLexer.h"


bool is_digits(const std::string& str);

bool is_letter(const std::string& str);


void  myLexer::outerConsume()
{
	input.consume();

	_charPosInLine++;
}


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
	CommonToken data fields for constructor (source, type,channel, start, stop):

		source: pair<TokenSource *, CharStream *> source(this, &intput)
		type:
		channel: Token::DEFAULT_CHANNEL
		start: the char index of the first character of the token (index into the stream), (just set it to input.index())
		stop: the char index of the last character of the token

	Then need to use setter methods to set (line, charPosinLine, text):

		line: lineNum
		charPositionInLine: the index in the line of the first char of the token (use charPosInLine)
		text:
	*/

	//							**ALGORITHM**

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

	if (input.LA(1) == input.EOF)
	{

		hitEndOfFile = true;
	}

else
{

	//while (input.LA(1) != input.EOF)

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
	}

	//cout << "line: " << lineNum << " char pos: " << _charPosInLine + 1 << endl;


	// now we can get the next token



		// convert current char to string
		string c = input.getText(antlr4::misc::Interval(input.index(), input.index()));

		// convert to char
		char* c1 = c.data();

		// start = stop = index()
		start = stop = input.index();

		initCharPos = _charPosInLine;

		// EASY SINGLE CHAR TOKENS {,},(,),;,*,&,],+
		if (c == "{" || c == "}" || c == "(" || c == ")" || c == ";" || c == "*" || c == "&" || c == "]" || c == "+")
		{
			switch (*c1)
			{
			case '{':
				type = L_CURLY;
				cout << " lcurly ";
				break;

			case '}':
				type = R_CURLY;
				cout << " rcurly ";
				break;

			case '(':
				type = L_PAREN;
				cout << " lparen ";
				break;

			case ')':
				type = R_PAREN;
				cout << " rparen ";
				break;

			case ';':
				type = SEMI_COLON;
				cout << " semicolon ";
				break;

			case '*':
				type = POINTER;
				cout << " star ";
				break;

			case '&':
				type = REFERENCE;
				cout << " ref ";
				break;

			case ']':
				type = R_BRACKET;
				cout << " rbrack ";
				break;

			case '+':
				type = PLUS;
				cout << " plus ";
				break;

			default:
				cout << "invalid type\n";
				break;

			}

			// consume the character
			outerConsume();

			text = c;
		}

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

					cout << " doubleEquals ";
				}

				else
				{
					type = SINGLE_EQUALS;

					cout << " equals ";
				}

				break;

			case '[':
				if (nextChar == ']')
				{
					isDouble = true;

					text = "[]";

					type = DOUBLE_BRACKETS;

					cout << " doublebrackets ";
				}

				else
				{
					type = L_BRACKET;

					cout << " lbracket ";
				}

				break;

			case '!':
				if (nextChar == '=')
				{
					isDouble = true;
					
					text = "!=";

					type = NOT_EQUAL;

					cout << " notequal ";
				}

				else
				{
					type = NOT;

					cout << " not ";
				}

				break;

			case '<':
				if (nextChar == '=')
				{
					isDouble = true;

					text = "<=";

					type = LESS_EQUAL;

					cout << " lessEqual ";
				}

				else
				{
					type = LESS;

					cout << " less ";
				}
				break;

			case '>':
				if (nextChar == '=')
				{
					isDouble = true;

					text = ">=";

					type = GREATER_EQUAL;

					cout << " greatEqual ";
				}

				else
				{
					type = GREATER;

					cout << " greater ";
				}
				break;

			default:
				cout << "invalid token\n";
				break;

			}

			if (isDouble)
			{
				stop = input.index() + 1;

				// consume second char
				outerConsume();
			}

			else
			{
				text = c;
			}

			// consume first char
			outerConsume();
		}

		// negative or minus
		else if (c == "-")
		{
			char prevChar = char(input.LA(-1));

			// check previous char, if it's a number, then it's subtraction, anything else it's negative
			if (isdigit(prevChar))
			{
				type = MINUS;

				cout << " minus ";

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

				cout << " negNum= ";

				cout << text;

				type = NUMBER;
			}
		}

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

				cout << " INT ";
			}

			else if (text == "main")
			{
				type = MAIN;

				cout << " MAIN ";
			}

			else if (text == "return")
			{
				type = RETURN;

				cout << " RETURN ";
			}

			else if (text == "mut")
			{
				type = MUT;

				cout << " MUT ";
			}

			else if (text == "new")
			{
				type = NEW;

				cout << " NEW ";
			}

			else if (text == "while")
			{
				type = WHILE;

				cout << " WHILE ";
			}

			else if (text == "if")
			{
				type = IF;

				cout << " IF ";
			}

			else if (text == "elif")
			{
				type = ELIF;

				cout << " ELIF ";
			}

			else if (text == "else")
			{
				type = ELSE;

				cout << " ELSE ";
			}

			else
			{
				type = ID;

				cout << " id= " << text;
			}
		}

		// number
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

			cout << " number= " << text;
		}

		else
		{
			cout << "invalid input to lexer \n";
		}


		cout << "\nline: " << lineNum << " char pos: " << initCharPos + 1 << endl;

		// convert token type from enum to size_t
		returnedType = type;

	}

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
	
}




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
}



/*
helper function to determine if a string is a number
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
























