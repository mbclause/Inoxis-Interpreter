#include "antlr4-runtime.h"
#include ".antlr/InoxisBaseListener.h"
#include "funcSymbol.h"
#include <string>
#include <map>
#include <iostream>

using namespace std;

/*
Need to write functions (not sure whether enter/exit for all of them):

enterFuncDef (add function to symbol table)

enterfuncCall (check symbol table)

enterfuncDef (check symbol table)

enterParam (add param id to symbol table for function)

enterVarDec (add variable to function symbol table, add appropriate info about whether it's mut or not)

enterVar (check symbol table)




enterassignRHS (check whether variable is mut or not, if there's allocation, update memSafety info for variable)
*/



class symbolTable : public InoxisBaseListener
{
	map<string, funcSymbol> funcSymbols;

	void enterFuncDec(InoxisParser::FuncDecContext* ctx);

	void enterFuncDef(InoxisParser::FuncDefContext* ctx);

	bool compFuncSignatures(funcSymbol func1, funcSymbol func2);

	// need some error checking and tracking code
};


