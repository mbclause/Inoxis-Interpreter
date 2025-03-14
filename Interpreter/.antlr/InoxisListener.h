
// Generated from Inoxis.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "InoxisParser.h"

/*
Need to write functions (not sure whether enter/exit for all of them):

enterFuncDef (add function to symbol table)

enterfuncCall (check symbol table)

enterfuncDef (check symbol table)

enterParam (add param id to symbol table for function)

enterVarDec (add variable to function symbol table, add appropriate info about whether it's mut or not)

enterVar (check symbol table, check mem safety if needsMemSafety flag is set)




enterassignRHS (check whether variable is mut or not, if there's allocation, update memSafety info for variable)
*/


/**
 * This interface defines an abstract listener for a parse tree produced by InoxisParser.
 * 
 * The biggest difference between the listener and visitor mechanisms is that 
 listener methods are called by the ANTLR-provided walker object, whereas visitor 
 methods must walk their children with explicit visit calls. 
 Forgetting to invoke visit on a node�s children means those subtrees don�t get visited. 
 */
class  InoxisListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(InoxisParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(InoxisParser::ProgramContext *ctx) = 0;

  virtual void enterFuncDecs(InoxisParser::FuncDecsContext *ctx) = 0;
  virtual void exitFuncDecs(InoxisParser::FuncDecsContext *ctx) = 0;

  virtual void enterMain(InoxisParser::MainContext *ctx) = 0;
  virtual void exitMain(InoxisParser::MainContext *ctx) = 0;

  virtual void enterFuncDefs(InoxisParser::FuncDefsContext *ctx) = 0;
  virtual void exitFuncDefs(InoxisParser::FuncDefsContext *ctx) = 0;

  virtual void enterStatList(InoxisParser::StatListContext *ctx) = 0;
  virtual void exitStatList(InoxisParser::StatListContext *ctx) = 0;

  virtual void enterFuncDec(InoxisParser::FuncDecContext *ctx) = 0;
  virtual void exitFuncDec(InoxisParser::FuncDecContext *ctx) = 0;

  virtual void enterFuncDef(InoxisParser::FuncDefContext *ctx) = 0;
  virtual void exitFuncDef(InoxisParser::FuncDefContext *ctx) = 0;

  virtual void enterFuncCall(InoxisParser::FuncCallContext *ctx) = 0;
  virtual void exitFuncCall(InoxisParser::FuncCallContext *ctx) = 0;

  virtual void enterFuncCallFactor(InoxisParser::FuncCallFactorContext *ctx) = 0;
  virtual void exitFuncCallFactor(InoxisParser::FuncCallFactorContext *ctx) = 0;

  virtual void enterParam(InoxisParser::ParamContext *ctx) = 0;
  virtual void exitParam(InoxisParser::ParamContext *ctx) = 0;

  virtual void enterVar(InoxisParser::VarContext *ctx) = 0;
  virtual void exitVar(InoxisParser::VarContext *ctx) = 0;

  virtual void enterVarDec(InoxisParser::VarDecContext *ctx) = 0;
  virtual void exitVarDec(InoxisParser::VarDecContext *ctx) = 0;

  virtual void enterArg(InoxisParser::ArgContext *ctx) = 0;
  virtual void exitArg(InoxisParser::ArgContext *ctx) = 0;

  virtual void enterIndex(InoxisParser::IndexContext *ctx) = 0;
  virtual void exitIndex(InoxisParser::IndexContext *ctx) = 0;

  virtual void enterStatement(InoxisParser::StatementContext *ctx) = 0;
  virtual void exitStatement(InoxisParser::StatementContext *ctx) = 0;

  virtual void enterAssign(InoxisParser::AssignContext *ctx) = 0;
  virtual void exitAssign(InoxisParser::AssignContext *ctx) = 0;

  virtual void enterReturn(InoxisParser::ReturnContext *ctx) = 0;
  virtual void exitReturn(InoxisParser::ReturnContext *ctx) = 0;

  virtual void enterRetVal(InoxisParser::RetValContext *ctx) = 0;
  virtual void exitRetVal(InoxisParser::RetValContext *ctx) = 0;

  virtual void enterMut(InoxisParser::MutContext *ctx) = 0;
  virtual void exitMut(InoxisParser::MutContext *ctx) = 0;

  virtual void enterPointRef(InoxisParser::PointRefContext *ctx) = 0;
  virtual void exitPointRef(InoxisParser::PointRefContext *ctx) = 0;

  virtual void enterSubscript(InoxisParser::SubscriptContext *ctx) = 0;
  virtual void exitSubscript(InoxisParser::SubscriptContext *ctx) = 0;

  virtual void enterArray(InoxisParser::ArrayContext *ctx) = 0;
  virtual void exitArray(InoxisParser::ArrayContext *ctx) = 0;

  virtual void enterAllocate(InoxisParser::AllocateContext *ctx) = 0;
  virtual void exitAllocate(InoxisParser::AllocateContext *ctx) = 0;

  virtual void enterVarDecRHS(InoxisParser::VarDecRHSContext *ctx) = 0;
  virtual void exitVarDecRHS(InoxisParser::VarDecRHSContext *ctx) = 0;

  virtual void enterAssignRHS(InoxisParser::AssignRHSContext *ctx) = 0;
  virtual void exitAssignRHS(InoxisParser::AssignRHSContext *ctx) = 0;

  virtual void enterExpression(InoxisParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(InoxisParser::ExpressionContext *ctx) = 0;

  virtual void enterFactor(InoxisParser::FactorContext *ctx) = 0;
  virtual void exitFactor(InoxisParser::FactorContext *ctx) = 0;

  virtual void enterWhile(InoxisParser::WhileContext *ctx) = 0;
  virtual void exitWhile(InoxisParser::WhileContext *ctx) = 0;

  virtual void enterIfElseBlock(InoxisParser::IfElseBlockContext *ctx) = 0;
  virtual void exitIfElseBlock(InoxisParser::IfElseBlockContext *ctx) = 0;

  virtual void enterElif(InoxisParser::ElifContext *ctx) = 0;
  virtual void exitElif(InoxisParser::ElifContext *ctx) = 0;

  virtual void enterElse(InoxisParser::ElseContext *ctx) = 0;
  virtual void exitElse(InoxisParser::ElseContext *ctx) = 0;

  virtual void enterCondition(InoxisParser::ConditionContext *ctx) = 0;
  virtual void exitCondition(InoxisParser::ConditionContext *ctx) = 0;

  virtual void enterNot(InoxisParser::NotContext *ctx) = 0;
  virtual void exitNot(InoxisParser::NotContext *ctx) = 0;

  virtual void enterCondOp(InoxisParser::CondOpContext *ctx) = 0;
  virtual void exitCondOp(InoxisParser::CondOpContext *ctx) = 0;

  virtual void enterCondRHS(InoxisParser::CondRHSContext *ctx) = 0;
  virtual void exitCondRHS(InoxisParser::CondRHSContext *ctx) = 0;


};

