/*
File: MemSafetyPass.h
Description: The class definition for the MemSafetyPass class. 
Since it also walks the AST, it inherits from the InoxisBaseListener class. As it walks the AST, it sets memory 
permissions for varSymbol objects and also checks that they have the required permissions for the operation.
*/

#pragma once
#include "antlr4-runtime.h"
#include ".antlr/InoxisBaseListener.h"
#include "symbolTable.h"
#include "dataType.h"
#include <string>
#include <variant>
#include <map>
#include <iostream>

using namespace std;
using namespace antlr4::tree;


// this struct is a flag that represents when a variable goes out of scope
struct sentinal
{
	string varName;

	bool   heapAllocation;
};





// Class Definition: MemSafetyPass
class MemSafetyPass : public InoxisBaseListener
{
public:
	// ctors
	MemSafetyPass(ParseTreeProperty<funcSymbol> funcs) : functions(funcs), _numErrors(0), statementIndex(0),
	inWhileLoop(false) {};

	MemSafetyPass() : _numErrors(0), statementIndex(0), inWhileLoop(false) {};




	// overloaded InoxisListener functions
	void enterAssign(InoxisParser::AssignContext* ctx);

	void enterFuncCall(InoxisParser::FuncCallContext* ctx);

	void enterFuncDef(InoxisParser::FuncDefContext* ctx);

	void exitFuncDef(InoxisParser::FuncDefContext* ctx) { statLists.put(ctx, currentStatList); resetStatList(); };

	void enterMain(InoxisParser::MainContext* ctx);

	void exitMain(InoxisParser::MainContext* ctx) { statLists.put(ctx, currentStatList); resetStatList(); };

	void exitStatement(InoxisParser::StatementContext* ctx) { incrementStatements(); };

	void exitReturn(InoxisParser::ReturnContext* ctx) { incrementStatements(); };

	void enterVarDec(InoxisParser::VarDecContext* ctx);

	void enterPrint(InoxisParser::PrintContext* ctx);

	void enterOut(InoxisParser::OutContext* ctx);

	// check type safety
	void exitVarDec(InoxisParser::VarDecContext* ctx) {
		if (ctx->varDecRHS()->getText().length() > 0)
			checkDeclarationTypeSafety(ctx);
	}

	void exitAssign(InoxisParser::AssignContext* ctx) { checkAssignTypeSafety(ctx); }

	// check if the variable expression evaluates to an integer
	void exitVarDecRHS(InoxisParser::VarDecRHSContext* ctx) {
		bool isInt = expIsIntProp.get(ctx->assignRHS());
		expIsIntProp.put(ctx, isInt); 
	}

	void exitAssignRHS(InoxisParser::AssignRHSContext* ctx) { 
		if (ctx->expression())
		{
			bool isInt = expIsIntProp.get(ctx->expression());

			expIsIntProp.put(ctx, isInt);
		}
	}

	void  exitVar(InoxisParser::VarContext* ctx);

	void exitAdd(InoxisParser::AddContext* ctx) {
		bool  left = expIsIntProp.get(ctx->expression()[0]);

		bool  right = expIsIntProp.get(ctx->expression()[1]);

		bool  result = false;

		if (left && right)
			result = true;

		expIsIntProp.put(ctx, result);
	}

	void exitNumLiteral(InoxisParser::NumLiteralContext* ctx) { expIsIntProp.put(ctx, true); }

	void exitSubtract(InoxisParser::SubtractContext* ctx) {
		bool  left = expIsIntProp.get(ctx->expression()[0]);

		bool  right = expIsIntProp.get(ctx->expression()[1]);

		bool  result = false;

		if (left && right)
			result = true;

		expIsIntProp.put(ctx, result);
	}

	void exitFuncCallExp(InoxisParser::FuncCallExpContext* ctx) { expIsIntProp.put(ctx, true); }

	void exitVarLiteral(InoxisParser::VarLiteralContext* ctx) { expIsIntProp.put(ctx, expIsIntProp.get(ctx->var())); }





	// member functions
	void reportMemError(antlr4::ParserRuleContext* ctx) {
		size_t line = ctx->getStart()->getLine();
		cout << "Line " << line << ": ";
		_numErrors++;
	};


	vector<string>  getVars(string statement);

	bool   checkIfSentinal(vector<variant<string, sentinal>>
		statements, int start, string var);

	bool   isFinalUse(vector<string>  statements, int start, string var);

	void  incrementStatements();

	void  resetStatList() { statementIndex = 0; };

	void  dropVar(string varName);

	bool  checkReadPermissions(vector<string> vars, antlr4::ParserRuleContext* ctx);
	
	vector<string>  getPrintVars(InoxisParser::PrintContext* ctx);

	vector<string>  convertStatementsToString(vector<InoxisParser::StatementContext*>  statements, 
		InoxisParser::ReturnContext* returnStatement);

	void  addConditionalStatements(InoxisParser::StatementContext* condStatement, vector<string> &stringStatements);

	void  checkAssignTypeSafety(InoxisParser::AssignContext* ctx);

	void  checkDeclarationTypeSafety(InoxisParser::VarDecContext* ctx);


	void  printStatList() {
		for (int i = 0; i < currentStatList.size(); i++)
		{
			if (holds_alternative<string>(currentStatList[i]))
				cout << get<string>(currentStatList[i]) << endl;

			else
				cout << get<sentinal>(currentStatList[i]).varName << " dropped\n";
		}
	}


	// data members
	ParseTreeProperty<funcSymbol> functions;

	ParseTreeProperty<vector<variant<string, sentinal>>> statLists;

	vector<variant<string, sentinal>> currentStatList;

	ParseTreeProperty<bool>   expIsIntProp;

	int  statementIndex;

	int _numErrors;

	bool  inWhileLoop;

	funcSymbol currentFunction;
};