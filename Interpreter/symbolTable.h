#pragma once
#include "antlr4-runtime.h"
#include ".antlr/InoxisBaseListener.h"
#include "funcSymbol.h"
#include "dataType.h"
#include <string>
#include <map>
#include <iostream>

using namespace std;






class symbolTable : public InoxisBaseListener
{
public:

	symbolTable() : numErrors(0) {};




	void enterFuncDec(InoxisParser::FuncDecContext* ctx);

	void enterFuncDef(InoxisParser::FuncDefContext* ctx);

	void enterVarDec(InoxisParser::VarDecContext* ctx);

	void enterMain(InoxisParser::MainContext* ctx);

	void exitMain(InoxisParser::MainContext* ctx);

	void enterVar(InoxisParser::VarContext* ctx);

	void enterFuncCall(InoxisParser::FuncCallContext* ctx);

	void exitFuncDef(InoxisParser::FuncDefContext* ctx);




	bool compFuncSignatures(funcSymbol func1, funcSymbol func2);

	void reportError(antlr4::ParserRuleContext* ctx) { 
		size_t line = ctx->getStart()->getLine();
		cout << "Line " << line << ": ";
		numErrors++; 
	};




	// need some error checking and tracking code
	int numErrors;

	antlr4::tree::ParseTreeProperty<funcSymbol>  treeFuncSymbols;

	map<string, funcSymbol> funcSymbols;

	antlr4::tree::ParseTreeProperty<vector<varSymbol>>  varListProp;

	vector<varSymbol>  variablesList;

	funcSymbol  currentFunction;
};


