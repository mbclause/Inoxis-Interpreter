
// Generated from Inoxis.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "InoxisParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by InoxisParser.
 */
class  InoxisVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by InoxisParser.
   */
    virtual std::any visitProgram(InoxisParser::ProgramContext *context) = 0;

    virtual std::any visitFuncDecs(InoxisParser::FuncDecsContext *context) = 0;

    virtual std::any visitMain(InoxisParser::MainContext *context) = 0;

    virtual std::any visitFuncDefs(InoxisParser::FuncDefsContext *context) = 0;

    virtual std::any visitStatList(InoxisParser::StatListContext *context) = 0;

    virtual std::any visitFuncDec(InoxisParser::FuncDecContext *context) = 0;

    virtual std::any visitFuncDef(InoxisParser::FuncDefContext *context) = 0;

    virtual std::any visitFuncCall(InoxisParser::FuncCallContext *context) = 0;

    virtual std::any visitFuncCallFactor(InoxisParser::FuncCallFactorContext *context) = 0;

    virtual std::any visitParam(InoxisParser::ParamContext *context) = 0;

    virtual std::any visitVar(InoxisParser::VarContext *context) = 0;

    virtual std::any visitVarDec(InoxisParser::VarDecContext *context) = 0;

    virtual std::any visitArg(InoxisParser::ArgContext *context) = 0;

    virtual std::any visitIndex(InoxisParser::IndexContext *context) = 0;

    virtual std::any visitStatement(InoxisParser::StatementContext *context) = 0;

    virtual std::any visitAssign(InoxisParser::AssignContext *context) = 0;

    virtual std::any visitPrint(InoxisParser::PrintContext *context) = 0;

    virtual std::any visitOut(InoxisParser::OutContext *context) = 0;

    virtual std::any visitReturn(InoxisParser::ReturnContext *context) = 0;

    virtual std::any visitRetVal(InoxisParser::RetValContext *context) = 0;

    virtual std::any visitMut(InoxisParser::MutContext *context) = 0;

    virtual std::any visitPointRef(InoxisParser::PointRefContext *context) = 0;

    virtual std::any visitSubscript(InoxisParser::SubscriptContext *context) = 0;

    virtual std::any visitArray(InoxisParser::ArrayContext *context) = 0;

    virtual std::any visitAllocate(InoxisParser::AllocateContext *context) = 0;

    virtual std::any visitVarDecRHS(InoxisParser::VarDecRHSContext *context) = 0;

    virtual std::any visitAssignRHS(InoxisParser::AssignRHSContext *context) = 0;

    virtual std::any visitRhsRef(InoxisParser::RhsRefContext *context) = 0;

    virtual std::any visitVarLiteral(InoxisParser::VarLiteralContext *context) = 0;

    virtual std::any visitAdd(InoxisParser::AddContext *context) = 0;

    virtual std::any visitNumLiteral(InoxisParser::NumLiteralContext *context) = 0;

    virtual std::any visitSubtract(InoxisParser::SubtractContext *context) = 0;

    virtual std::any visitFuncCallExp(InoxisParser::FuncCallExpContext *context) = 0;

    virtual std::any visitWhile(InoxisParser::WhileContext *context) = 0;

    virtual std::any visitIfElseBlock(InoxisParser::IfElseBlockContext *context) = 0;

    virtual std::any visitElif(InoxisParser::ElifContext *context) = 0;

    virtual std::any visitElse(InoxisParser::ElseContext *context) = 0;

    virtual std::any visitCondition(InoxisParser::ConditionContext *context) = 0;

    virtual std::any visitNot(InoxisParser::NotContext *context) = 0;

    virtual std::any visitCondOp(InoxisParser::CondOpContext *context) = 0;

    virtual std::any visitCondRHS(InoxisParser::CondRHSContext *context) = 0;


};

