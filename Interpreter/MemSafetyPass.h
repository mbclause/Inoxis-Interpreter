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


	void enterFuncDef(InoxisParser::FuncDefContext* ctx) {
		string funcName = ctx->ID()->getText();

		funcSymbol function = functions.get(ctx);

		cout << function.getName() << endl;

		for (auto x : function.locals)
		{
			varSymbol var = x.second;

			var.printVarSymbol();
		}
	};


	// data members
	ParseTreeProperty<funcSymbol> functions;

	int _numErrors;
};