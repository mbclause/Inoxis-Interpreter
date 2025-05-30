/*
File: MemSafetyPass.cpp
Description: The member function definitions for MemSafetyPass. 
Like the other AST walkers, these are mostly overridden enter and exit rule functions.
*/

#include "MemSafetyPass.h"

using namespace DataType;


/*
Function: exitVar
Description: make sure that this variable expression evaluates to an integer and pass that result up the tree
*/
void  MemSafetyPass::exitVar(InoxisParser::VarContext* ctx)
{
	// get the var name
	string  varName = ctx->ID()->getText();

	// get the lhs data type
	DATA_TYPE varDataType = currentFunction.locals[varName].dataType;

	bool isArray = currentFunction.locals[varName]._isArray;

	// check if an operator is used on the lhs
	bool containsDereference = false;

	bool containsAddressOp = false;

	bool containsSubscript = false;

	bool  expIsInt = false;

	if (ctx->array()->getText().length() > 0)
		containsSubscript = true;

	if (ctx->pointRef()->getText() == "*")
		containsDereference = true;

	if (ctx->pointRef()->getText() == "&")
		containsAddressOp = true;

	// can't use subscript operator on non array
	if (isArray && containsSubscript && varDataType != REF)
	{
		reportMemError(ctx);

		cout << " can't use subscript operator on non array\n";
	}

	if (containsDereference && varDataType == INT)
	{
		reportMemError(ctx);

		cout << " can only dereference a pointer\n";
	}

	// if * or [] is in expression, then it evaluates to an int
	if (containsSubscript || containsDereference)
	{
		expIsInt = true;
	}

	// else, only INT data types evaluate to ints
	else
	{
		if (varDataType == INT)
			expIsInt = true;
	}

	// put the result in the parse tree
	expIsIntProp.put(ctx, expIsInt);


} // end exitVar



/*
Function: checkDeclarationTypeSafety
Description: make sure that the data types on both sides of the assignment statement match. If not, report an error.
*/
void  MemSafetyPass::checkDeclarationTypeSafety(InoxisParser::VarDecContext* ctx)
{
	// get the lhs var name
	string  lhsVarName = ctx->ID()->getText();

	// get the lhs data type
	DATA_TYPE lhsDataType = currentFunction.locals[lhsVarName].dataType;

	bool lhsIsArray = currentFunction.locals[lhsVarName]._isArray;

	bool rhsAllocation = false;

	bool rhsMutRef = false;

	bool rhsIsInt = expIsIntProp.get(ctx->varDecRHS());

	// check if the rhs is a mutable reference
	if (ctx->varDecRHS()->assignRHS()->rhsRef() != NULL)
		rhsMutRef = true;

	// check if there's an allocation
	if (ctx->varDecRHS()->assignRHS()->allocate() != NULL)
		rhsAllocation = true;

	// cannot assign a value to a stack array during declaration
	if (ctx->array()->getText().size() > 0)
	{
		reportMemError(ctx);

		cout << "cannot assign a value to a stack array during declaration\n";
	}

	else
	{
		// if the lhs vars data type is an int
		if (lhsDataType == INT)
		{
			if (rhsAllocation)
			{
				reportMemError(ctx);

				cout << " cannot allocate to a non-pointer\n";
			}

			// check that the rhs is an int by getting the parse tree property
			if (!rhsIsInt)
			{
				reportMemError(ctx);

				cout << " can only assign an integer to an int\n";
			}
		}

		// if it's a pointer, only another pointer can be assigned to it, or there could be an allocation
		else if (lhsDataType == POINTER)
		{
			if (!rhsAllocation)
			{
				// get the number of variables on the rhs
				string  rhsText = ctx->varDecRHS()->assignRHS()->getText();

				vector<string>  rhsVars = getVars(rhsText);

				int  numRHSVars = rhsVars.size();

				if (numRHSVars != 1)
				{
					reportMemError(ctx);

					cout << " can only assign another pointer to a pointer\n";
				}

				else
				{
					// check that the rhs var is another pointer
					string  rhsVarName = rhsVars[0];

					if (currentFunction.locals[rhsVarName].dataType != POINTER)
					{
						reportMemError(ctx);

						cout << " can only assign another pointer to a pointer\n";
					}
				}
			}
		}

		// vardec for reference is already check in enterVarDec()
		else if (lhsDataType == REF)
		{
			if (rhsAllocation)
			{
				reportMemError(ctx);

				cout << " cannot allocate to a non-pointer\n";
			}

		}
	}
} // end checkDeclarationTypeSafety





