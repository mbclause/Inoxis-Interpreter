/*
File: myLexer.h
Description: The class definition for the myLexer class. It inherits from the antlr4 TokenSource class.
*/

#ifndef MYLEXER_H
#define MYLEXER_H

#include <iostream>
#include <string>
#include <vector>
#include "antlr4-runtime.h"

using namespace std;



/// Class: myLexer
/// 
/// Parent Class: TokenSource
/// 
/// Description for a TokenSource class:
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
/// 

class myLexer : public antlr4::TokenSource
{
public:
	// token type enum, the integer values match those of the Inoxis.tokens file generated by ANTLR from the grammar
	// only the integer values will be passed to token object
	enum TOKEN_TYPE {
		T__0, INT_TYPE, MAIN, L_PAREN, R_PAREN, L_CURLY, R_CURLY, SEMI_COLON, SINGLE_EQUALS,
		COUT, EXTRACT_OP, END_LINE, RETURN, MUT, POINTER, REFERENCE, 
		DOUBLE_BRACKETS, L_BRACKET, R_BRACKET, 
		NEW, PLUS, MINUS, WHILE, IF, ELIF, ELSE, NOT, LESS, GREATER, DOUBLE_EQUALS, 
		LESS_EQUAL, GREATER_EQUAL, NOT_EQUAL,WS, ID, COMMENT, NUMBER, STR_LITERAL
	};


	// constructors
	myLexer(antlr4::ANTLRInputStream in);


	// data members
	// the input file stream
	antlr4::ANTLRInputStream input;

	// not used in myLexer but required for TokenSource
	antlr4::TokenFactory<antlr4::CommonToken>  *factory;

	// current line number in input stream
	size_t lineNum;

	// current char index in line
	size_t _charPosInLine;

	bool hitEndOfFile;

	int errorCount;



	/// Return a Token object from your input stream (usually a
	/// CharStream). Do not fail/return upon lexing error; keep chewing
	/// on the characters until you get a good one; errors are not passed through
	/// to the parser.
	std::unique_ptr<antlr4::Token> nextToken() override;



	// overriden functions from TokenSource

	/// Get the line number for the current position in the input stream. The
	/// first line in the input is line 1.
	/// 
	/// Returns the line number for the current position in the input stream, or
	/// 0 if the current token source does not track line numbers
	size_t getLine() const override {return lineNum;};

	/// Get the index into the current line for the current position in the input
	/// stream. The first character on a line has position 0.
	/// 
	size_t getCharPositionInLine() override {return _charPosInLine;};

	antlr4::CharStream* getInputStream() override { return &input; };

	std::string getSourceName() override { return input.name; };

	antlr4::TokenFactory<antlr4::CommonToken>* getTokenFactory() override {return factory;};



	// helper functions
	void newLine() { lineNum++; _charPosInLine = 0; };

	// consume char in input stream and increment char pos index in line
	void outerConsume() {input.consume(); _charPosInLine++;};

	int getErrorCount() { return errorCount; };

	void report_error(char token) {
		cerr << "Lexer error: invalid character ' " << token << " ' at " << lineNum << ": " << _charPosInLine << endl; 
		errorCount++;
	};
};

#endif