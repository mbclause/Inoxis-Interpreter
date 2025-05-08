/*
File: symbolTable.h
Description: The class definition for the symbol table class, which inherits from the InoxisBaseListener class. 
This is one of the parse tree walker classes. 
It creates a symbol table of funcSymbol objects and validates the symbols.
*/

#pragma once
#include "antlr4-runtime.h"
#include ".antlr/InoxisBaseListener.h"
#include "funcSymbol.h"
#include "dataType.h"
#include <string>
#include <map>
#include <iostream>

using namespace std;





// class: symbolTable
// Inherits from InoxisBaseListener
class symbolTable : public InoxisBaseListener
{
public:

	// constructor
	symbolTable() : numErrors(0) {};


	// overloaded InoxisBaseListener functions
	void enterFuncDec(InoxisParser::FuncDecContext* ctx);

	void enterFuncDef(InoxisParser::FuncDefContext* ctx);

	void enterVarDec(InoxisParser::VarDecContext* ctx);

	void enterMain(InoxisParser::MainContext* ctx);

	void exitMain(InoxisParser::MainContext* ctx);

	void enterVar(InoxisParser::VarContext* ctx);

	void enterFuncCall(InoxisParser::FuncCallContext* ctx);

	void exitFuncDef(InoxisParser::FuncDefContext* ctx);



	// member functions
	bool compFuncSignatures(funcSymbol func1, funcSymbol func2);

	void reportError(antlr4::ParserRuleContext* ctx) { 
		size_t line = ctx->getStart()->getLine();
		cout << "Line " << line << ": ";
		numErrors++; 
	};




	// data members
	int numErrors;

	// ParseTreeProperty objects get saved in the tree itself
	antlr4::tree::ParseTreeProperty<funcSymbol>  treeFuncSymbols;

	map<string, funcSymbol> funcSymbols;

	antlr4::tree::ParseTreeProperty<vector<varSymbol>>  varListProp;

	vector<varSymbol>  variablesList;

	funcSymbol  currentFunction;
};