/*
Function: checkAssignTypeSafety
Description: make sure that the data types on both sides of the assignment statement match. If not, report an error.
*/
void  MemSafetyPass::checkAssignTypeSafety(InoxisParser::AssignContext* ctx)
{
	// get the lhs var name
	string  lhsVarName = ctx->var()->ID()->getText();

	// get the lhs data type
	DATA_TYPE lhsDataType = currentFunction.locals[lhsVarName].dataType;

	bool lhsIsArray = currentFunction.locals[lhsVarName]._isArray;

	// check if an operator is used on the lhs
	bool containsDereference = false;

	bool containsAddressOp = false;

	bool containsSubscript = false;

	bool rhsAllocation = false;

	bool rhsIsInt = expIsIntProp.get(ctx->assignRHS());

	if (ctx->var()->array()->getText().length() > 0)
		containsSubscript = true;

	if (ctx->var()->pointRef()->getText() == "*")
		containsDereference = true;

	if (ctx->var()->pointRef()->getText() == "&")
		containsAddressOp = true;

	if (ctx->assignRHS()->allocate() != NULL)
		rhsAllocation = true;

	// you can't have an address operator on the lhs of an assignment
	if (containsAddressOp)
	{
		reportMemError(ctx);

		cout << " cannot have '&' on the lhs of an assignment\n";
	}

	// can't have an allocation to a non-pointer/reference


	// the lhs can be an int if the dereference or subscript operator is used with it
	if (containsSubscript || containsDereference)
	{
		if (rhsAllocation)
		{
			reportMemError(ctx);

			cout << " cannot allocate to a non-pointer\n";
		}

		// check that the rhs is an int by getting the parse tree property
		if (!rhsIsInt)
		{
			reportMemError(ctx);

			cout << " can only assign an integer to an int\n";
		}
	}
	
	else
	{

		// if the lhs vars data type is an int
		if (lhsDataType == INT)
		{
			if (rhsAllocation)
			{
				reportMemError(ctx);

				cout << " cannot allocate to a non-pointer\n";
			}

			// check that the rhs is an int by getting the parse tree property
			if (!rhsIsInt)
			{
				reportMemError(ctx);

				cout << " can only assign an integer to an int\n";
			}
		}

		// if it's a pointer, only another pointer can be assigned to it, or there could be an allocation
		else if (lhsDataType == POINTER)
		{
			if (!rhsAllocation)
			{
				// get the number of variables on the rhs
				string  rhsText = ctx->assignRHS()->getText();

				vector<string>  rhsVars = getVars(rhsText);

				int  numRHSVars = rhsVars.size();

				if (numRHSVars != 1)
				{
					reportMemError(ctx);

					cout << " can only assign another pointer to a pointer\n";
				}

				else
				{
					// check that the rhs var is another pointer
					string  rhsVarName = rhsVars[0];

					if (currentFunction.locals[rhsVarName].dataType != POINTER)
					{
						reportMemError(ctx);

						cout << " can only assign another pointer to a pointer\n";
					}
				}
			}
		}

		// if it's a reference, make sure it's used with * or [], since another address can't be assigned to it
		else if (lhsDataType == REF)
		{
			if (rhsAllocation)
			{
				reportMemError(ctx);

				cout << " cannot allocate to a non-pointer\n";
			}

				reportMemError(ctx);

				cout << " cannot re-assign another address to a reference\n";

		}
	}
} // end checkAssignTypeSafety




