
// Generated from Inoxis.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "InoxisListener.h"


/**
 * This class provides an empty implementation of InoxisListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  InoxisBaseListener : public InoxisListener {
public:

  virtual void enterProgram(InoxisParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(InoxisParser::ProgramContext * /*ctx*/) override { }

  virtual void enterFuncDecs(InoxisParser::FuncDecsContext * /*ctx*/) override { }
  virtual void exitFuncDecs(InoxisParser::FuncDecsContext * /*ctx*/) override { }

  virtual void enterMain(InoxisParser::MainContext * /*ctx*/) override { }
  virtual void exitMain(InoxisParser::MainContext * /*ctx*/) override { }

  virtual void enterFuncDefs(InoxisParser::FuncDefsContext * /*ctx*/) override { }
  virtual void exitFuncDefs(InoxisParser::FuncDefsContext * /*ctx*/) override { }

  virtual void enterStatList(InoxisParser::StatListContext * /*ctx*/) override { }
  virtual void exitStatList(InoxisParser::StatListContext * /*ctx*/) override { }

  virtual void enterFuncDec(InoxisParser::FuncDecContext * /*ctx*/) override { }
  virtual void exitFuncDec(InoxisParser::FuncDecContext * /*ctx*/) override { }

  virtual void enterFuncDef(InoxisParser::FuncDefContext * /*ctx*/) override { }
  virtual void exitFuncDef(InoxisParser::FuncDefContext * /*ctx*/) override { }

  virtual void enterFuncCall(InoxisParser::FuncCallContext * /*ctx*/) override { }
  virtual void exitFuncCall(InoxisParser::FuncCallContext * /*ctx*/) override { }

  virtual void enterFuncCallFactor(InoxisParser::FuncCallFactorContext * /*ctx*/) override { }
  virtual void exitFuncCallFactor(InoxisParser::FuncCallFactorContext * /*ctx*/) override { }

  virtual void enterParam(InoxisParser::ParamContext * /*ctx*/) override { }
  virtual void exitParam(InoxisParser::ParamContext * /*ctx*/) override { }

  virtual void enterVar(InoxisParser::VarContext * /*ctx*/) override { }
  virtual void exitVar(InoxisParser::VarContext * /*ctx*/) override { }

  virtual void enterVarDec(InoxisParser::VarDecContext * /*ctx*/) override { }
  virtual void exitVarDec(InoxisParser::VarDecContext * /*ctx*/) override { }

  virtual void enterArg(InoxisParser::ArgContext * /*ctx*/) override { }
  virtual void exitArg(InoxisParser::ArgContext * /*ctx*/) override { }

  virtual void enterIndex(InoxisParser::IndexContext * /*ctx*/) override { }
  virtual void exitIndex(InoxisParser::IndexContext * /*ctx*/) override { }

  virtual void enterStatement(InoxisParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(InoxisParser::StatementContext * /*ctx*/) override { }

  virtual void enterAssign(InoxisParser::AssignContext * /*ctx*/) override { }
  virtual void exitAssign(InoxisParser::AssignContext * /*ctx*/) override { }

  virtual void enterPrint(InoxisParser::PrintContext * /*ctx*/) override { }
  virtual void exitPrint(InoxisParser::PrintContext * /*ctx*/) override { }

  virtual void enterOut(InoxisParser::OutContext * /*ctx*/) override { }
  virtual void exitOut(InoxisParser::OutContext * /*ctx*/) override { }

  virtual void enterReturn(InoxisParser::ReturnContext * /*ctx*/) override { }
  virtual void exitReturn(InoxisParser::ReturnContext * /*ctx*/) override { }

  virtual void enterRetVal(InoxisParser::RetValContext * /*ctx*/) override { }
  virtual void exitRetVal(InoxisParser::RetValContext * /*ctx*/) override { }

  virtual void enterMut(InoxisParser::MutContext * /*ctx*/) override { }
  virtual void exitMut(InoxisParser::MutContext * /*ctx*/) override { }

  virtual void enterPointRef(InoxisParser::PointRefContext * /*ctx*/) override { }
  virtual void exitPointRef(InoxisParser::PointRefContext * /*ctx*/) override { }

  virtual void enterSubscript(InoxisParser::SubscriptContext * /*ctx*/) override { }
  virtual void exitSubscript(InoxisParser::SubscriptContext * /*ctx*/) override { }

  virtual void enterArray(InoxisParser::ArrayContext * /*ctx*/) override { }
  virtual void exitArray(InoxisParser::ArrayContext * /*ctx*/) override { }

  virtual void enterAllocate(InoxisParser::AllocateContext * /*ctx*/) override { }
  virtual void exitAllocate(InoxisParser::AllocateContext * /*ctx*/) override { }

  virtual void enterVarDecRHS(InoxisParser::VarDecRHSContext * /*ctx*/) override { }
  virtual void exitVarDecRHS(InoxisParser::VarDecRHSContext * /*ctx*/) override { }

  virtual void enterAssignRHS(InoxisParser::AssignRHSContext * /*ctx*/) override { }
  virtual void exitAssignRHS(InoxisParser::AssignRHSContext * /*ctx*/) override { }

  virtual void enterExpression(InoxisParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(InoxisParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterFactor(InoxisParser::FactorContext * /*ctx*/) override { }
  virtual void exitFactor(InoxisParser::FactorContext * /*ctx*/) override { }

  virtual void enterWhile(InoxisParser::WhileContext * /*ctx*/) override { }
  virtual void exitWhile(InoxisParser::WhileContext * /*ctx*/) override { }

  virtual void enterIfElseBlock(InoxisParser::IfElseBlockContext * /*ctx*/) override { }
  virtual void exitIfElseBlock(InoxisParser::IfElseBlockContext * /*ctx*/) override { }

  virtual void enterElif(InoxisParser::ElifContext * /*ctx*/) override { }
  virtual void exitElif(InoxisParser::ElifContext * /*ctx*/) override { }

  virtual void enterElse(InoxisParser::ElseContext * /*ctx*/) override { }
  virtual void exitElse(InoxisParser::ElseContext * /*ctx*/) override { }

  virtual void enterCondition(InoxisParser::ConditionContext * /*ctx*/) override { }
  virtual void exitCondition(InoxisParser::ConditionContext * /*ctx*/) override { }

  virtual void enterNot(InoxisParser::NotContext * /*ctx*/) override { }
  virtual void exitNot(InoxisParser::NotContext * /*ctx*/) override { }

  virtual void enterCondOp(InoxisParser::CondOpContext * /*ctx*/) override { }
  virtual void exitCondOp(InoxisParser::CondOpContext * /*ctx*/) override { }

  virtual void enterCondRHS(InoxisParser::CondRHSContext * /*ctx*/) override { }
  virtual void exitCondRHS(InoxisParser::CondRHSContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

