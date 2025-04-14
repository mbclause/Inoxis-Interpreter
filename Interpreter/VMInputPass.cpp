#include "VMInputPass.h"


/*
Function: exitNumLiteral
Description: get the number and create a new literal struct with it, then add it to the rule context for it's parent
*/
void VMInputPass::exitNumLiteral(InoxisParser::NumLiteralContext* ctx)
{
	// get the number
	int num = stoi(ctx->INT()->getText());

	literal numLiteral;

	numLiteral.number = num;

	expression exp = initLiteralExpression(numLiteral);

	//cout << exp.val.litVal.number << endl;

	expProp.put(ctx, exp);
}



/*
Function: exitVarLiteral
Description: lookup index for variable in locals garray, use that to create an expression and pass it up
*/
void VMInputPass::exitVarLiteral(InoxisParser::VarLiteralContext* ctx)
{
	string varName = ctx->var()->ID()->getText();

	unsigned varIndex = currentLocalsMap[varName];

	literal varLiteral;

	varLiteral.varIndex = varIndex;

	expression exp = initLiteralExpression(varLiteral);

	expProp.put(ctx, exp);
}



/*
Function: exitAdd
Description: get the two expression operands and store them in a new BinOp expression
*/
void VMInputPass::exitAdd(InoxisParser::AddContext* ctx)
{
	expression left = expProp.get(ctx->expression(0));

	expression* leftPtr = makeExpression(left);

	expression right = expProp.get(ctx->expression(1));

	expression* rightPtr = makeExpression(right);

	BinOp* newBinOp = makeBinOp(ADD, leftPtr, rightPtr);

	// nestle data into ast
	binaryOpProp.put(ctx, *newBinOp);

	// free the binOp pointer
	freeBinOp(newBinOp);

	//cout << left.val.litVal.number << " + " << right.val.litVal.number << endl;
}



/*
Function: exitSubtract
Description: same as addition, just change OP
*/
void VMInputPass::exitSubtract(InoxisParser::SubtractContext* ctx)
{
	expression left = expProp.get(ctx->expression(0));

	expression* leftPtr = makeExpression(left);

	expression right = expProp.get(ctx->expression(1));

	expression* rightPtr = makeExpression(right);

	BinOp* newBinOp = makeBinOp(SUBTRACT, leftPtr, rightPtr);

	// nestle data into ast
	binaryOpProp.put(ctx, *newBinOp);

	// free the binOp pointer
	freeBinOp(newBinOp);
}



/*
Function: enterFuncDef
Description: 
*/
void VMInputPass::enterFuncDef(InoxisParser::FuncDefContext* ctx)
{
	cout << endl << ctx->ID()->getText() << endl;

	GArray*  localSymbols = g_array_new(false, false, sizeof(unsigned));

	// get the function symbol
	funcSymbol currentFunction = symbolTables.get(ctx);

	// create a new map from var names to array indices
	map<string, int>  locals;

	// add parameter first
	locals[currentFunction._paramName] = 0;

	int i = 1;

	// loop through the locals and make a new array from their names
	for (auto item : currentFunction.locals)
	{
		locals[item.first] = i;

		i++;
	}

	// push a zero to the garray for each locals
	for (auto item : locals)
	{
		g_array_append_val(localSymbols, zero);
	}

	currentSymbolsGArray = localSymbols;

	currentStatList = statLists.get(ctx); 

	currentFuncIndex++;
}



/*
Function: enterMain
Description:
*/
void VMInputPass::enterMain(InoxisParser::MainContext* ctx)
{
	cout << "\nmain\n"; 

	funcSymbol currentFunction = symbolTables.get(ctx);

	GArray* localSymbols = g_array_new(false, false, sizeof(unsigned));

	// create a new map from var names to array indices
	map<string, int>  locals;

	int i = 0;

	// loop through the locals and make a new array from their names
	for (auto item : currentFunction.locals)
	{
		locals[item.first] = i;

		i++;
	}

	// push a zero to the garray for each locals
	for (auto item : locals)
	{
		g_array_append_val(localSymbols, zero);
	}

	currentSymbolsGArray = localSymbols;
	
	currentStatList = statLists.get(ctx);
}








// function: incrementStatements
// every time this is called by exitStatement, we need to print that statement, then loop through any following
// sentinels, dropping all of those permissions
void  VMInputPass::incrementStatements()
{
	bool statementPrinted = false;

	// make sure we haven't reached the end of the list
	// this will happen if we've reached the end of the function and there are no sentinals left
	if (statementIndex < currentStatList.size())
	{

		// if the variant holds a statement, print it
		if (holds_alternative<InoxisParser::StatementContext*>(currentStatList[statementIndex]))
		{
			try
			{
				cout << get<InoxisParser::StatementContext*>(currentStatList[statementIndex])->getText() << endl;
			}

			catch (std::bad_variant_access const& ex)
			{
				cout << "Exception: " << ex.what() << endl;
			}

			// go to next variant to check if it's a sentinal
			statementIndex++;

			statementPrinted = true;
		}

		else if (holds_alternative<InoxisParser::ReturnContext*>(currentStatList[statementIndex]))
		{
			try
			{
				cout << get<InoxisParser::ReturnContext*>(currentStatList[statementIndex])->getText() << endl;
			}

			catch (std::bad_variant_access const& ex)
			{
				cout << "Exception: " << ex.what() << endl;
			}

			// go to next variant to check if it's a sentinal
			statementIndex++;

			statementPrinted = true;
		}

		// while the current variant is a sentinel...
		while (true)
		{
			if (statementIndex >= currentStatList.size())
				break;

			if (!holds_alternative<sentinal>(currentStatList[statementIndex]))
				break;

			try
			{
				// get the name of the dropped var and then drop its permissions
				sentinal currentSentinal = get<sentinal>(currentStatList[statementIndex]);

				// if the variable is a pointer to heap memory, free the memory

				cout << currentSentinal.varName << " freed\n";
			}

			catch (std::bad_variant_access const& ex)
			{
				cout << "Exception: " << ex.what() << endl;
			}

			// go to next statement
			statementIndex++;
		}

		if (statementIndex < currentStatList.size() && !statementPrinted)
		{
			if (holds_alternative<InoxisParser::StatementContext*>(currentStatList[statementIndex]))
			{
				try
				{
					cout << get<InoxisParser::StatementContext*>(currentStatList[statementIndex])->getText() << endl;
				}

				catch (std::bad_variant_access const& ex)
				{
					cout << "Exception: " << ex.what() << endl;
				}

				// go to next variant to check if it's a sentinal
				statementIndex++;

				statementPrinted = true;
			}

			else if (holds_alternative<InoxisParser::ReturnContext*>(currentStatList[statementIndex]))
			{
				try
				{
					cout << get<InoxisParser::ReturnContext*>(currentStatList[statementIndex])->getText() << endl;
				}

				catch (std::bad_variant_access const& ex)
				{
					cout << "Exception: " << ex.what() << endl;
				}

				// go to next variant to check if it's a sentinal
				statementIndex++;

				statementPrinted = true;
			}
		}
	}
}