/*
Function: addConditionalStatements
Description: given a conditional statement, get all of the statements inside the block and add them to stringStatements
*/
void  MemSafetyPass::addConditionalStatements(InoxisParser::StatementContext* condStatement, 
	vector<string>& stringStatements)
{
	// if the statement is an if/else block
	if (condStatement->ifElseBlock() != NULL)
	{
		auto ifElse = condStatement->ifElseBlock();

		// add the if condition to stringStatements
		stringStatements.push_back(ifElse->condition()->getText());

		// if there are any statements in the if block...
		if (ifElse->statList() != NULL)
		{
			auto statements = ifElse->statList()->statement();

			// get all the statements in the block
			vector<string> ifStatements = convertStatementsToString(statements, NULL);

			// concatenate to our vector
			// from stackOverflow
			stringStatements.insert(stringStatements.end(), ifStatements.begin(), ifStatements.end());
		}

		// if there's an elif in the block...
		if (ifElse->elif() != NULL)
		{
			auto elif = ifElse->elif();

			auto conditionsVector = elif->condition();

			auto statListsVector = elif->statList();

			// loop through each elif
			for (int i = 0; i < conditionsVector.size(); i++)
			{
				// add the condition to stringStatements
				stringStatements.push_back(conditionsVector[i]->getText());

				// check if the current elif block has any statements...
				if (statListsVector[i] != NULL)
				{
					auto statements = statListsVector[i]->statement();

					// get all the statements in the block
					vector<string> elifStatements = convertStatementsToString(statements, NULL);

					// concatenate to our vector
					// from stackOverflow
					stringStatements.insert(stringStatements.end(), elifStatements.begin(), elifStatements.end());
				}
			}
		}

		if (ifElse->else_() != NULL)
		{
			auto elseStatement = ifElse->else_();

			// if there are any statements in the else block...
			if (elseStatement->statList() != NULL)
			{
				auto statements = elseStatement->statList()->statement();

				// get all the statements in the block
				vector<string> elseStatements = convertStatementsToString(statements, NULL);

				// concatenate to our vector
				// from stackOverflow
				stringStatements.insert(stringStatements.end(), elseStatements.begin(), elseStatements.end());
			}
		}
	}

	// otherwise it's a while loop
	else
	{
		auto whileStatement = condStatement->while_();

		string  whileSentinal = "ENTER_WHILE";

		string  endWhileSentinal = "EXIT_WHILE";

		stringStatements.push_back(whileSentinal);

		// add the if condition to stringStatements
		stringStatements.push_back(whileStatement->condition()->getText());

		// if there are any statements in the if block...
		if (whileStatement->statList() != NULL)
		{
			auto statements = whileStatement->statList()->statement();

			// get all the statements in the block
			vector<string> whileStatements = convertStatementsToString(statements, NULL);

			// concatenate to our vector
			// from stackOverflow
			stringStatements.insert(stringStatements.end(), whileStatements.begin(), whileStatements.end());
		}

		stringStatements.push_back(endWhileSentinal);
	}
} // end addConditionalStatements



