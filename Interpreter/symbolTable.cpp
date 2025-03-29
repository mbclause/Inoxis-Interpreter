#include "symbolTable.h"
using namespace DataType;



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

			//cout << funcName << " has been declared\n";
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
		currentFunction = funcSymbols[funcName];

		/*for (auto x : currentFunction.locals)
		{
			varSymbol var = x.second;

			var.printVarSymbol();
		}*/
	}
}


void symbolTable::enterMain(InoxisParser::MainContext* ctx)
{
	funcSymbol main("main", "", false, INT, INT);

	funcSymbols["main"] = main;

	currentFunction = funcSymbols["main"];
}



void symbolTable::enterFuncCall(InoxisParser::FuncCallContext* ctx)
{
	string funcName = ctx->ID()->getText();

	string currentFuncName = currentFunction.getName();

	funcSymbol currentFunc = funcSymbols[currentFuncName];

	if (funcSymbols.count(funcName) != 1)
	{
		cout << funcName << " has NOT been declared\n";

		reportError();

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
				cout << "argument has not been declared\n";

				reportError();
			}

			varSymbol varArg = currentFunc.locals[argName];

			// if the variable is already a pointer/reference/array, 
			// we don't want any extra point/ref symbols passed in
			if (varArg._isArray || varArg.dataType == POINTER || varArg.dataType == REF)
			{

				if (argType != INT)
				{
					cout << "argument is already a pointer or reference\n";

					reportError();
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
	//cout << argType << " " << calledFunc._paramType << endl;

	if (argType != calledFunc._paramType)
	{
		cout << "argument data type does not match parameter data type\n";

		reportError();
	}

	else
	{
		string paramName = calledFunc._paramName;

		varSymbol param(paramName, calledFunc.paramIsMut, needsMemSafety, isArray, argType, none, none, false);

		funcSymbols[funcName].locals[paramName] = param;
	}

	//cout << funcName << " " << argDataTypeText << " " << argType << endl;
}



void symbolTable::exitFuncDef(InoxisParser::FuncDefContext* ctx)
{
	string funcName = ctx->ID()->getText();

	funcSymbol function = funcSymbols[funcName];

	treeFuncSymbols.put(ctx, function);

	function = treeFuncSymbols.get(ctx);

	/*cout << function.getName() << endl;

	for (auto x : function.locals)
	{
		varSymbol var = x.second;

		var.printVarSymbol();
	}*/
}


void symbolTable::exitMain(InoxisParser::MainContext* ctx)
{
	string funcName = "main";

	funcSymbol function = funcSymbols[funcName];

	treeFuncSymbols.put(ctx, function);

	function = treeFuncSymbols.get(ctx);

	/*cout << "main\n";

	for (auto x : function.locals)
	{
		varSymbol var = x.second;

		var.printVarSymbol();
	}*/
}



void symbolTable::enterVarDec(InoxisParser::VarDecContext* ctx)
{
	funcSymbol parentFunc = currentFunction;

	// get name, mut, and whether there's an allocation 
	// do I need to store whether it's a pointer/reference/array?
	string name = ctx->ID()->getText();
	
	// then check parentFunc locals to see if the name conflicts with another local
	if (currentFunction.locals.count(name) != 0)
	{
		reportError();

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

	DATA_TYPE dataType = INT;

	if (mutText == "mut")
	{
		isMut = true;
	}

	if (!arrayText.empty())
		isArray = true;

	if (dataTypeText == "*")
		dataType = POINTER;

	else if (dataTypeText == "&")
		dataType = REF;

	

	if (dataType != POINTER && needsMemSafety)
	{
		cout << "cannot allocate heap memory to a non-pointer\n";

		reportError();

		return;
	}

	varSymbol newVar(name, isMut, needsMemSafety, isArray, dataType, none, none, false);

	funcSymbols[parentFunc.getName()].locals[name] = newVar;

	newVar = funcSymbols[parentFunc.getName()].locals[name];
}




void symbolTable::enterVar(InoxisParser::VarContext* ctx)
{
	string currentFuncName = currentFunction.getName();

	funcSymbol parentFunc = funcSymbols[currentFuncName];

	string name = ctx->ID()->getText();

	if (parentFunc.locals.count(name) != 1)
	{
		reportError();

		cout << "Variable: " << name << " has not been declared" << endl;

		return;
	}
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