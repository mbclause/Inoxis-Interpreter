/*
File: Token.h
*/

#include "Token_Type.h"
#include <string>

using namespace std;


// Token class definition
class Token
{
	// data members
	TOKEN_TYPE type;

	string  value;

	// default ctor
	Token(TOKEN_TYPE t, string val) { type = t; value = val; };
};