/*
Function: convertStatementsToString
Description: given a vector of inoxis statements, convert each to a string.
*/
vector<string>  MemSafetyPass::convertStatementsToString(vector<InoxisParser::StatementContext*>  statements, 
	InoxisParser::ReturnContext* returnStatement)
{
	vector<string>  stringStatements;

	// loop through statements
	for (int i = 0; i < statements.size(); i++)
	{
		auto statement = statements[i];

		vector<string> printVars;

		// if it's a print statement, call getPrintVars, just make a comma separated
		// string out of the returned variables
		if (statement->print() != NULL)
		{
			printVars = getPrintVars(statement->print());

			string printVarsString;

			for (int j = 0; j < printVars.size(); j++)
			{
				printVarsString += printVars[j];

				printVarsString += ", ";
			}

			stringStatements.push_back(printVarsString);
		}

		// if the statement is an if/else block or while loop, call addConditional statements to add all of the 
		// statements in that block to the vector
		else if (statement->ifElseBlock() != NULL)
		{
			//cout << statement->getText() << " is an if/else statement\n";

			addConditionalStatements(statement, stringStatements);
		}

		else if (statement->while_() != NULL)
		{
			//cout << statement->getText() << " is an while statement\n";

			addConditionalStatements(statement, stringStatements);
		}

		// otherwise just add the statement string
		else
		{
			stringStatements.push_back(statement->getText());
		}
	}

	// add the return statement last if there is one
	if(returnStatement != NULL)
		stringStatements.push_back(returnStatement->getText());

	return stringStatements;
} // end convertStatementsToString



/*
Function: getPrintVars
Description: return all of the variables in the print statement as a string vector
*/
vector<string>  MemSafetyPass::getPrintVars(InoxisParser::PrintContext* ctx)
{
	vector<string> vars;

	if (ctx->printLiteral()->var() != NULL)
	{
		// check it's read permissions
		string var = ctx->printLiteral()->var()->ID()->getText();

		vars.push_back(var);
	}

	// if there's more to the print statement
	if(ctx->out() != NULL)
		if (ctx->out()->printLiteral().size() > 0)
		{
			for (int i = 0; i < ctx->out()->printLiteral().size(); i++)
			{
				if(ctx->out()->printLiteral()[i]->var())
					vars.push_back(ctx->out()->printLiteral()[i]->var()->ID()->getText());
			}
		}


	return vars;
} // end getPrintVars



/*
Function: enterOut
Description: this rule is entered if there is more than one use of the extraction operator in a print statement
check all of the variable's read permissions in the rest of the print statement
*/
void MemSafetyPass::enterOut(InoxisParser::OutContext* ctx)
{
	vector<string>  varNames;

	// if there are any vars in the output
	if (ctx->printLiteral().size() > 0)
	{
		// loop through them and add their names to the string vector
		for (int i = 0; i < ctx->printLiteral().size(); i++)
		{
			if(ctx->printLiteral()[i]->var())
				varNames.push_back(ctx->printLiteral()[i]->var()->ID()->getText());
		}

		// check the vars read permissions
		if (!checkReadPermissions(varNames, ctx))
		{
			//reportMemError(ctx);
		}
	}
} // end enterOut



/*
Function: enterPrint
Description: if the first output in the statement is a variable: check it's read permissions
*/
void MemSafetyPass::enterPrint(InoxisParser::PrintContext* ctx)
{
	// if the first output is a variable...
	if (ctx->printLiteral()->var() != NULL)
	{
		// check it's read permissions
		string var = ctx->printLiteral()->var()->ID()->getText();

		vector<string> varVec{ var };

		if (!checkReadPermissions(varVec, ctx))
		{
			//reportMemError(ctx);
		}
	}
} // end enterPrint



