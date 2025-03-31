#include "MemSafetyPass.h"



void MemSafetyPass::enterMain(InoxisParser::MainContext* ctx)
{
	currentFunction = functions.get(ctx);

	inFuncDef = true;

	cout << "MAIN\n";

	// sentinel drops permissions for borower and regains for borowee

	// create new vector of variants (either parse tree node, or sentinal) called anotatedStatements
	vector<variant<InoxisParser::StatementContext*, sentinal>>  anotatedStatements;


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
						if (isFinalUse(statements, i + 1, varName))
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



void MemSafetyPass::enterFuncDef(InoxisParser::FuncDefContext* ctx) 
{
	inFuncDef = true;

	currentFunction = functions.get(ctx);

	cout << endl << currentFunction.getName() << endl;

	// sentinel drops permissions for borower and regains for borowee

	// create new vector of variants (either parse tree node, or sentinal) called anotatedStatements
	vector<variant<InoxisParser::StatementContext*, sentinal>>  anotatedStatements;


	// make sure the function contains statements
	if (ctx->statList() != NULL)
	{
		// get the statements vector
		auto statements = ctx->statList()->statement();

		// first need to add the sentinal for the parameter
		string paramName = ctx->param()->ID()->getText();

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
bool MemSafetyPass::checkIfSentinal(vector<variant<InoxisParser::StatementContext*, sentinal>>  statements, 
	int start, string var)
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
bool   MemSafetyPass::isFinalUse(vector<InoxisParser::StatementContext*>  statements, int start, string var)
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

	// if we reach the end, return true
	return true;
}









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




// increment statList index, make sure we're in bounds
// while the current statement is a sentinal, call dropPermissions()
void  MemSafetyPass::incrementStatements()
{
	if(statementIndex == 0)
		cout << get<InoxisParser::StatementContext*>(currentStatList[statementIndex])->getText() << endl;

	statementIndex++;

	// make sure we haven't reached the end of the list
	// this will happen if we've reached the end of the function and there are no sentinals left
	if (statementIndex < currentStatList.size())
	{
		// while the current statment is a sentinel...
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

				// dropPermissions(currentSentinal.varName);

				cout << currentSentinal.varName << " dropped \n";
			}

			catch (std::bad_variant_access const& ex)
			{
				cout << "bad variant access\n";
			}

			// go to next statement
			statementIndex++;
		}

		// otherwise print the next statement
		if (statementIndex < currentStatList.size())
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
			}
		}
	}
}