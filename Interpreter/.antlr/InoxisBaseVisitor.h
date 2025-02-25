
// Generated from Inoxis.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "InoxisVisitor.h"


/**
 * This class provides an empty implementation of InoxisVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  InoxisBaseVisitor : public InoxisVisitor {
public:

  virtual std::any visitProgram(InoxisParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDecs(InoxisParser::FuncDecsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMain(InoxisParser::MainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDefs(InoxisParser::FuncDefsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatList(InoxisParser::StatListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDec(InoxisParser::FuncDecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(InoxisParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncCall(InoxisParser::FuncCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncCallFactor(InoxisParser::FuncCallFactorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParam(InoxisParser::ParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVar(InoxisParser::VarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDec(InoxisParser::VarDecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArg(InoxisParser::ArgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndex(InoxisParser::IndexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(InoxisParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssign(InoxisParser::AssignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturn(InoxisParser::ReturnContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRetVal(InoxisParser::RetValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMut(InoxisParser::MutContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPointRef(InoxisParser::PointRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubscript(InoxisParser::SubscriptContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray(InoxisParser::ArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAllocate(InoxisParser::AllocateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecRHS(InoxisParser::VarDecRHSContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignRHS(InoxisParser::AssignRHSContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(InoxisParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFactor(InoxisParser::FactorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhile(InoxisParser::WhileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfElseBlock(InoxisParser::IfElseBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElif(InoxisParser::ElifContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElse(InoxisParser::ElseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondition(InoxisParser::ConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNot(InoxisParser::NotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondOp(InoxisParser::CondOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondRHS(InoxisParser::CondRHSContext *ctx) override {
    return visitChildren(ctx);
  }


};