/*
Function: checkReadPermissions
Description: checks all the variable names passed to it for read permissions
Returns true if all vars have them and false otherwise
*/
bool  MemSafetyPass::checkReadPermissions(vector<string> vars, antlr4::ParserRuleContext* ctx)
{
	// loop through all variables
	for (int i = 0; i < vars.size(); i++)
	{
		// get current variable
		varSymbol  var = currentFunction.locals[vars[i]];

		// check the permissions for the place as well if var is borrow
		if (var.isBorrow)
		{
			if (!var.hasReadPermissions(true))
			{
				reportMemError(ctx);

				cout << "*" << var._name << " does not have required Read permissions\n";

				return false;
			}
		}

		if (!var.hasReadPermissions(false))
		{
			reportMemError(ctx);

			cout << var._name << " does not have required Read permissions\n";

			return false;
		}
	}

	return true;
} // end checkReadPermissions



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

	// check that the lhs var has proper write permissions
	// first check the place permissions if the var is a borrow
	if (var.isBorrow)
	{
		if (ctx->var()->pointRef() != NULL)
		{
			if (ctx->var()->pointRef()->getText() == "*")
			{
				if (!var.hasWritePermissions(true))
				{
					reportMemError(ctx);

					cout << var._name << "s place does not have write permissions\n";
				}
			}
		}

		else
		{
			if (!var.hasWritePermissions(false))
			{
				reportMemError(ctx);

				cout << var._name << "s place does not have write permissions\n";
			}
		}
	}

	// for non-borrows just check regular permissions
	else
	{
		if (!var.hasWritePermissions(false))
		{
			reportMemError(ctx);

			cout << var._name << " does not have write permissions\n";
		}
	}

			


	// drop assigned pointers
	DATA_TYPE  lhsType = currentFunction.locals[varName].dataType;

	string rhsText = ctx->assignRHS()->getText();

	vector<string> rhsVars = getVars(rhsText);

	size_t numRHSVars = rhsVars.size();

	// first, check the read permissions for any variables on the right hand side
	if (!checkReadPermissions(rhsVars, ctx))
	{
		//reportMemError(ctx);
	}

	else
	{

		if (lhsType == POINTER)
		{
			if (lhsMut)
			{
				currentFunction.locals[varName].setPermissions(read | write | own, false);
			}

			else
			{
				currentFunction.locals[varName].setPermissions(read | own, false);
			}

			// if the lhs is initialized with another pointer, the rhs pointer is dropped
			if (numRHSVars == 1)
			{
				string rhsVar = rhsVars[0];

				DATA_TYPE rhsDataType = currentFunction.locals[rhsVar].dataType;

				if (currentFunction.locals[rhsVar].ownsHeapData)
				{
					currentFunction.locals[varName].ownsHeapData = true;

					currentFunction.locals[rhsVar].ownsHeapData = false;
				}

				if (rhsDataType == POINTER)
				{

					dropVar(rhsVar);
				}
			}

			// if there's an allocation...
			if (ctx->assignRHS()->allocate() != NULL)
			{
				currentFunction.locals[varName].ownsHeapData = true;
			}
		}
	}

} // end enterAssign








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

			size_t numRHSVars = rhsVars.size();


			// first, check the read permissions for any variables on the right hand side
			if (!checkReadPermissions(rhsVars, ctx))
			{
				//reportMemError();
			}

			else
			{

				// integer init 
				if (lhsType == INT)
				{
					// check that the rhs is an expression
					// we would do this recursively, expressions are made up of smaller expressions

					if (lhsMut)
					{
						currentFunction.locals[varName].setPermissions(read | write | own, false);
					}

					else
					{
						currentFunction.locals[varName].setPermissions(read | own, false);
					}
				}

				// pointer init with variable
				// example:
				// int *y = &x;
				// int *z = new int;  *z = 7; int *y = z;
				// pointer init with allocation
				// int *x = new int;
				else if (lhsType == POINTER)
				{

					if (lhsMut)
					{
						currentFunction.locals[varName].setPermissions(read | write | own, false);
					}

					else
					{
						currentFunction.locals[varName].setPermissions(read | own, false);
					}

					// if the lhs is initialized with another pointer, the rhs pointer is dropped
					if (numRHSVars == 1)
					{
						string rhsVar = rhsVars[0];

						DATA_TYPE rhsDataType = currentFunction.locals[rhsVar].dataType;

						if (currentFunction.locals[rhsVar].ownsHeapData)
						{
							currentFunction.locals[varName].ownsHeapData = true;
						}

						if (rhsDataType == POINTER)
						{

							dropVar(rhsVar);
						}
					}

					// if there's an allocation...
					if (ctx->varDecRHS()->assignRHS()->allocate() != NULL)
					{
						currentFunction.locals[varName].ownsHeapData = true;
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

						if (currentFunction.locals[rhsVar].ownsHeapData)
						{
							currentFunction.locals[varName].ownsHeapData = true;

							currentFunction.locals[rhsVar].ownsHeapData = false;
						}

						// check if the rhs is mut
						if (ctx->varDecRHS()->assignRHS()->rhsRef()->mut() != NULL)
						{
							if (ctx->varDecRHS()->assignRHS()->rhsRef()->mut()->getText() == "mut")
							{
								mutRef = true;
							}
						}

						if (ctx->varDecRHS()->getText().find("&") != string::npos)
						{
							rhsRefSymbol = true;
						}

						if (lhsMut)
						{
							// report error, not allowed in C++
							reportMemError(ctx);

							cout << "cannot change the address of a reference in Inoxis\n";
						}

						else
						{
							// mutable reference, syntax is "int &var1 = &mut var2;
							if (mutRef)
							{
								// check that the rhs has &
								if (!rhsRefSymbol)
								{
									reportMemError(ctx);
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
							}

							else
							{
								// drop write and own permissions for borrowee
								currentFunction.locals[rhsVar].setPermissions(read, false);

								// lhs is a borrow now
								currentFunction.locals[varName].isBorrow = true;

								// set lhs's borrowee
								currentFunction.locals[varName].borrowee = rhsVar;

								// borrower reference gains r/o
								currentFunction.locals[varName].setPermissions(read | own, false);

								// borrower data gains r
								currentFunction.locals[varName].setPermissions(read, true);
							}
						}
					}

					else
					{
						reportMemError(ctx);

						cout << "can only have one variable on rhs when initializing a reference\n";
					}
				}

			}


		}

		// otherwise set normal read/write permissions depending on mutability
		else
		{
			if (lhsMut)
			{
				currentFunction.locals[varName].setPermissions(read | write | own, false);
			}

			else
			{
				currentFunction.locals[varName].setPermissions(read | own, false);
			}
		}
	}
} // end enterVarDec





