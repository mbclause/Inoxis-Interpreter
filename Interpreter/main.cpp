/*
File: main
Description: Reads the Inoxis file name/path from the command line and then calls the interpreter master function.
*/

#include <iostream>
#include <fstream>
#include <string>

#include "antlr4-runtime.h"

using namespace std;


int main(int argc, char* argv[])
{
	//check for correct number of command line args
	if (argc != 2)
	{
		cerr << "Usage: inoxis.exe [file name]" << endl;

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

	// interpret the program in the file, passed as file stream, right now this will just do lexical analysis on the program
	// and print out the list of tokens
	// interpret(in)


	return 0;
}