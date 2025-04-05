#include "MemSafetyPass.h"

using namespace DataType;



/*
Function: enterAssign
Description: First, check that immutable vars are not being assigned new values
second, drop pointer vars that are assigned to other pointer vars
*/
void   MemSafetyPass::enterAssign(InoxisParser::AssignContext* ctx)
{
	// mutability check
	// get name of variable being assigned
	string  varName = ctx->var()->ID()->getText();

	// get variable
	varSymbol var = currentFunction.locals[varName];

	// check if the variable's mutable
	bool lhsMut = var._isMutable;

	// if it's not, then you can't assign a new value to it
	if (!lhsMut)
	{
		reportMemError();

		cout << varName << " is IMMUTABLE. You cannot change it's value.\n";
	}


	// drop assigned pointers
	DATA_TYPE  lhsType = currentFunction.locals[varName].dataType;

	string rhsText = ctx->assignRHS()->getText();

	vector<string> rhsVars = getVars(rhsText);

	int numRHSVars = rhsVars.size();

	if (lhsType == POINTER)
	{
		if (lhsMut)
		{
			currentFunction.locals[varName].setPermissions(read | write | own, false);

			cout << "assign: " << varName << ". Permissions: " << currentFunction.locals[varName].memPermissions << endl;
		}

		else
		{
			currentFunction.locals[varName].setPermissions(read | own, false);

			cout << "assign: " << varName << ". Permissions: " << currentFunction.locals[varName].memPermissions << endl;
		}

		// if the lhs is initialized with another pointer, the rhs pointer is dropped
		if (numRHSVars == 1)
		{
			string rhsVar = rhsVars[0];

			DATA_TYPE rhsDataType = currentFunction.locals[rhsVar].dataType;

			if (rhsDataType == POINTER)
			{
				dropVar(rhsVar);
			}
		}
	}

}








/*
function: enterVarDec
Description: init memory permissions for the declared variable
if that var is a borrow, then init it and its paths permissions and changer permissions
for the borrowee, maybe create another function that does the borrowing, since assignment can do the same thing
*/
void MemSafetyPass::enterVarDec(InoxisParser::VarDecContext* ctx)
{
	string funcName = currentFunction.getName();

	string varName = ctx->ID()->getText();

	DATA_TYPE  lhsType = currentFunction.locals[varName].dataType;

	bool  lhsMut = currentFunction.locals[varName]._isMutable;



	// if we initialize the variable
	if (ctx->varDecRHS() != NULL)
	{
		if (ctx->varDecRHS()->assignRHS() != NULL)
		{
			string rhsText = ctx->varDecRHS()->assignRHS()->getText();

			vector<string> rhsVars = getVars(rhsText);

			int numRHSVars = rhsVars.size();

			// integer init 
			// int x = 7;
			// int y = x;
			if (lhsType == INT)
			{
				// check that the rhs is an expression
				// we would do this recursively, expressions are made up of smaller expressions

				if (lhsMut)
				{
					currentFunction.locals[varName].setPermissions(read | write | own, false);

					cout << "init: " << varName << ". Permissions: " << currentFunction.locals[varName].memPermissions << endl;
				}

				else
				{
					currentFunction.locals[varName].setPermissions(read | own, false);

					cout << "init: " << varName << ". Permissions: " << currentFunction.locals[varName].memPermissions << endl;
				}
			}

			// pointer init with variable
			// int *y = &x;
			// int *z = new int;  *z = 7; int *y = z;
			// pointer init with allocation
			// int *x = new int;
			else if (lhsType == POINTER)
			{

				if (lhsMut)
				{
					currentFunction.locals[varName].setPermissions(read | write | own, false);

					cout << "init: " << varName << ". Permissions: " << currentFunction.locals[varName].memPermissions << endl;
				}

				else
				{
					currentFunction.locals[varName].setPermissions(read | own, false);

					cout << "init: " << varName << ". Permissions: " << currentFunction.locals[varName].memPermissions << endl;
				}

				// if the lhs is initialized with another pointer, the rhs pointer is dropped
				if (numRHSVars == 1)
				{
					string rhsVar = rhsVars[0];

					DATA_TYPE rhsDataType = currentFunction.locals[rhsVar].dataType;

					if (rhsDataType == POINTER)
					{
						dropVar(rhsVar);
					}
				}
			}

			// lhs has type reference
			else
			{
				// make sure there's just a variable on the RHS
				if (numRHSVars == 1)
				{
					bool mutRef = false;

					bool rhsRefSymbol = false;

					string rhsVar = rhsVars[0];

					// check if the rhs is mut
					if (ctx->varDecRHS()->assignRHS()->expression()->factor()->var()->mut() != NULL)
						mutRef = true;

					if (ctx->varDecRHS()->assignRHS()->expression()->factor()->var()->pointRef() != NULL)
						if (ctx->varDecRHS()->assignRHS()->expression()->factor()->var()->pointRef()->getText() == "&")
							rhsRefSymbol = true;

					if (lhsMut)
					{
						// report error, not allowed in C++
					}

					// can't change address
					else
					{
						// mutable reference, syntax is "int &var1 = &mut var2;
						if (mutRef)
						{
							// check that the rhs has &
							if (!rhsRefSymbol)
							{
								reportMemError();
								cout << "invalid mutable reference syntax: usage - int &var1 = mut& var2;\n";
							}

							// drop all permissions for borrowee
							currentFunction.locals[rhsVar].setPermissions(none, false);

							// lhs is a borrow now
							currentFunction.locals[varName].isBorrow = true;

							// set lhs's borrowee
							currentFunction.locals[varName].borrowee = rhsVar;

							// borrower reference gains r/o
							currentFunction.locals[varName].setPermissions(read | own, false);

							// borrower data gains r/w/o
							currentFunction.locals[varName].setPermissions(read | write | own, true);

							cout << "init: " << varName << ". Permissions: " << currentFunction.locals[varName].memPermissions
								<< ". Place permissions: " << currentFunction.locals[varName].placeMemPermissions << endl;
						}

						else
						{

						}
					}
				}

				else
				{
					cout << "error line: " << "can only have one variable on rhs\n";

					reportMemError();

					return;
				}
			}


		}
	}
}





