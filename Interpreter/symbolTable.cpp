/*
File: symbolTable.cpp
Description: The member function definitions for the symbolTable class. 
Most of these are overridden functions from InoxisBaseListener. 
It includes an enterRule and exitRule function for each parser rule in the Inoxis grammar. 
They are called when rules are entered and exited while walking the AST.
*/

#include "symbolTable.h"
using namespace DataType;



/*
Function: enterFuncDec
Description: gets the function signature for the function declaration and uses it to create a funcSymbol object
*/
void   symbolTable::enterFuncDec(InoxisParser::FuncDecContext* ctx)
{
	// get the function name, param name and data type, return type, and whether the parameter is mutable
	string funcName = ctx->ID()->getText();

	// check that the function name isn't already in funcSymbols
	if (funcSymbols.count(funcName) == 1)
	{
		reportError(ctx);

		cout << funcName << " already declared.\n";

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

	// create a new funcSymbol object and add it to the funcSymbols hash table
	funcSymbol newFunction(funcName, paramName, isMut, returnType, paramType);

	funcSymbols[funcName] = newFunction;
} // end enterFuncDec



/*
Function: enterFuncDef
Description: check that the function has been declared by checking the funcSymbols table, then add the parameter
to the function's local variables table
*/
void   symbolTable::enterFuncDef(InoxisParser::FuncDefContext* ctx)
{
	// get the function signature for the definition
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

	bool isArray = false;

	int arraySize = 0;

	if (ctx->param()->paramArray()->getText().size() > 0)
	{
		isArray = true;

		arraySize = stoi(ctx->param()->paramArray()->INT()->getText());
	}



	funcSymbol funcDef(funcName, paramName, isMut, returnType, paramType);


	// check that the function has been declared
	if (funcSymbols.count(funcName) == 1)
	{
		funcSymbol funcDec = funcSymbols[funcName];

		if (compFuncSignatures(funcDef, funcDec))
		{
			isDeclared = true;
		}

		else
		{
			reportError(ctx);

			cout << funcName << " has NOT been declared\n";
		}
	}

	else
	{
		reportError(ctx);

		cout << funcName << " has NOT been declared\n";
	}

	// add the parameter to locals
	if (isDeclared)
	{
		currentFunction = funcSymbols[funcName];

		varSymbol param(paramName, isMut, false, isArray, paramType, none, none, false, arraySize);

		variablesList.push_back(param);

		funcSymbols[funcName].locals[paramName] = param;
	}
} // end enterFuncDef



/*
Function: enterMain
Description: simply add a function called "main" to the funcSymbols table
*/
void symbolTable::enterMain(InoxisParser::MainContext* ctx)
{
	funcSymbol main("main", "", false, INT, INT);

	funcSymbols["main"] = main;

	currentFunction = funcSymbols["main"];
}



/*
Function: enterFuncCall
Description: First check that the function called has been declared. Also check that the argument has been declared.
Then check that the argument and parameter data types match.
*/
void symbolTable::enterFuncCall(InoxisParser::FuncCallContext* ctx)
{
	// get all of the funcCall info
	string funcName = ctx->ID()->getText();

	string currentFuncName = currentFunction.getName();

	funcSymbol currentFunc = funcSymbols[currentFuncName];

	if (funcSymbols.count(funcName) != 1)
	{
		reportError(ctx);

		cout << funcName << " has NOT been declared\n";

		return;
	}

	funcSymbol calledFunc = funcSymbols[funcName];


	string argName = "";

	string argDataTypeText = "";

	DATA_TYPE argType = INT;

	bool argIsInt = false;

	bool needsMemSafety = false;

	bool isArray = false;

	if (ctx->arg()->INT() != NULL)
	{
		argType = INT;

		argIsInt = true;
	}

	else
	{
		if (ctx->arg()->var() != NULL)
		{

			if (ctx->arg()->var()->pointRef() != NULL)
			{
				argDataTypeText = ctx->arg()->var()->pointRef()->getText();

				if (argDataTypeText == "&")
					argType = REF;
				else if(argDataTypeText == "*")
					argType = POINTER;
			}
		}
	}

	if (!argIsInt)
	{
		if (ctx->arg()->var() != NULL)
		{
			argName = ctx->arg()->var()->ID()->getText();

			if (currentFunc.locals.count(argName) != 1)
			{
				reportError(ctx);

				cout << "argument has not been declared\n";
			}

			varSymbol varArg = currentFunc.locals[argName];

			// if the variable is already a pointer/reference/array, 
			// we don't want any extra point/ref symbols passed in
			if (varArg._isArray || varArg.dataType == POINTER || varArg.dataType == REF)
			{

				if (argType != INT)
				{
					reportError(ctx);

					cout << "argument is already a pointer or reference\n";
				}

				if (varArg._needsMemSafety)
					needsMemSafety = true;

				if (varArg._isArray)
					isArray = true;

				argType = varArg.dataType;
			}
		}
	}

	// i need to compare the argument data type with the data type of the parameter
	// or maybe I need to get the variable data type and compare THAT to the parameter data type
	// then, i could use this info to add the proper PARAM variable to that functions locals,
	// with all of the proper memory info

	if (argType != calledFunc._paramType)
	{
		reportError(ctx);

		cout << "argument data type does not match parameter data type\n";
	}

	else
	{
		string paramName = calledFunc._paramName;

		varSymbol param(paramName, calledFunc.paramIsMut, needsMemSafety, isArray, argType, none, none, false, 0);
	}
} // end enterFuncCall



/*
Function: exitFuncDef
Description: store the funcSymbol object for the current function in the parse tree
*/
void symbolTable::exitFuncDef(InoxisParser::FuncDefContext* ctx)
{
	string funcName = ctx->ID()->getText();

	funcSymbol function = funcSymbols[funcName];

	treeFuncSymbols.put(ctx, function);

	varListProp.put(ctx, variablesList);

	variablesList.clear();
} // end exitFuncDef




/*
Function: exitMain
Description: same as exitFuncDef, but for main
*/
void symbolTable::exitMain(InoxisParser::MainContext* ctx)
{
	string  funcName = "main";

	funcSymbol function = funcSymbols[funcName];

	treeFuncSymbols.put(ctx, function);

	function = treeFuncSymbols.get(ctx);

	varListProp.put(ctx, variablesList);

	variablesList.clear();
}



/*
Function: enterVarDec
Description: create a varSymbol object with the declared var's info, then add it to the locals table for current
function.
*/
void symbolTable::enterVarDec(InoxisParser::VarDecContext* ctx)
{
	funcSymbol parentFunc = currentFunction;

	// get name, mut, and whether there's an allocation 
	// do I need to store whether it's a pointer/reference/array?
	string name = ctx->ID()->getText();
	
	// then check parentFunc locals to see if the name conflicts with another local
	if (currentFunction.locals.count(name) != 0)
	{
		reportError(ctx);

		cout << "variable name conflict with: " << name << endl;

		return;
	}

	bool needsMemSafety = false;

	string mutText = ctx->mut()->getText();

	string arrayText = ctx->array()->getText();

	if(ctx->varDecRHS() != NULL)
		if(ctx->varDecRHS()->assignRHS() != NULL)
			if (ctx->varDecRHS()->assignRHS()->allocate() != NULL)
				needsMemSafety = true;
		

	string dataTypeText = ctx->pointRef()->getText();

	bool isMut = false;

	bool isArray = false;

	int arraySize = 0;

	DATA_TYPE dataType = INT;

	if (mutText == "mut")
	{
		isMut = true;
	}

	if (!arrayText.empty())
	{
		isArray = true;

		// get the array size
		arraySize = stoi(ctx->array()->index()->getText());
	}

	if (dataTypeText == "*")
		dataType = POINTER;

	else if (dataTypeText == "&")
		dataType = REF;

	

	if (dataType != POINTER && needsMemSafety)
	{
		reportError(ctx);

		cout << "cannot allocate heap memory to a non-pointer\n";

		return;
	}

	varSymbol newVar(name, isMut, needsMemSafety, isArray, dataType, none, none, false, arraySize);

	funcSymbols[parentFunc.getName()].locals[name] = newVar;

	newVar = funcSymbols[parentFunc.getName()].locals[name];

	variablesList.push_back(newVar);

	currentFunction = funcSymbols[parentFunc.getName()];
} // end enterVarDec




/*
Function: enterVar
Description: check that the variable has been declared by looking up the name in the currentFunc.locals table.
*/
void symbolTable::enterVar(InoxisParser::VarContext* ctx)
{
	string currentFuncName = currentFunction.getName();

	funcSymbol parentFunc = funcSymbols[currentFuncName];

	string name = ctx->ID()->getText();

	if (parentFunc.locals.count(name) != 1)
	{
		reportError(ctx);

		cout << "Variable: " << name << " has not been declared" << endl;

		return;
	}
} // end enterVar




/*
Function: compFuncSignartures
Description: given two funcSymbol objects, check if they are the same and return true or false.
*/
bool symbolTable::compFuncSignatures(funcSymbol func1, funcSymbol func2)
{
	bool sameFunc = false;

	if (func1._paramName == func2._paramName)
		if (func1.paramIsMut == func2.paramIsMut)
			if (func1._returnType == func2._returnType)
				if (func1._paramType == func2._paramType)
					sameFunc = true;

	return sameFunc;
} // end compFuncSignatures