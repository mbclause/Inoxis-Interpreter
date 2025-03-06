/*
File: Interpreter.cpp
*/


// include statements
#include "Interpreter.h"



/*
Function: run
*/
void     Interpreter::run(antlr4::ANTLRInputStream input)
{
	myLexer lexer(input);

	//int numLexErrors = lexer.getErrorCount();

	//InoxisLexer lexer(&input);

	antlr4::CommonTokenStream tokens(&lexer);

	InoxisParser parser(&tokens);

	antlr4::tree::ParseTree* tree = parser.program();

	// pass this to VM object if there are no errors
	// if there are errors 

	auto s = tree->toStringTree(&parser);

	cout << "Parse Tree: " << s << endl;

	
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