/*
function: enterFuncCall
Description: if a pointer is passed as a function argument, then it is dropped
*/
void MemSafetyPass::enterFuncCall(InoxisParser::FuncCallContext* ctx)
{
	// get the function signature of the called function
	string calledFuncName = ctx->ID()->getText();

	funcSymbol calledFunc = functions.get(ctx);

	string  argName = ctx->arg()->var()->ID()->getText();

	// if the paramemter is a pointer
	if (calledFunc._paramType == POINTER)
	{
		//make sure that the dereference operator * is not in the function call
		if (ctx->getText().find("*") != string::npos)
		{
			reportMemError();

			cout << "data type of parameter and argument do not match in func call\n";
		}

		// no * in call, drop all of the argument's permissions
		else
		{
			if (currentFunction.locals[argName].dataType != POINTER)
			{
				reportMemError();

				cout << "data type of parameter and argument do not match in func call\n";
			}

			else
			{
				dropVar(argName);
			}
		}
	}
}



/*
function: enterMain
Description: same as for enterFuncDef
*/
void MemSafetyPass::enterMain(InoxisParser::MainContext* ctx)
{
	currentFunction = functions.get(ctx);

	inFuncDef = true;

	cout << "MAIN\n";

	// sentinel drops permissions for borower and regains for borowee

	// create new vector of variants (either parse tree node, or sentinal) called anotatedStatements
	vector<variant<InoxisParser::StatementContext*, sentinal, InoxisParser::ReturnContext*>>  anotatedStatements;


	// make sure the function contains statements
	if (ctx->statList() != NULL)
	{
		// get the statements vector
		auto statements = ctx->statList()->statement();

		// for statement in statements
		for (int i = 0; i < statements.size(); i++)
		{
			auto statement = statements[i];

			//cout << statement->getText() << endl;

			vector<string> vars = getVars(statement->getText());

			//copy statement into anotatedStatements
			anotatedStatements.push_back(statement);

			// loop through all vars in statement
			for (int j = 0; j < vars.size(); j++)
			{
				string varName = vars[j];

				// check if there's a sentinal value for the variable
				if (!checkIfSentinal(anotatedStatements, i, varName))
				{
					// if there isn't, check if this is the last time the var is used
					// call isFinalUse()
					if (i + 1 >= statements.size())
					{
						// add sentinal for var to anotatedStatements
						sentinal newSentinal{ varName, false };

						anotatedStatements.push_back(newSentinal);
					}

					else
					{
						if (isFinalUse(statements, NULL, i + 1, varName))
						{
							// add sentinal for var to anotatedStatements
							sentinal newSentinal{ varName, false };

							anotatedStatements.push_back(newSentinal);
						}
					}
				}
			}

			// need to check code to add sentinal for the parameter
		}


		/*for (int k = 0; k < anotatedStatements.size(); k++)
		{
			if (holds_alternative<sentinal>(anotatedStatements[k]))
			{
				auto mySentinal = get<sentinal>(anotatedStatements[k]);

				cout << "Sentinel: " << mySentinal.varName << endl;
			}

			else
			{
				auto statement = get<InoxisParser::StatementContext*>(anotatedStatements[k]);

				cout << statement->getText() << endl;
			}
		}*/

		// now we save the anotated statements so that we can keep track of when 
		// variables are dropped while we walk the rest of the parse tree for this function
		currentStatList = anotatedStatements;

		// for statement in anotatedStatements
			// do memory safety checking
	}

	cout << endl;
}



