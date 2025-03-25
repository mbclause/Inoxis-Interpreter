#pragma once
#include "antlr4-runtime.h"
#include ".antlr/InoxisBaseListener.h"
#include "symbolTable.h"
#include "dataType.h"
#include <string>
#include <map>
#include <iostream>

using namespace std;
using namespace antlr4::tree;




// Class Definition: MemSafetyPass
class MemSafetyPass : public InoxisBaseListener
{
public:
	// ctors
	MemSafetyPass(ParseTreeProperty<funcSymbol> funcs) : functions(funcs), _numErrors(0) {};

	MemSafetyPass() : _numErrors(0) {};


	//void enterFuncDef(InoxisParser::FuncDefContext* ctx);

	//assign: var '=' assignRHS ';';
	void enterAssign(InoxisParser::AssignContext* ctx);

	void enterFuncDef(InoxisParser::FuncDefContext* ctx) {
		currentFunction = functions.get(ctx);
	}

	void enterMain(InoxisParser::MainContext* ctx) {
		currentFunction = functions.get(ctx);
	}


	void reportMemError() { _numErrors++; };


	// data members
	ParseTreeProperty<funcSymbol> functions;

	int _numErrors;

	funcSymbol currentFunction;
};