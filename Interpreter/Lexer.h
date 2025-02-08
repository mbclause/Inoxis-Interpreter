/*
Plan for integrating my lexer class with antlr:
1. have my lexer class inherit from the TokenSource antlr class.
2. since nextToken() is a virtual function, I'll make my own definition for that.
3. write the rest of my lexer
4. use antlr's Token class for tokens
5. pass my lexer to CommonTokenStream constructor
6. This will generate the proper input for the antlr parser
7. I also need to use the proper intput file stream 

*/




#include <string>
#include <vector>
#include "antlr4-runtime.h"

using namespace std;

class Lexer : public antlr4::TokenSource
{
public:
	Lexer(string in) { input = in; };

	//vector<antlr4::Token> tokens;

	string input;

	//std::unique_ptr<antlr4::Token> nextToken() override;



	//vector<antlr4::Token> ScanTokens();
};