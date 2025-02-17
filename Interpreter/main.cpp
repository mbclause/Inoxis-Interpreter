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

	antlr4::ANTLRInputStream input(in);

	// test rig for antlr input stream

	/*int line = 1;

	int charPosInLine = 0;
	

	while (input.LA(1) != input.EOF)
	{
		//    /n is 10 in ascii
		if (input.LA(1) == 10)
		{
			line++;

			charPosInLine = 0;

			cout << endl;
		}

		else
		{

			charPosInLine++;

			cout << charPosInLine << " ";
		}

		//cout << input.getText(antlr4::misc::Interval(input.index(),input.index()));

		input.consume();
	}*/



	myLexer lexer(input);

	lexer.nextToken();

	//InoxisLexer lexer(&input);

	/*antlr4::CommonTokenStream tokens(&lexer);

	InoxisParser parser(&tokens);

	antlr4::tree::ParseTree* tree = parser.main();

	auto s = tree->toStringTree(&parser);*/

	//cout << "Parse Tree: " << s << endl;


	return 0;
}