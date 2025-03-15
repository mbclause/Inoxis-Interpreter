#include "symbolTable.h"


/*
going to need to add more info to funcSymbol, mainly the type and name of the parameter, need to make
sure it matches with the definition
*/
void   symbolTable::enterFuncDec(InoxisParser::FuncDecContext* ctx)
{
	string funcName = ctx->ID()->getText();

	string paramName = ctx->param()->ID()->getText();

	string returnTypeText = ctx->pointRef()->getText();

	string paramTypeText = ctx->param()->pointRef()->getText();

	string mutText = ctx->param()->mut()->getText();

	DATA_TYPE returnType = INT;

	DATA_TYPE paramType = INT;

	bool isMut = false;

	if (returnTypeText == "*")
	{
		returnType = POINTER;
	}

	else if (returnTypeText == "&")
	{
		returnType = REF;
	}

	else
	{

	}

	if (paramTypeText == "*")
	{
		paramType = POINTER;
	}

	else if (paramTypeText == "&")
	{
		paramType = REF;
	}

	else
	{

	}

	if (mutText == "mut")
	{
		isMut = true;
	}



	cout << "in function declaration. Function name: " << funcName << "\nParam Name: " << paramName << 
		"\nreturn type: " << returnTypeText << endl;

	funcSymbol newFunction(funcName, paramName, isMut, returnType, paramType);

	funcSymbols[funcName] = newFunction;
}




void   symbolTable::enterFuncDef(InoxisParser::FuncDefContext* ctx)
{
	bool isDeclared = false;


	string funcName = ctx->ID()->getText();

	string paramName = ctx->param()->ID()->getText();

	string returnTypeText = ctx->pointRef()->getText();

	string paramTypeText = ctx->param()->pointRef()->getText();

	string mutText = ctx->param()->mut()->getText();

	DATA_TYPE returnType = INT;

	DATA_TYPE paramType = INT;

	bool isMut = false;

	if (returnTypeText == "*")
	{
		returnType = POINTER;
	}

	else if (returnTypeText == "&")
	{
		returnType = REF;
	}

	else
	{

	}

	if (paramTypeText == "*")
	{
		paramType = POINTER;
	}

	else if (paramTypeText == "&")
	{
		paramType = REF;
	}

	else
	{

	}

	if (mutText == "mut")
	{
		isMut = true;
	}



	funcSymbol funcDef(funcName, paramName, isMut, returnType, paramType);



	if (funcSymbols.count(funcName) == 1)
	{
		funcSymbol funcDec = funcSymbols[funcName];

		if (compFuncSignatures(funcDef, funcDec))
		{
			isDeclared = true;

			cout << funcName << " has been declared\n";
		}
	}

	else
	{
		cout << funcName << " has NOT been declared\n";
	}
}




bool compFuncSignatures(funcSymbol func1, funcSymbol func2)
{
	return false;
}