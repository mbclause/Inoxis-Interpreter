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




	//assign: var '=' assignRHS ';';
	void enterAssign(InoxisParser::AssignContext* ctx);

	void enterFuncDef(InoxisParser::FuncDefContext* ctx);

	void exitFuncDef(InoxisParser::FuncDefContext* ctx) { inFuncDef = false; resetStatList(); };

	void enterMain(InoxisParser::MainContext* ctx);

	void exitMain(InoxisParser::MainContext* ctx) { inFuncDef = false; resetStatList(); };

	void exitStatement(InoxisParser::StatementContext* ctx) { incrementStatements(); };




	void reportMemError() { _numErrors++; };

	vector<string>  getVars(string statement);

	bool   checkIfSentinal(vector<variant<InoxisParser::StatementContext*, sentinal>>  statements, int start, string var);

	bool   isFinalUse(vector<InoxisParser::StatementContext*>  statements, int start, string var);

	void  incrementStatements();

	void  resetStatList() { statementIndex = 0; };

	void  dropVar(string varName);


	// data members
	ParseTreeProperty<funcSymbol> functions;

	vector<variant<InoxisParser::StatementContext*, sentinal>> currentStatList;

	int  statementIndex;

	int _numErrors;

	funcSymbol currentFunction;

	bool   inFuncDef;
};