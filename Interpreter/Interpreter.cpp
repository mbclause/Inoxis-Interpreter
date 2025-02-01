/*
File: Interpreter.cpp
*/


// include statements
#include "Interpreter.h"
#include "Lexer.h"
#include <iostream>



/*
Function: run
*/
void Interpreter::run(string input)
{
	Lexer lexer(input);

	antlr4::CommonTokenStream tokens = lexer.ScanTokens();

	
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