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


struct sentinal
{
	string varName;

	bool   heapAllocation;
};



// need to actually set heapAllocation in sentinal 

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

	void exitMain(InoxisParser::MainContext* ctx) { statLists.put(ctx, currentStatList); 
	printStatList();
	resetStatList(); };

	void exitStatement(InoxisParser::StatementContext* ctx) { incrementStatements(); };

	void exitReturn(InoxisParser::ReturnContext* ctx) { incrementStatements(); };

	void enterVarDec(InoxisParser::VarDecContext* ctx);

	void enterPrint(InoxisParser::PrintContext* ctx);

	void enterOut(InoxisParser::OutContext* ctx);




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

	int  statementIndex;

	int _numErrors;

	bool  inWhileLoop;

	funcSymbol currentFunction;
};