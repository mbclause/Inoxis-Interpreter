#include "symbolTable.h"


/*
going to need to add more info to funcSymbol, mainly the type and name of the parameter, need to make
sure it matches with the definition
*/
void   symbolTable::enterFuncDec(InoxisParser::FuncDecContext* ctx)
{
	string funcName = ctx->ID()->getText();

	// check that the function name isn't already in funcSymbols
	if (funcSymbols.count(funcName) == 1)
	{
		reportError();

		cout << "Function name: " << funcName << " already declared.\n";

		return;
	}


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



	//cout << "in function declaration. Function name: " << funcName << "\nParam Name: " << paramName << 
		//"\nreturn type: " << returnTypeText << endl;

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

		else
		{
			cout << funcName << " has NOT been declared\n";

			reportError();
		}
	}

	else
	{
		cout << funcName << " has NOT been declared\n";

		reportError();
	}

	if (isDeclared)
	{
		currentFunction = funcDef;

		// use ctx to get the names of every variable declared in the function body and add them to locals
		



		// need to add code to add the parameter to the locals hashmap, problem is, I don't know
		// how to do the memory safety stuff, because this depends on what's passed to in the function call
		// this would only matter if the parameter is a pointer or reference

		// use the varSymbol ctor to pass in the parameter name, data type, and isMutable
		// then add the varSymbol to the locals
		// I think I'm going to need a separate table that keeps track of heep memory accesses
	}
}


void symbolTable::enterMain(InoxisParser::MainContext* ctx)
{
	funcSymbol main("main", "", false, INT, INT);

	currentFunction = main;
}



void symbolTable::enterVarDec(InoxisParser::VarDecContext* ctx)
{
	funcSymbol parentFunc = currentFunction;

	// get name, mut, and whether there's an allocation 
	// do I need to store whether it's a pointer/reference/array?
	
	// then check parentFunc locals to see if the name conflicts with another local
}




bool symbolTable::compFuncSignatures(funcSymbol func1, funcSymbol func2)
{
	bool sameFunc = false;

	if (func1._paramName == func2._paramName)
		if (func1.paramIsMut == func2.paramIsMut)
			if (func1._returnType == func2._returnType)
				if (func1._paramType == func2._paramType)
					sameFunc = true;

	return sameFunc;
}