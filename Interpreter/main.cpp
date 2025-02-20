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

using namespace std;


int main(int argc, char* argv[])
{
	//check for correct number of command line args
	/*if (argc != 2)
	{
		cerr << "Usage: inoxis.exe [file name]" << endl;

		exit(1);
	}*/

	// get file name from command line
	string file_name = argv[1];

	ifstream in;

	ofstream out;

	out.open("parse_tree_antlrLexer.txt");

	// open Inoxis file
	in.open(file_name);

	// check file has opened correctly
	if (!in.is_open())
	{
		cerr << "Error opening file\n";

		exit(1);
	}

	if (!out.is_open())
	{
		cerr << "Error opening file\n";

		exit(1);
	}

	antlr4::ANTLRInputStream input(in);



	//myLexer lexer(input);

	//while(!lexer.hitEndOfFile)
		//lexer.nextToken();

	InoxisLexer lexer(&input);

	antlr4::CommonTokenStream tokens(&lexer);

	InoxisParser parser(&tokens);

	antlr4::tree::ParseTree* tree = parser.main();

	auto s = tree->toStringTree(&parser);

	out << "Parse Tree: " << s << endl;


	return 0;
}