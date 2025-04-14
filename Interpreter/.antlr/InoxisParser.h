
// Generated from Inoxis.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  InoxisParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    WS = 33, ID = 34, COMMENT = 35, INT = 36, STRING_LITERAL = 37
  };

  enum {
    RuleProgram = 0, RuleFuncDecs = 1, RuleMain = 2, RuleFuncDefs = 3, RuleStatList = 4, 
    RuleFuncDec = 5, RuleFuncDef = 6, RuleFuncCall = 7, RuleFuncCallFactor = 8, 
    RuleParam = 9, RuleVar = 10, RuleVarDec = 11, RuleArg = 12, RuleIndex = 13, 
    RuleStatement = 14, RuleAssign = 15, RulePrint = 16, RuleOut = 17, RuleReturn = 18, 
    RuleRetVal = 19, RuleMut = 20, RulePointRef = 21, RuleSubscript = 22, 
    RuleArray = 23, RuleAllocate = 24, RuleVarDecRHS = 25, RuleAssignRHS = 26, 
    RuleRhsRef = 27, RuleExpression = 28, RuleWhile = 29, RuleIfElseBlock = 30, 
    RuleElif = 31, RuleElse = 32, RuleCondition = 33, RuleNot = 34, RuleCondOp = 35, 
    RuleCondRHS = 36
  };

  explicit InoxisParser(antlr4::TokenStream *input);

  InoxisParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~InoxisParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class FuncDecsContext;
  class MainContext;
  class FuncDefsContext;
  class StatListContext;
  class FuncDecContext;
  class FuncDefContext;
  class FuncCallContext;
  class FuncCallFactorContext;
  class ParamContext;
  class VarContext;
  class VarDecContext;
  class ArgContext;
  class IndexContext;
  class StatementContext;
  class AssignContext;
  class PrintContext;
  class OutContext;
  class ReturnContext;
  class RetValContext;
  class MutContext;
  class PointRefContext;
  class SubscriptContext;
  class ArrayContext;
  class AllocateContext;
  class VarDecRHSContext;
  class AssignRHSContext;
  class RhsRefContext;
  class ExpressionContext;
  class WhileContext;
  class IfElseBlockContext;
  class ElifContext;
  class ElseContext;
  class ConditionContext;
  class NotContext;
  class CondOpContext;
  class CondRHSContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncDecsContext *funcDecs();
    MainContext *main();
    FuncDefsContext *funcDefs();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  FuncDecsContext : public antlr4::ParserRuleContext {
  public:
    FuncDecsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FuncDecContext *> funcDec();
    FuncDecContext* funcDec(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncDecsContext* funcDecs();

  class  MainContext : public antlr4::ParserRuleContext {
  public:
    MainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatListContext *statList();
    ReturnContext *return_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MainContext* main();

  class  FuncDefsContext : public antlr4::ParserRuleContext {
  public:
    FuncDefsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FuncDefContext *> funcDef();
    FuncDefContext* funcDef(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncDefsContext* funcDefs();

  class  StatListContext : public antlr4::ParserRuleContext {
  public:
    StatListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatListContext* statList();

  class  FuncDecContext : public antlr4::ParserRuleContext {
  public:
    FuncDecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PointRefContext *pointRef();
    antlr4::tree::TerminalNode *ID();
    ParamContext *param();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncDecContext* funcDec();

  class  FuncDefContext : public antlr4::ParserRuleContext {
  public:
    FuncDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PointRefContext *pointRef();
    antlr4::tree::TerminalNode *ID();
    ParamContext *param();
    StatListContext *statList();
    ReturnContext *return_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncDefContext* funcDef();

  class  FuncCallContext : public antlr4::ParserRuleContext {
  public:
    FuncCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    ArgContext *arg();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncCallContext* funcCall();

  class  FuncCallFactorContext : public antlr4::ParserRuleContext {
  public:
    FuncCallFactorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    ArgContext *arg();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncCallFactorContext* funcCallFactor();

  class  ParamContext : public antlr4::ParserRuleContext {
  public:
    ParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PointRefContext *pointRef();
    MutContext *mut();
    antlr4::tree::TerminalNode *ID();
    SubscriptContext *subscript();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParamContext* param();

  class  VarContext : public antlr4::ParserRuleContext {
  public:
    VarContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PointRefContext *pointRef();
    antlr4::tree::TerminalNode *ID();
    ArrayContext *array();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarContext* var();

  class  VarDecContext : public antlr4::ParserRuleContext {
  public:
    VarDecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PointRefContext *pointRef();
    MutContext *mut();
    antlr4::tree::TerminalNode *ID();
    ArrayContext *array();
    VarDecRHSContext *varDecRHS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDecContext* varDec();

  class  ArgContext : public antlr4::ParserRuleContext {
  public:
    ArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    VarContext *var();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgContext* arg();

  class  IndexContext : public antlr4::ParserRuleContext {
  public:
    IndexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *ID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IndexContext* index();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarDecContext *varDec();
    AssignContext *assign();
    WhileContext *while_();
    IfElseBlockContext *ifElseBlock();
    FuncCallContext *funcCall();
    PrintContext *print();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  AssignContext : public antlr4::ParserRuleContext {
  public:
    AssignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarContext *var();
    AssignRHSContext *assignRHS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignContext* assign();

  class  PrintContext : public antlr4::ParserRuleContext {
  public:
    PrintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OutContext *out();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    VarContext *var();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrintContext* print();

  class  OutContext : public antlr4::ParserRuleContext {
  public:
    OutContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING_LITERAL();
    antlr4::tree::TerminalNode* STRING_LITERAL(size_t i);
    std::vector<VarContext *> var();
    VarContext* var(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OutContext* out();

  class  ReturnContext : public antlr4::ParserRuleContext {
  public:
    ReturnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RetValContext *retVal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturnContext* return_();

  class  RetValContext : public antlr4::ParserRuleContext {
  public:
    RetValContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RetValContext* retVal();

  class  MutContext : public antlr4::ParserRuleContext {
  public:
    MutContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MutContext* mut();

  class  PointRefContext : public antlr4::ParserRuleContext {
  public:
    PointRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PointRefContext* pointRef();

  class  SubscriptContext : public antlr4::ParserRuleContext {
  public:
    SubscriptContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubscriptContext* subscript();

  class  ArrayContext : public antlr4::ParserRuleContext {
  public:
    ArrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IndexContext *index();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayContext* array();

  class  AllocateContext : public antlr4::ParserRuleContext {
  public:
    AllocateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArrayContext *array();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AllocateContext* allocate();

  class  VarDecRHSContext : public antlr4::ParserRuleContext {
  public:
    VarDecRHSContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignRHSContext *assignRHS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDecRHSContext* varDecRHS();

  class  AssignRHSContext : public antlr4::ParserRuleContext {
  public:
    AssignRHSContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RhsRefContext *rhsRef();
    ExpressionContext *expression();
    AllocateContext *allocate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignRHSContext* assignRHS();

  class  RhsRefContext : public antlr4::ParserRuleContext {
  public:
    RhsRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MutContext *mut();
    antlr4::tree::TerminalNode *ID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RhsRefContext* rhsRef();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  VarLiteralContext : public ExpressionContext {
  public:
    VarLiteralContext(ExpressionContext *ctx);

    VarContext *var();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddContext : public ExpressionContext {
  public:
    AddContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NumLiteralContext : public ExpressionContext {
  public:
    NumLiteralContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *INT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SubtractContext : public ExpressionContext {
  public:
    SubtractContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FuncCallExpContext : public ExpressionContext {
  public:
    FuncCallExpContext(ExpressionContext *ctx);

    FuncCallFactorContext *funcCallFactor();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  WhileContext : public antlr4::ParserRuleContext {
  public:
    WhileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionContext *condition();
    StatListContext *statList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhileContext* while_();

  class  IfElseBlockContext : public antlr4::ParserRuleContext {
  public:
    IfElseBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionContext *condition();
    StatListContext *statList();
    ElifContext *elif();
    ElseContext *else_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfElseBlockContext* ifElseBlock();

  class  ElifContext : public antlr4::ParserRuleContext {
  public:
    ElifContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConditionContext *> condition();
    ConditionContext* condition(size_t i);
    std::vector<StatListContext *> statList();
    StatListContext* statList(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElifContext* elif();

  class  ElseContext : public antlr4::ParserRuleContext {
  public:
    ElseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionContext *condition();
    StatListContext *statList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElseContext* else_();

  class  ConditionContext : public antlr4::ParserRuleContext {
  public:
    ConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NotContext *not_();
    antlr4::tree::TerminalNode *ID();
    CondOpContext *condOp();
    CondRHSContext *condRHS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionContext* condition();

  class  NotContext : public antlr4::ParserRuleContext {
  public:
    NotContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NotContext* not_();

  class  CondOpContext : public antlr4::ParserRuleContext {
  public:
    CondOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CondOpContext* condOp();

  class  CondRHSContext : public antlr4::ParserRuleContext {
  public:
    CondRHSContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *INT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CondRHSContext* condRHS();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