/*
function: enterFuncCall
Description: if a pointer is passed as a function argument, then it is dropped
*/
void MemSafetyPass::enterFuncCall(InoxisParser::FuncCallContext* ctx)
{
	// get the function signature of the called function
	string calledFuncName = ctx->ID()->getText();

	funcSymbol calledFunc = functions.get(ctx);

	if (ctx->arg()->var() != NULL)
	{
		string  argName = ctx->arg()->var()->ID()->getText();

		vector<string>  argVec{ argName };

		// check that the argument has read permissions
		if (!checkReadPermissions(argVec, ctx))
		{
			//reportMemError();
		}

		else
		{

			// if the paramemter is a pointer
			if (calledFunc._paramType == POINTER)
			{
				//make sure that the dereference operator * is not in the function call
				if (ctx->getText().find("*") != string::npos)
				{
					reportMemError(ctx);

					cout << "data type of parameter and argument do not match in func call\n";
				}

				// no * in call, drop all of the argument's permissions
				else
				{
					if (currentFunction.locals[argName].dataType != POINTER)
					{
						reportMemError(ctx);

						cout << "data type of parameter and argument do not match in func call\n";
					}

					else
					{
						dropVar(argName);
					}
				}
			}
		}
	}

} // end enterFuncCall



/*
function: enterMain
Description: same as for enterFuncDef
*/
void MemSafetyPass::enterMain(InoxisParser::MainContext* ctx)
{
	currentFunction = functions.get(ctx);

	// sentinel drops permissions for borower and regains for borowee

	// create new vector of variants (either parse tree node, or sentinal) called anotatedStatements
	vector<variant<string, sentinal>>  anotatedStatements;


	// make sure the function contains statements
	if (ctx->statList() != NULL)
	{
		// get the statements vector
		auto s = ctx->statList()->statement();

		// convert to strings
		vector<string>  statements = convertStatementsToString(s, ctx->return_());

		vector<string>  whileVars;

		// for statement in statements
		for (int i = 0; i < statements.size(); i++)
		{
			string statement = statements[i];

			if (statement == "ENTER_WHILE")
				inWhileLoop = true;

			// once we exit while loop, we need to check all vars used in it and add sentinals
			if (statement == "EXIT_WHILE")
			{
				inWhileLoop = false;

				for (int k = 0; k < whileVars.size(); k++)
				{
					string varName = whileVars[k];

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
							if (isFinalUse(statements, i + 1, varName))
							{
								// add sentinal for var to anotatedStatements
								sentinal newSentinal{ varName, false };

								anotatedStatements.push_back(newSentinal);
							}
						}
					}
				}

				whileVars.clear();
			}

			anotatedStatements.push_back(statement);

			vector<string> vars = getVars(statement);

			// loop through all vars in statement
			for (int j = 0; j < vars.size(); j++)
			{
				string varName = vars[j];

				// if we're in a while loop, we don't want to add a sentinal
				// add the var to a list we'll check after we exit loop
				if (inWhileLoop)
				{
					whileVars.push_back(varName);
				}

				else
				{

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
							if (isFinalUse(statements, i + 1, varName))
							{
								// add sentinal for var to anotatedStatements
								sentinal newSentinal{ varName, false };

								anotatedStatements.push_back(newSentinal);
							}
						}
					}
				}
			}
		}




		// now we save the anotated statements so that we can keep track of when 
		// variables are dropped while we walk the rest of the parse tree for this function
		currentStatList = anotatedStatements;


	}
} // end enterMain



