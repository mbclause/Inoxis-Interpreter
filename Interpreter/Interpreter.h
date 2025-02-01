/*
File: Interpreter.h
*/

// include statements
#include <string>
#include <vector>
#include "Token.h"
#include "antlr4-runtime.h"

using namespace std;

// enum type for error reporting
enum ERROR_TYPE { SYNTAX_ERROR, MEM_SAFETY_ERROR };


// Interpreter class definition
class Interpreter
{
	// default ctor
	Interpreter(string input) { run(input); error_count = 0; };

	// data members

	int error_count;

	// member functions
	void run(string input);

	void report_error(ERROR_TYPE type, int line);
};