/*
function: enterFuncDef
Description: loop through all statements in the function, adding them to annotatedStatements.
for each local variable, after the last time it's used, add a sentinal for it to annotatedStatements
*/
void MemSafetyPass::enterFuncDef(InoxisParser::FuncDefContext* ctx) 
{
	inFuncDef = true;

	currentFunction = functions.get(ctx);

	cout << endl << currentFunction.getName() << endl;

	// sentinel drops permissions for borower and regains for borowee

	// create new vector of variants (either parse tree node, or sentinal) called anotatedStatements
	vector<variant<InoxisParser::StatementContext*, sentinal, InoxisParser::ReturnContext*>>  anotatedStatements;

	int i = 0;

	// make sure the function contains statements
	if (ctx->statList() != NULL)
	{
		// get the statements vector
		auto statements = ctx->statList()->statement();

		// first need to add the sentinal for the parameter if it's not used
		string paramName = ctx->param()->ID()->getText();

		// check if there's a sentinal value for the variable
		if (!checkIfSentinal(anotatedStatements, 0, paramName))
		{
			if (isFinalUse(statements, ctx->return_(), 0, paramName))
			{
				// add sentinal for var to anotatedStatements
				sentinal newSentinal{ paramName, false };

				anotatedStatements.push_back(newSentinal);
			}
		}

		// for statement in statements
		for (int i = 0; i < statements.size(); i++)
		{
			auto statement = statements[i];

			//cout << statement->getText() << endl;

			vector<string> vars = getVars(statement->getText());

			//copy statement into anotatedStatements
			anotatedStatements.push_back(statement);

			// loop through all vars in statement
			for (int j = 0; j < vars.size(); j++)
			{
				string varName = vars[j];

				// check if there's a sentinal value for the variable
				if (!checkIfSentinal(anotatedStatements, i, varName))
				{
					// if there isn't, check if this is the last time the var is used
					// call isFinalUse()
					if (i + 1 >= statements.size())
					{
						// add sentinal for var to anotatedStatements
						sentinal newSentinal{ varName, false };

						anotatedStatements.push_back(newSentinal);
					}

					else
					{
						if (isFinalUse(statements, ctx->return_(), i + 1, varName))
						{
							// add sentinal for var to anotatedStatements
							sentinal newSentinal{ varName, false };

							anotatedStatements.push_back(newSentinal);
						}
					}
				}
			}
		}

		auto returnStatement = ctx->return_();

		vector<string> vars = getVars(returnStatement->getText());

		//copy statement into anotatedStatements
		anotatedStatements.push_back(returnStatement);

		// loop through all vars in return statement and add a sentinal for each
		for (int j = 0; j < vars.size(); j++)
		{
			string varName = vars[j];

			sentinal newSentinal{ varName, false };

			anotatedStatements.push_back(newSentinal);
		}


		/*for (int k = 0; k < anotatedStatements.size(); k++)
		{
			if (holds_alternative<sentinal>(anotatedStatements[k]))
			{
				auto mySentinal = get<sentinal>(anotatedStatements[k]);

				cout << "Sentinel: " << mySentinal.varName << endl;
			}

			else
			{
				auto statement = get<InoxisParser::StatementContext*>(anotatedStatements[k]);

				cout << statement->getText() << endl;
			}
		}*/

		// now we save the anotated statements so that we can keep track of when 
		// variables are dropped while we walk the rest of the parse tree for this function
		currentStatList = anotatedStatements;

		// for statement in anotatedStatements
			// do memory safety checking
	}

	cout << endl;
}





