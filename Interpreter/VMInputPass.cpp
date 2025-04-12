#include "VMInputPass.h"






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









void  VMInputPass::test()
{
	// create statements array
	GArray* statements = g_array_new(false, false, sizeof(statement));

	// create symbols array
	GArray* symbols = g_array_new(false, false, sizeof(int));

	// create functions array
	GArray* functions = g_array_new(false, false, sizeof(function));

	int zero = 0;

	// make expression 6 + 7
	literal a;

	a.number = 6;

	expression* aExp = makeLiteralExpression(a);

	literal b;

	b.number = 7;

	expression* bExp = makeLiteralExpression(b);

	BinOp* result = makeBinOp(ADD, aExp, bExp);

	expression* res = makeBinOpExpression(result);


	// now create a variable to assign res to
	// var = 6 + 7
	literal var;

	var.varIndex = 0;

	// create a new entry in the symbol table (0 by default)
	g_array_append_val(symbols, zero);

	// use that to create a literal expression
	expression* lhs = makeLiteralExpression(var);

	// create new variable declaration statement with the expressions
	varDec  newVarDec{ false, 0, *lhs, *res };

	// create a new statement using that
	statement newStatement = initVarDecStatement(newVarDec);

	g_array_append_val(statements, newStatement);

	// create new function
	function* newFunc = makeFunction(statements, symbols);

	g_array_append_val(functions, newFunc);


	if (res->kind == EXPR_BIN)
		cout << res->val.binaryOp.lhs->val.litVal.number << " + " << res->val.binaryOp.rhs->val.litVal.number << endl;

	// this free aExp and bExp as well
	freeBinOp(result);

	free(res);

	free(lhs);

	freeFunction(newFunc);

	g_array_free(functions, true);

}