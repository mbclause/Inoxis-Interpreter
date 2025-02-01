
#include <string>
#include <vector>
#include "Token.h"
#include "antlr4-runtime.h"

using namespace std;

class Lexer
{
public:
	Lexer(string in) { input = in; };

	antlr4::CommonTokenStream tokens;

	string input;

	antlr4::CommonTokenStream ScanTokens();
};