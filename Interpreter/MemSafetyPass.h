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

	bool   isBorrow;
};



// Class Definition: MemSafetyPass
class MemSafetyPass : public InoxisBaseListener
{
public:
	// ctors
	MemSafetyPass(ParseTreeProperty<funcSymbol> funcs) : functions(funcs), _numErrors(0), 
		inFuncDef(false), statementIndex(0) {};

	MemSafetyPass() : _numErrors(0), inFuncDef(false), statementIndex(0) {};




	// overloaded InoxisListener functions
	void enterAssign(InoxisParser::AssignContext* ctx);

	void enterFuncCall(InoxisParser::FuncCallContext* ctx);

	void enterFuncDef(InoxisParser::FuncDefContext* ctx);

	void exitFuncDef(InoxisParser::FuncDefContext* ctx) { inFuncDef = false; resetStatList(); };

	void enterMain(InoxisParser::MainContext* ctx);

	void exitMain(InoxisParser::MainContext* ctx) { inFuncDef = false; resetStatList(); };

	void exitStatement(InoxisParser::StatementContext* ctx) { incrementStatements(); };

	void exitReturn(InoxisParser::ReturnContext* ctx) { incrementStatements(); };

	void enterVarDec(InoxisParser::VarDecContext* ctx);

	void enterPrint(InoxisParser::PrintContext* ctx);

	void enterOut(InoxisParser::OutContext* ctx);




	void reportMemError() { _numErrors++; };

	vector<string>  getVars(string statement);

	bool   checkIfSentinal(vector<variant<InoxisParser::StatementContext*, sentinal, InoxisParser::ReturnContext*>>
		statements, int start, string var);

	bool   isFinalUse(vector<InoxisParser::StatementContext*>  statements, InoxisParser::ReturnContext* returnStatement, 
		int start, string var);

	void  incrementStatements();

	void  resetStatList() { statementIndex = 0; };

	void  dropVar(string varName);

	bool  checkReadPermissions(vector<string> vars);
	
	vector<string>  getPrintVars(InoxisParser::PrintContext* ctx);


	// data members
	ParseTreeProperty<funcSymbol> functions;

	vector<variant<InoxisParser::StatementContext*, sentinal, InoxisParser::ReturnContext*>> currentStatList;

	int  statementIndex;

	int _numErrors;

	funcSymbol currentFunction;

	bool   inFuncDef;
};