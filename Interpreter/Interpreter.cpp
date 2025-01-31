/*
File: Interpreter.cpp
*/


// include statements
#include "Interpreter.h"
#include "Lexer.h"



/*
Function: run
*/
void Interpreter::run(string input)
{
	lexer(input);

	
}



/*
Function: lexer
*/
void Interpreter::lexer(string input)
{

}



/*
Function: report_error
*/
void Interpreter::report_error(ERROR_TYPE type, int line)
{
	string error_type;

	if (type == SYNTAX_ERROR)
		error_type = "SYNTAX ERROR";
	else
		error_type = "MEMORY SAFETY ERROR";

	cerr << error_type << " at line " << line << ".\n";

	error_count++;
}