/*
File: VMInputPass.h
Description: This class will walk the AST and for each function 
*/

#pragma once
#include "antlr4-runtime.h"
#include ".antlr/InoxisBaseListener.h"
#include "symbolTable.h"
#include "dataType.h"
#include "MemSafetyPass.h"
#include "VMInput.h"
#include <string>
#include <variant>
#include <map>
#include <iostream>

using namespace std;
using namespace antlr4::tree;


class VMInputPass : public InoxisBaseListener
{
public:
	VMInputPass(ParseTreeProperty<vector<variant<InoxisParser::StatementContext*, sentinal,
		InoxisParser::ReturnContext*>>> _statLists, 
		ParseTreeProperty<funcSymbol> _symbolTables) : statLists(_statLists), 
		symbolTables(_symbolTables), statementIndex(0), numLocals(0), currentFuncIndex(0)
	{ 
		functions = g_array_new(false, false, sizeof(function));

		currentSymbolsGArray = g_array_new(false, false, sizeof(unsigned));
	};


	// ENTER_RULE
	// funcDec (add to functions, add parameter to symbols)
	// funcDef (set current statList)
	void enterFuncDef(InoxisParser::FuncDefContext* ctx);
	
	// main (set current statlist)
	void enterMain(InoxisParser::MainContext* ctx);
	
	// EXIT RULE
	// need these to build up expressions
	// enter numLiteral
	void exitNumLiteral(InoxisParser::NumLiteralContext* ctx);
	
	// varLiteral
	void exitVarLiteral(InoxisParser::VarLiteralContext* ctx);

	// funcCallExp

	// add
	void exitAdd(InoxisParser::AddContext* ctx);

	// subtract
	void exitSubtract(InoxisParser::SubtractContext* ctx);

	// rhsRef
	//void exitRhsRef(InoxisParser::RhsRefContext* ctx);

	// condition
	//void exitCondition(InoxisParser::ConditionContext* ctx);


	// statement types
	// varDec
	//void exitVarDec(InoxisParser::VarDecContext* ctx);

	// assign
	//void exitAssign(InoxisParser::AssignContext* ctx);

	// print
	//void exitPrint(InoxisParser::PrintContext* ctx);

	// out
	//void exitOut(InoxisParser::OutContext* ctx);

	// funcCall
	//void exitFuncCall(InoxisParser::FuncCallContext* ctx);
	
	// control flow
	// ifElseBlock
	//void exitIfElseBlock(InoxisParser::IfElseBlockContext* ctx);

	// elif
	//void exitElif(InoxisParser::ElifContext* ctx);

	// else
	//void exitElse(InoxisParser::ElseContext* ctx);

	// while
	//void exitWhile(InoxisParser::WhileContext* ctx);


	// funcDef (add statements)??
	void exitMain(InoxisParser::MainContext* ctx) { statementIndex = 0; }

	// allocate garrays for statements and locals, push a 0 to locals numLocals times
	void exitFuncDef(InoxisParser::FuncDefContext* ctx) { statementIndex = 0; }

	// also add statement to the function statements??
	void exitStatement(InoxisParser::StatementContext* ctx) { incrementStatements(); };

	void exitReturn(InoxisParser::ReturnContext* ctx) { incrementStatements(); };


	// need to have similar incrementStatList function to see when we reach sentinal for pointer var
	// then we would add a free statement for that var to the statements

	void  incrementStatements();


	// data members
	vector<variant<InoxisParser::StatementContext*, sentinal, InoxisParser::ReturnContext*>> currentStatList;

	int statementIndex;

	ParseTreeProperty<vector<variant<InoxisParser::StatementContext*, sentinal, InoxisParser::ReturnContext*>>> statLists;

	// do I need this??
	ParseTreeProperty<funcSymbol>  symbolTables;

	// current statements list for function

	// number of locals for current function
	int  numLocals;

	// index for current function
	int  currentFuncIndex;

	// GArray of functions
	GArray* functions;

	// map from var name to index for current function locals
	map<string, int>  currentLocalsMap;

	GArray* currentSymbolsGArray;

	const int zero = 0;


	// need parse tree properties for each struct
	ParseTreeProperty<literal>		litProp;

	ParseTreeProperty<unaryOp>		unaryProp;

	ParseTreeProperty<BinOp>		binaryOpProp;

	ParseTreeProperty<funcCall>		callProp;

	ParseTreeProperty<expression>	expProp;

	ParseTreeProperty<controlFlow>	flowProp;

	ParseTreeProperty<assign>		assgnProp;

	ParseTreeProperty<Return>		retProp;

	ParseTreeProperty<varDec>		decProp;

	ParseTreeProperty<print>		PrintProp;

	ParseTreeProperty<statement>	stmntProp;

	ParseTreeProperty<function>		funcProp;
};