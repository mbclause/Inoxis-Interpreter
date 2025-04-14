#include "VMInput.h"
#include <iostream>

using namespace std;

void test();


void  test()
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