/*
function: enterFuncDef
Description: loop through all statements in the function, adding them to annotatedStatements.
for each local variable, after the last time it's used, add a sentinal for it to annotatedStatements
*/
void MemSafetyPass::enterFuncDef(InoxisParser::FuncDefContext* ctx) 
{

	currentFunction = functions.get(ctx);

	string paramName = ctx->param()->ID()->getText();

	// sentinel drops permissions for borower and regains for borowee

	// create new vector of variants (either parse tree node, or sentinal) called anotatedStatements
	vector<variant<string, sentinal>>  anotatedStatements;

	int i = 0;

	vector<string>  whileVars;

	// make sure the function contains statements
	if (ctx->statList() != NULL)
	{
		// get the statements vector
		auto s = ctx->statList()->statement();

		vector<string> statements = convertStatementsToString(s, ctx->return_());

		// first need to add the sentinal for the parameter if it's not used

		// check if there's a sentinal value for the variable
		if (!checkIfSentinal(anotatedStatements, 0, paramName))
		{
			if (isFinalUse(statements, 0, paramName))
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

			anotatedStatements.push_back(statement);

			vector<string> vars = getVars(statement);

			if (statement == "ENTER_WHILE")
				inWhileLoop = true;

			// once we exit while loop, we need to check all vars used in it and add sentinals
			if (statement == "EXIT_WHILE")
			{
				inWhileLoop = false;

				for (int k = 0; k < whileVars.size(); k++)
				{
					string varName = whileVars[k];

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
							if (isFinalUse(statements, i + 1, varName))
							{
								// add sentinal for var to anotatedStatements
								sentinal newSentinal{ varName, false };

								anotatedStatements.push_back(newSentinal);
							}
						}
					}
				}

				whileVars.clear();
			}

			// loop through all vars in statement
			for (int j = 0; j < vars.size(); j++)
			{
				string varName = vars[j];

				// if we're in a while loop, we don't want to add a sentinal
				// add the var to a list we'll check after we exit loop
				if (inWhileLoop)
				{
					whileVars.push_back(varName);
				}

				else
				{

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
							if (isFinalUse(statements, i + 1, varName))
							{
								// add sentinal for var to anotatedStatements
								sentinal newSentinal{ varName, false };

								anotatedStatements.push_back(newSentinal);
							}
						}
					}
				}
			}
		}




		// now we save the anotated statements so that we can keep track of when 
		// variables are dropped while we walk the rest of the parse tree for this function
		currentStatList = anotatedStatements;

	}



	// now we have to initialize the parameters permissions
	if (ctx->param()->mut()->getText() == "mut")
	{
		currentFunction.locals[paramName].setPermissions(read | write | own, false);
	}

	else
	{
		currentFunction.locals[paramName].setPermissions(read | own, false);
	}
} // end enterFuncDef





