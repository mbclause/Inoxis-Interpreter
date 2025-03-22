#include "antlr4-runtime.h"
#include ".antlr/InoxisBaseListener.h"
#include "funcSymbol.h"
#include "dataType.h"
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


/*
Ok, now we need some sort of scope stack which keeps track of which function we're in
*/




class symbolTable : public InoxisBaseListener
{
public:

	symbolTable() : numErrors(0) {};




	void enterFuncDec(InoxisParser::FuncDecContext* ctx);

	void enterFuncDef(InoxisParser::FuncDefContext* ctx);

	void enterVarDec(InoxisParser::VarDecContext* ctx);

	void enterMain(InoxisParser::MainContext* ctx);

	void enterVar(InoxisParser::VarContext* ctx);

	void enterFuncCall(InoxisParser::FuncCallContext* ctx);




	bool compFuncSignatures(funcSymbol func1, funcSymbol func2);

	void reportError() { numErrors++; };




	// need some error checking and tracking code
	int numErrors;

	map<string, funcSymbol> funcSymbols;

	funcSymbol  currentFunction;
};


