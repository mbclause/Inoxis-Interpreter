/*
File: main
Description: Reads the Inoxis file name/path from the command line and then calls the interpreter master function.
*/

#include <iostream>
#include <fstream>
#include <string>

#include "antlr4-runtime.h"
#include ".antlr/InoxisLexer.h"
#include ".antlr/InoxisParser.h"
#include "misc/interval.h"

#include "myLexer.h"
#include "Interpreter.h"

using namespace std;

template class antlr4::tree::ParseTreeProperty<int>;



int main(int argc, char* argv[])
{
	//check for correct number of command line args
	if (argc != 2)
	{
		cerr << "Usage: Inoxis-Interpreter.exe [file name]" << endl;

		exit(1);
	}

	// get file name from command line
	string file_name = argv[1];

	ifstream in;

	// open Inoxis file
	in.open(file_name);

	// check file has opened correctly
	if (!in.is_open())
	{
		cerr << "Error opening file\n";

		exit(1);
	}

	

	antlr4::ANTLRInputStream input(in);

	Interpreter newInterpreter(input);


	return 0;
}