// getVars()
// description: loop through all of the local variable names and searhc the input string for them and add any hits
// to the returned string vector
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
} // end getVars



// function: checkIFSentinal
// loop through rest of the anotated statements starting from 'start' index
// check if there's a sentinal value for var
bool MemSafetyPass::checkIfSentinal(vector<variant<string, sentinal>>
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

				cout << "Exception: " << ex.what() << endl;
			}
		}
	}

	return false;
} // end checkIfSentinal




// function: isFinalUse
// given a variable name, and the index of current statement + 1, check if the variable is used in the 
// remaining statements
bool   MemSafetyPass::isFinalUse(vector<string> statements, int start, string var)
{
	// loop through statements
	for (int i = start; i < statements.size(); i++)
	{
		// get current statement
		auto statement = statements[i];

		vector<string> vars;

		//cout << statement->getText() << endl;

		// get all the variable names in statement
		vars = getVars(statement);

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
} // end isFinalUse












// function: incrementStatements
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
		if (holds_alternative<string>(currentStatList[statementIndex]))
		{
			try
			{

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

			if(!holds_alternative<sentinal>(currentStatList[statementIndex]))
				break;

			try
			{
				// get the name of the dropped var and then drop its permissions
				sentinal currentSentinal = get<sentinal>(currentStatList[statementIndex]);

				bool setSentinalFlag = false;

				// if the variable is a borrow, only free the data if the borrowee has been dropped
				// since the borrowee will regain permissions and own the heap data again
				// data will be freed after the borrowee is dropped in that case
				if (currentFunction.locals[currentSentinal.varName].ownsHeapData)
				{
					// if borrow, check if borowee has been dropped
					if (currentFunction.locals[currentSentinal.varName].isBorrow)
					{
						// get borrowee name
						string borroweeName = currentFunction.locals[currentSentinal.varName].borrowee;

						// if it's been dropped, free data
						if (currentFunction.locals[borroweeName].hasBeenDropped)
							setSentinalFlag = true;
					}

					else
						setSentinalFlag = true;
				}

				if (setSentinalFlag)
				{
					currentSentinal.heapAllocation = true;

					currentStatList[statementIndex].emplace<sentinal>(currentSentinal);
				}

				dropVar(currentSentinal.varName);

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
			if (holds_alternative<string>(currentStatList[statementIndex]))
			{
				try
				{

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
} // end incrementStatement



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



		// if the dropped var is a borrow
		if (currentFunction.locals[varName].isBorrow)
		{
			string borroweeName = currentFunction.locals[varName].borrowee;

			// its borrowee now regains its permissions
			if (currentFunction.locals.count(borroweeName) == 1 && !currentFunction.locals[borroweeName].hasBeenDropped)
			{
				currentFunction.locals[borroweeName].regainPermissions();

				// borrowee now owns heap data again
				if (currentFunction.locals[varName].ownsHeapData == true)
				{
					currentFunction.locals[borroweeName].ownsHeapData = true;

				}
			}

			if (currentFunction.locals[varName].ownsHeapData == true)
			{
				currentFunction.locals[varName].ownsHeapData = false;

			}
		}

		// not a borrow, just drop heap ownership
		else
		{
			if (currentFunction.locals[varName].ownsHeapData == true)
				currentFunction.locals[varName].ownsHeapData = false;
		}
	}
} // end dropVar