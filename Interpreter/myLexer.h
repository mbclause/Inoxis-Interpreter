/*
Plan for integrating my lexer class with antlr:
1. have my lexer class inherit from the TokenSource antlr class.
2. since nextToken() is a virtual function, I'll make my own definition for that.
3. write the rest of my lexer
4. use antlr's Token class for tokens
5. pass my lexer to CommonTokenStream constructor
6. This will generate the proper input for the antlr parser
7. I also need to use the proper intput file stream 


What if I ran the lexer, which would return a vector filled with all of the tokens. Then, nextToken would just return the next token in the vector,
I suppose I could keep an index variable that I could update.
*/




#include <string>
#include <vector>
#include "antlr4-runtime.h"

using namespace std;



/// A source of tokens must provide a sequence of tokens via nextToken()
/// and also must reveal it's source of characters; CommonToken's text is
/// computed from a CharStream; it only store indices into the char
/// stream.
/// 
/// Errors from the lexer are never passed to the parser. Either you want to keep
/// going or you do not upon token recognition error. If you do not want to
/// continue lexing then you do not want to continue parsing. Just throw an
/// exception not under RecognitionException and Java will naturally toss
/// you all the way out of the recognizers. If you want to continue lexing then
/// you should not throw an exception to the parser--it has already requested a
/// token. Keep lexing until you get a valid one. Just report errors and keep
/// going, looking for a valid token.

class myLexer : public antlr4::TokenSource
{
public:
	// constructors
	myLexer(antlr4::ANTLRInputStream in) { input = in; };


	// data members
	// Life cycle of a token is this:
	// Created by emit() (via the token factory) or by action code, holding ownership of it.
	// Ownership is handed over to the token stream when calling nextToken().


	antlr4::ANTLRInputStream input;

	// index into the tokens vector
	int index = 0;

	/// Return a Token object from your input stream (usually a
	/// CharStream). Do not fail/return upon lexing error; keep chewing
	/// on the characters until you get a good one; errors are not passed through
	/// to the parser.
	/// 
	/// 
	/// return the next token stored in the tokens vector, incrementing the index
	std::unique_ptr<antlr4::Token> nextToken() override;



	// overriden functions from TokenSource

	size_t getLine() const override;

	size_t getCharPositionInLine() override;

	antlr4::CharStream* getInputStream() override { return &input; };

	std::string getSourceName() override { return input.name; };

	antlr4::TokenFactory<antlr4::CommonToken>* getTokenFactory() override;
};