#include "myLexer.h"






std::unique_ptr<antlr4::Token> myLexer::nextToken() {
	if (index < tokens.size())
	{
		index++;
		return std::move(tokens[index - 1]);
	}

	else
	{
		cerr << "ran out of tokens\n";
		exit(1);
	}
}























size_t     myLexer::getLine() const
{

}




size_t     myLexer::getCharPositionInLine()
{

}




antlr4::TokenFactory<antlr4::CommonToken>*    myLexer::getTokenFactory()
{

}