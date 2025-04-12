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
		ParseTreeProperty<funcSymbol> _symbolTables) : statLists(_statLists), 
		symbolTables(_symbolTables), statementIndex(0) { };


	// ENTER_RULE
	// funcDec (add to functions, add parameter to symbols)
	// funcDef (set current statList)
	void enterFuncDef(InoxisParser::FuncDefContext* ctx) {
		cout << endl << ctx->ID()->getText() << endl;
		currentStatList = statLists.get(ctx); }
	
	// main (set current statlist)
	void enterMain(InoxisParser::MainContext* ctx) { cout << "\nmain\n"; currentStatList = statLists.get(ctx); }
	
	// need these to build up expressions
	// enter numLiteral
	
	// varLiteral

	// funcCallSubRule

	// add

	// subtract

	// rhsRef

	// condition


	// statement types
	// varDec

	// assign

	// print

	// funcCall

	// return
	
	// control flow
	// ifElseBlock

	// elif

	// else

	// while

	// EXIT RULE
	// funcDef (add statements)??
	void exitMain(InoxisParser::MainContext* ctx) { statementIndex = 0; }

	void exitFuncDef(InoxisParser::FuncDefContext* ctx) { statementIndex = 0; }

	// exit statement (increment statList)

	// also add statement to the function statements??
	void exitStatement(InoxisParser::StatementContext* ctx) { incrementStatements(); };

	void exitReturn(InoxisParser::ReturnContext* ctx) { incrementStatements(); };


	// need to have similar incrementStatList function to see when we reach sentinal for pointer var
	// then we would add a free statement for that var to the statements

	void test();

	void  incrementStatements();


	// data members
	vector<variant<InoxisParser::StatementContext*, sentinal, InoxisParser::ReturnContext*>> currentStatList;

	int statementIndex;

	ParseTreeProperty<vector<variant<InoxisParser::StatementContext*, sentinal, InoxisParser::ReturnContext*>>> statLists;

	// do I need this??
	ParseTreeProperty<funcSymbol>  symbolTables;
};