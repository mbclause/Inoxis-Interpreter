#include "symbolTable.h"


/*
going to need to add more info to funcSymbol, mainly the type and name of the parameter, need to make
sure it matches with the definition
*/
void   symbolTable::enterFuncDec(InoxisParser::FuncDecContext* ctx)
{
	string funcName = ctx->ID()->getText();

	cout << "in function declaration. Function name: " << funcName << endl;

	funcSymbol newFunction(funcName);

	funcSymbols[funcName] = newFunction;
}




void   symbolTable::enterFuncDef(InoxisParser::FuncDefContext* ctx)
{
	string funcName = ctx->ID()->getText();

	if (funcSymbols.count(funcName) > 0)
	{
		cout << funcName << " has been defined\n";
	}

	else
	{
		cout << funcName << " has NOT been defined\n";
	}
}