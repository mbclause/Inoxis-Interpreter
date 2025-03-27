#include "MemSafetyPass.h"




void   MemSafetyPass::enterAssign(InoxisParser::AssignContext* ctx)
{
	// get name of variable being assigned
	string  varName = ctx->var()->ID()->getText();

	// symbol has been validated in previous pass, get it from function locals

	/*cout << currentFunction.getName() << endl;

	for (auto x : currentFunction.locals)
	{
		varSymbol var = x.second;

		var.printVarSymbol();
	}*/

	// get variable
	varSymbol var = currentFunction.locals[varName];

	//var.printVarSymbol();

	// check if the variable's mutable
	bool isMut = var._isMutable;

	// if it's not, then you can't assign a new value to it
	if (!isMut)
	{
		reportMemError();

		cout << varName << " is IMMUTABLE. You cannot change it's value.\n";
	}
}