/*
File: Interpreter.h
*/

// include statements
#include <string>
#include <vector>
#include <iostream>
#include "antlr4-runtime.h"
#include "myLexer.h"
#include ".antlr/InoxisLexer.h"
#include ".antlr/InoxisParser.h"
#include "misc/interval.h"
#include "symbolTable.h"
#include "MemSafetyPass.h"

using namespace std;

// enum type for error reporting
enum ERROR_TYPE { SYNTAX_ERROR, MEM_SAFETY_ERROR };


// Interpreter class definition
class Interpreter
{
public:
	// default ctor
	Interpreter(antlr4::ANTLRInputStream input) { run(input); error_count = 0; };

	// data members

	int error_count;

	symbolTable symTable;

	// member functions
	void run(antlr4::ANTLRInputStream input);

	void report_error(ERROR_TYPE type, int line);
};
