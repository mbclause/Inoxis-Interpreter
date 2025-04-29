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
using namespace DataType;


class VMInputPass : public InoxisBaseListener
{
public:
	VMInputPass(ParseTreeProperty<vector<variant<string, sentinal>>> _statLists,
		ParseTreeProperty<funcSymbol> _symbolTables, ParseTreeProperty<vector<varSymbol>> varLists) :
		statLists(_statLists),
		symbolTables(_symbolTables), statementIndex(0), numLocals(0), currentFuncIndex(1), inControlBlock(false),
		varListProp(varLists)
	{ 
		// my array of function structs
		functions = g_array_new(false, false, sizeof(function));

		// symbol array for the current function
		currentSymbolsGArray = g_array_new(false, false, sizeof(memVal));

		currentStatementsGArray = g_array_new(false, false, sizeof(statement));
	};


	// ENTER_RULE
	// funcDec (add to functions, add parameter to symbols)
	void enterFuncDec(InoxisParser::FuncDecContext* ctx) {
		string funcName = ctx->ID()->getText();

		functionMap[funcName] = currentFuncIndex;

		currentFuncIndex++;
	}

	void enterWhile(InoxisParser::WhileContext* ctx);

	void enterIfElseBlock(InoxisParser::IfElseBlockContext* ctx);

	// funcDef (set current statList)
	void enterFuncDef(InoxisParser::FuncDefContext* ctx);
	
	// main (set current statlist)
	void enterMain(InoxisParser::MainContext* ctx);
	
	// EXIT RULE
	// need these to build up expressions
	// numLiteral
	void exitNumLiteral(InoxisParser::NumLiteralContext* ctx);
	
	// varLiteral
	void exitVarLiteral(InoxisParser::VarLiteralContext* ctx);

	// funcCallExp
	void exitFuncCallFactor(InoxisParser::FuncCallFactorContext* ctx);

	// add
	void exitAdd(InoxisParser::AddContext* ctx);

	// subtract
	void exitSubtract(InoxisParser::SubtractContext* ctx);

	// exitVar
	void exitVar(InoxisParser::VarContext* ctx);

	void exitIndex(InoxisParser::IndexContext* ctx);

	void exitArray(InoxisParser::ArrayContext* ctx)
	{
		expProp.put(ctx, expProp.get(ctx->index()));

		allocationSizeProp.put(ctx, allocationSizeProp.get(ctx->index()));
	}

	void exitArg(InoxisParser::ArgContext* ctx);

	// rhsRef
	void exitRhsRef(InoxisParser::RhsRefContext* ctx);


	// statement types
	// varDec
	void exitVarDec(InoxisParser::VarDecContext* ctx);

	void exitVarDecRHS(InoxisParser::VarDecRHSContext* ctx) {
		expProp.put(ctx, expProp.get(ctx->assignRHS()));

		allocationSizeProp.put(ctx, allocationSizeProp.get(ctx->assignRHS()));
	}

	void exitAssignRHS(InoxisParser::AssignRHSContext* ctx);

	void exitAllocate(InoxisParser::AllocateContext* ctx);

	// assign
	void exitAssign(InoxisParser::AssignContext* ctx);

	// print
	void exitPrint(InoxisParser::PrintContext* ctx);

	// out
	void exitOut(InoxisParser::OutContext* ctx);

	void exitPrintLiteral(InoxisParser::PrintLiteralContext* ctx);

	// funcCall
	void exitFuncCall(InoxisParser::FuncCallContext* ctx);

	void exitFuncCallExp(InoxisParser::FuncCallExpContext* ctx) {
		expProp.put(ctx, expProp.get(ctx->funcCallFactor()));
	}
	
	void exitReturn(InoxisParser::ReturnContext* ctx);

	void exitRetVal(InoxisParser::RetValContext* ctx) {
		expProp.put(ctx, expProp.get(ctx->expression()));
	}
	
	// control flow
	// ifElseBlock
	void exitIfElseBlock(InoxisParser::IfElseBlockContext* ctx);

	// elif
	void exitElif(InoxisParser::ElifContext* ctx);

	// else
	void exitElse(InoxisParser::ElseContext* ctx);

	// while
	void exitWhile(InoxisParser::WhileContext* ctx);

	// condition
	void exitCondition(InoxisParser::ConditionContext* ctx);

	void exitCondRHS(InoxisParser::CondRHSContext* ctx);


	// funcDef (add statements)??
	void exitMain(InoxisParser::MainContext* ctx);

	
	void exitFuncDef(InoxisParser::FuncDefContext* ctx);

	// also add statement to the function statements??
	void exitStatement(InoxisParser::StatementContext* ctx);


	// need to have similar incrementStatList function to see when we reach sentinal for pointer var
	// then we would add a free statement for that var to the statements

	void  incrementStatements();

	// function to get all of the blocks in an ifElseBlock statement
	GArray* getIfElseBlocks(InoxisParser::IfElseBlockContext* ctx);

	void  findControlFlowBlocks(InoxisParser::IfElseBlockContext* ifctx, 
		InoxisParser::WhileContext* whilectx, int  depth);


	// data members
	vector<variant<string, sentinal>> currentStatList;

	int statementIndex;

	ParseTreeProperty<vector<variant<string, sentinal>>> statLists;

	// do I need this??
	ParseTreeProperty<funcSymbol>  symbolTables;

	ParseTreeProperty<vector<varSymbol>> varListProp;

	// current statements list for function

	// number of locals for current function
	int  numLocals;

	// index for current function
	int  currentFuncIndex;

	funcSymbol  currentFunction;

	// GArray of functions, the output of the pass
	GArray* functions;

	// map from var name to index for current function locals
	map<string, unsigned>  currentLocalsMap;

	// map from function name to its index in the functions table
	map<string, int>  functionMap;

	// of type int
	GArray* currentSymbolsGArray;

	// of type statement
	GArray* currentStatementsGArray;

	const int zero = 0;

	// keep track of if we're in an if/else/while block
	bool  inControlBlock;


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

	ParseTreeProperty<int>			allocationSizeProp;

	ParseTreeProperty<vector<InoxisParser::StatListContext*>>  elifStatsProp;

	ParseTreeProperty<vector<InoxisParser::ConditionContext*>>  elifCondsProp;

	// property that keeps track of how deep we are in a control flow block
	ParseTreeProperty<int>    cfDepthProp;
};