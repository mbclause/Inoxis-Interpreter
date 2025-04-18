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

	varSymbol param(paramName, isMut, false, false, paramType, none, none, false, 0);

	//variablesList.push_back(param);



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
			reportError(ctx);

			cout << funcName << " has NOT been declared\n";
		}
	}

	else
	{
		reportError(ctx);

		cout << funcName << " has NOT been declared\n";
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
	//cout << argType << " " << calledFunc._paramType << endl;

	if (argType != calledFunc._paramType)
	{
		reportError(ctx);

		cout << "argument data type does not match parameter data type\n";
	}

	else
	{
		string paramName = calledFunc._paramName;

		varSymbol param(paramName, calledFunc.paramIsMut, needsMemSafety, isArray, argType, none, none, false, 0);

		funcSymbols[funcName].locals[paramName] = param;

		funcSymbols[funcName].variablesList.push_back(param);
	}

	//cout << funcName << " " << argDataTypeText << " " << argType << endl;

	// save the called function's info in the parse tree
	treeFuncSymbols.put(ctx, calledFunc);
}



void symbolTable::exitFuncDef(InoxisParser::FuncDefContext* ctx)
{
	string funcName = ctx->ID()->getText();

	funcSymbol function = funcSymbols[funcName];

	treeFuncSymbols.put(ctx, function);

	function = treeFuncSymbols.get(ctx);

	varListProp.put(ctx, variablesList);


}


void symbolTable::exitMain(InoxisParser::MainContext* ctx)
{
	string funcName = "main";

	funcSymbol function = funcSymbols[funcName];

	for (auto var: function.locals)
	{
		varSymbol v = var.second;

		v.printVarSymbol();
	}

	treeFuncSymbols.put(ctx, function);

	function = treeFuncSymbols.get(ctx);

	varListProp.put(ctx, variablesList);

	
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
}




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