// getVars()
// could use string search, search the string for all the var names in function.locals
// false positives??
vector<string>  MemSafetyPass::getVars(string statement)
{
	vector<string>  vars;

	// loop through all local vars
	for (auto x : currentFunction.locals)
	{
		string varName = x.first;

		if (statement.find(varName) != std::string::npos)
		{
			vars.push_back(varName);
		}
	}

	return vars;
}




// loop through rest of the anotated statements starting from 'start' index
// check if there's a sentinal value for var
bool MemSafetyPass::checkIfSentinal(vector<variant<InoxisParser::StatementContext*, sentinal, InoxisParser::ReturnContext*>>
	statements, int start, string var)
{
	for (int i = start; i < statements.size(); i++)
	{
		if (holds_alternative<sentinal>(statements[i]))
		{
			try
			{
				auto mySentinal = get<sentinal>(statements[i]);

				if (mySentinal.varName == var)
					return true;
			}

			catch (std::bad_variant_access const& ex)
			{


				cout << "bad variant access\n";
			}
		}
	}

	return false;
}




// given a variable name, and the index of current statement + 1, check if the variable is used in the 
// remaining statements
bool   MemSafetyPass::isFinalUse(vector<InoxisParser::StatementContext*>  statements, InoxisParser::ReturnContext* returnStatement, 
	int start, string var)
{
	// loop through statements
	for (int i = start; i < statements.size(); i++)
	{
		// get current statement
		auto statement = statements[i];

		//cout << statement->getText() << endl;

		// get all the variable names in statement
		vector<string> vars = getVars(statement->getText());

		if (!vars.empty())
		{
			// loop through variable names
			for (int j = 0; j < vars.size(); j++)
			{

				// if it matches the variable name we're checking, return false
				if (vars[j] == var)
					return false;
			}
		}
	}

	// check return statement as well
	if (returnStatement != NULL)
	{
		vector<string> vars = getVars(returnStatement->getText());

		if (!vars.empty())
		{
			// loop through variable names
			for (int j = 0; j < vars.size(); j++)
			{
				// if it matches the variable name we're checking, return false
				if (vars[j] == var)
					return false;
			}
		}
	}

	// if we reach the end, return true
	return true;
}













// every time this is called by exitStatement, we need to print that statement, then loop through any following
// sentinels, dropping all of those permissions
void  MemSafetyPass::incrementStatements()
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
				cout << "bad variant access\n";
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
				cout << "bad variant access\n";
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

			if(!holds_alternative<sentinal>(currentStatList[statementIndex]))
				break;

			try
			{
				// get the name of the dropped var and then drop its permissions
				sentinal currentSentinal = get<sentinal>(currentStatList[statementIndex]);

				dropVar(currentSentinal.varName);

				cout << currentSentinal.varName << " dropped \n";
			}

			catch (std::bad_variant_access const& ex)
			{
				cout << "bad variant access\n";
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
					cout << "bad variant access\n";
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
					cout << "bad variant access\n";
				}

				// go to next variant to check if it's a sentinal
				statementIndex++;

				statementPrinted = true;
			}
		}
	}
}



/*
Function: dropVar
Returns: None
Param: varName - the name of the variable to be dropped
Description: Called when a sentinel for the variable with name varName is hit when looping through statements
all varName's permissions are dropped as well as it's place (if applicable)
if varName is a borrow, then regainPermissions is called, passing the varName's borowee
*/
void  MemSafetyPass::dropVar(string varName)
{
	// check that the var is in the current functions locals
	if (currentFunction.locals.count(varName) == 1)
	{
		// drop the variables permissions
		currentFunction.locals[varName].dropPermissions();

		currentFunction.locals[varName].hasBeenDropped = true;

		//cout << "after dropping, " << varName << "s permissions are now: " << 
			//currentFunction.locals[varName].memPermissions << endl;

		//currentFunction.locals[varName].isBorrow = true;

		//currentFunction.locals[varName].borrowee = "var";

		// if the dropped var is a borrow
		// what if both are dropped on the same line??
		if (currentFunction.locals[varName].isBorrow)
		{
			string borroweeName = currentFunction.locals[varName].borrowee;

			// its borrowee now regains its permissions
			if (currentFunction.locals.count(borroweeName) == 1 && !currentFunction.locals[borroweeName].hasBeenDropped)
			{
				currentFunction.locals[borroweeName].regainPermissions();
			}
		}
	}
}