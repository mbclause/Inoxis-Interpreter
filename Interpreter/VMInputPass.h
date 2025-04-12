/*
File: VMInputPass.h
Description: This class will walk the AST and for each function 
*/

#pragma once
#include "antlr4-runtime.h"
#include ".antlr/InoxisBaseListener.h"
#include "symbolTable.h"
#include "dataType.h"
#include "MemSafetyPass.h"
#include "VMInput.h"
#include <string>
#include <variant>
#include <map>
#include <iostream>

using namespace std;
using namespace antlr4::tree;


class VMInputPass : public InoxisBaseListener
{
public:
	VMInputPass(ParseTreeProperty<vector<variant<InoxisParser::StatementContext*, sentinal,
		InoxisParser::ReturnContext*>>> _statLists, 
		ParseTreeProperty<funcSymbol> _symbolTables) : statLists(_statLists), symbolTables(_symbolTables) { };


	// enter rules
	// enter each statement type
	// enter return
	// enter varDec


	// need to have similar incrementStatList function to see when we reach sentinal for pointer var
	// then we would add a free statement for that var to the statements

	void test();

	ParseTreeProperty<vector<variant<InoxisParser::StatementContext*, sentinal, InoxisParser::ReturnContext*>>> statLists;

	ParseTreeProperty<funcSymbol>  symbolTables;
};