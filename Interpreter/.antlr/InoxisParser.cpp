
// Generated from Inoxis.g4 by ANTLR 4.13.2


#include "InoxisListener.h"

#include "InoxisParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct InoxisParserStaticData final {
  InoxisParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  InoxisParserStaticData(const InoxisParserStaticData&) = delete;
  InoxisParserStaticData(InoxisParserStaticData&&) = delete;
  InoxisParserStaticData& operator=(const InoxisParserStaticData&) = delete;
  InoxisParserStaticData& operator=(InoxisParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag inoxisParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<InoxisParserStaticData> inoxisParserStaticData = nullptr;

void inoxisParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (inoxisParserStaticData != nullptr) {
    return;
  }
#else
  assert(inoxisParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<InoxisParserStaticData>(
    std::vector<std::string>{
      "program", "funcDecs", "main", "funcDefs", "statList", "funcDec", 
      "funcDef", "funcCall", "funcCallFactor", "param", "var", "varDec", 
      "arg", "index", "statement", "assign", "return", "retVal", "mut", 
      "pointRef", "subscript", "array", "allocate", "varDecRHS", "assignRHS", 
      "expression", "factor", "while", "ifElseBlock", "elif", "else", "condition", 
      "not", "condOp", "condRHS"
    },
    std::vector<std::string>{
      "", "'int'", "'main'", "'('", "')'", "'{'", "'}'", "';'", "'='", "'return'", 
      "'mut'", "'*'", "'&'", "'[]'", "'['", "']'", "'new'", "'+'", "'-'", 
      "'while'", "'if'", "'elif'", "'else'", "'!'", "'<'", "'>'", "'=='", 
      "'<='", "'>='", "'!='"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "WS", "ID", "COMMENT", 
      "INT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,33,281,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,1,0,1,
  	0,1,0,1,0,1,0,1,1,5,1,77,8,1,10,1,12,1,80,9,1,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,1,3,5,3,92,8,3,10,3,12,3,95,9,3,1,4,5,4,98,8,4,10,4,12,4,
  	101,9,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,
  	6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,1,12,1,12,3,12,153,8,12,1,13,1,13,1,14,1,14,1,14,1,14,1,14,3,14,162,
  	8,14,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,17,1,17,3,17,
  	176,8,17,1,18,3,18,179,8,18,1,19,3,19,182,8,19,1,20,3,20,185,8,20,1,21,
  	1,21,1,21,1,21,3,21,191,8,21,1,22,1,22,1,22,1,22,1,23,1,23,3,23,199,8,
  	23,1,24,1,24,3,24,203,8,24,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,
  	25,5,25,214,8,25,10,25,12,25,217,9,25,1,26,1,26,1,26,1,26,1,26,1,26,1,
  	26,3,26,226,8,26,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,28,1,28,1,
  	28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,1,29,1,29,1,
  	29,1,29,5,29,254,8,29,10,29,12,29,257,9,29,1,30,1,30,1,30,1,30,1,30,1,
  	30,1,30,1,30,3,30,267,8,30,1,31,1,31,1,31,1,31,1,31,1,32,3,32,275,8,32,
  	1,33,1,33,1,34,1,34,1,34,0,1,50,35,0,2,4,6,8,10,12,14,16,18,20,22,24,
  	26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,0,3,
  	2,0,31,31,33,33,1,0,11,12,1,0,24,29,269,0,70,1,0,0,0,2,78,1,0,0,0,4,81,
  	1,0,0,0,6,93,1,0,0,0,8,99,1,0,0,0,10,102,1,0,0,0,12,110,1,0,0,0,14,121,
  	1,0,0,0,16,127,1,0,0,0,18,132,1,0,0,0,20,138,1,0,0,0,22,142,1,0,0,0,24,
  	152,1,0,0,0,26,154,1,0,0,0,28,161,1,0,0,0,30,163,1,0,0,0,32,168,1,0,0,
  	0,34,175,1,0,0,0,36,178,1,0,0,0,38,181,1,0,0,0,40,184,1,0,0,0,42,190,
  	1,0,0,0,44,192,1,0,0,0,46,198,1,0,0,0,48,202,1,0,0,0,50,204,1,0,0,0,52,
  	225,1,0,0,0,54,227,1,0,0,0,56,235,1,0,0,0,58,255,1,0,0,0,60,266,1,0,0,
  	0,62,268,1,0,0,0,64,274,1,0,0,0,66,276,1,0,0,0,68,278,1,0,0,0,70,71,3,
  	2,1,0,71,72,3,4,2,0,72,73,3,6,3,0,73,74,5,0,0,1,74,1,1,0,0,0,75,77,3,
  	10,5,0,76,75,1,0,0,0,77,80,1,0,0,0,78,76,1,0,0,0,78,79,1,0,0,0,79,3,1,
  	0,0,0,80,78,1,0,0,0,81,82,5,1,0,0,82,83,5,2,0,0,83,84,5,3,0,0,84,85,5,
  	4,0,0,85,86,5,5,0,0,86,87,3,8,4,0,87,88,3,32,16,0,88,89,5,6,0,0,89,5,
  	1,0,0,0,90,92,3,12,6,0,91,90,1,0,0,0,92,95,1,0,0,0,93,91,1,0,0,0,93,94,
  	1,0,0,0,94,7,1,0,0,0,95,93,1,0,0,0,96,98,3,28,14,0,97,96,1,0,0,0,98,101,
  	1,0,0,0,99,97,1,0,0,0,99,100,1,0,0,0,100,9,1,0,0,0,101,99,1,0,0,0,102,
  	103,5,1,0,0,103,104,3,38,19,0,104,105,5,31,0,0,105,106,5,3,0,0,106,107,
  	3,18,9,0,107,108,5,4,0,0,108,109,5,7,0,0,109,11,1,0,0,0,110,111,5,1,0,
  	0,111,112,3,38,19,0,112,113,5,31,0,0,113,114,5,3,0,0,114,115,3,18,9,0,
  	115,116,5,4,0,0,116,117,5,5,0,0,117,118,3,8,4,0,118,119,3,32,16,0,119,
  	120,5,6,0,0,120,13,1,0,0,0,121,122,5,31,0,0,122,123,5,3,0,0,123,124,3,
  	24,12,0,124,125,5,4,0,0,125,126,5,7,0,0,126,15,1,0,0,0,127,128,5,31,0,
  	0,128,129,5,3,0,0,129,130,3,24,12,0,130,131,5,4,0,0,131,17,1,0,0,0,132,
  	133,5,1,0,0,133,134,3,38,19,0,134,135,3,36,18,0,135,136,5,31,0,0,136,
  	137,3,40,20,0,137,19,1,0,0,0,138,139,3,38,19,0,139,140,5,31,0,0,140,141,
  	3,42,21,0,141,21,1,0,0,0,142,143,5,1,0,0,143,144,3,38,19,0,144,145,3,
  	36,18,0,145,146,5,31,0,0,146,147,3,42,21,0,147,148,3,46,23,0,148,149,
  	5,7,0,0,149,23,1,0,0,0,150,153,5,33,0,0,151,153,3,20,10,0,152,150,1,0,
  	0,0,152,151,1,0,0,0,153,25,1,0,0,0,154,155,7,0,0,0,155,27,1,0,0,0,156,
  	162,3,22,11,0,157,162,3,30,15,0,158,162,3,54,27,0,159,162,3,56,28,0,160,
  	162,3,14,7,0,161,156,1,0,0,0,161,157,1,0,0,0,161,158,1,0,0,0,161,159,
  	1,0,0,0,161,160,1,0,0,0,162,29,1,0,0,0,163,164,3,20,10,0,164,165,5,8,
  	0,0,165,166,3,48,24,0,166,167,5,7,0,0,167,31,1,0,0,0,168,169,5,9,0,0,
  	169,170,3,34,17,0,170,171,5,7,0,0,171,33,1,0,0,0,172,176,5,33,0,0,173,
  	176,3,20,10,0,174,176,3,50,25,0,175,172,1,0,0,0,175,173,1,0,0,0,175,174,
  	1,0,0,0,176,35,1,0,0,0,177,179,5,10,0,0,178,177,1,0,0,0,178,179,1,0,0,
  	0,179,37,1,0,0,0,180,182,7,1,0,0,181,180,1,0,0,0,181,182,1,0,0,0,182,
  	39,1,0,0,0,183,185,5,13,0,0,184,183,1,0,0,0,184,185,1,0,0,0,185,41,1,
  	0,0,0,186,187,5,14,0,0,187,188,3,26,13,0,188,189,5,15,0,0,189,191,1,0,
  	0,0,190,186,1,0,0,0,190,191,1,0,0,0,191,43,1,0,0,0,192,193,5,16,0,0,193,
  	194,5,1,0,0,194,195,3,42,21,0,195,45,1,0,0,0,196,197,5,8,0,0,197,199,
  	3,48,24,0,198,196,1,0,0,0,198,199,1,0,0,0,199,47,1,0,0,0,200,203,3,50,
  	25,0,201,203,3,44,22,0,202,200,1,0,0,0,202,201,1,0,0,0,203,49,1,0,0,0,
  	204,205,6,25,-1,0,205,206,3,52,26,0,206,215,1,0,0,0,207,208,10,3,0,0,
  	208,209,5,17,0,0,209,214,3,50,25,4,210,211,10,2,0,0,211,212,5,18,0,0,
  	212,214,3,50,25,3,213,207,1,0,0,0,213,210,1,0,0,0,214,217,1,0,0,0,215,
  	213,1,0,0,0,215,216,1,0,0,0,216,51,1,0,0,0,217,215,1,0,0,0,218,226,3,
  	20,10,0,219,226,5,33,0,0,220,221,5,3,0,0,221,222,3,50,25,0,222,223,5,
  	4,0,0,223,226,1,0,0,0,224,226,3,16,8,0,225,218,1,0,0,0,225,219,1,0,0,
  	0,225,220,1,0,0,0,225,224,1,0,0,0,226,53,1,0,0,0,227,228,5,19,0,0,228,
  	229,5,3,0,0,229,230,3,62,31,0,230,231,5,4,0,0,231,232,5,5,0,0,232,233,
  	3,8,4,0,233,234,5,6,0,0,234,55,1,0,0,0,235,236,5,20,0,0,236,237,5,3,0,
  	0,237,238,3,62,31,0,238,239,5,4,0,0,239,240,5,5,0,0,240,241,3,8,4,0,241,
  	242,5,6,0,0,242,243,3,58,29,0,243,244,3,60,30,0,244,57,1,0,0,0,245,246,
  	5,21,0,0,246,247,5,3,0,0,247,248,3,62,31,0,248,249,5,4,0,0,249,250,5,
  	5,0,0,250,251,3,8,4,0,251,252,5,6,0,0,252,254,1,0,0,0,253,245,1,0,0,0,
  	254,257,1,0,0,0,255,253,1,0,0,0,255,256,1,0,0,0,256,59,1,0,0,0,257,255,
  	1,0,0,0,258,259,5,22,0,0,259,260,5,3,0,0,260,261,3,62,31,0,261,262,5,
  	4,0,0,262,263,5,5,0,0,263,264,3,8,4,0,264,265,5,6,0,0,265,267,1,0,0,0,
  	266,258,1,0,0,0,266,267,1,0,0,0,267,61,1,0,0,0,268,269,3,64,32,0,269,
  	270,5,31,0,0,270,271,3,66,33,0,271,272,3,68,34,0,272,63,1,0,0,0,273,275,
  	5,23,0,0,274,273,1,0,0,0,274,275,1,0,0,0,275,65,1,0,0,0,276,277,7,2,0,
  	0,277,67,1,0,0,0,278,279,7,0,0,0,279,69,1,0,0,0,18,78,93,99,152,161,175,
  	178,181,184,190,198,202,213,215,225,255,266,274
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  inoxisParserStaticData = std::move(staticData);
}

}

InoxisParser::InoxisParser(TokenStream *input) : InoxisParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

InoxisParser::InoxisParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  InoxisParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *inoxisParserStaticData->atn, inoxisParserStaticData->decisionToDFA, inoxisParserStaticData->sharedContextCache, options);
}

InoxisParser::~InoxisParser() {
  delete _interpreter;
}

const atn::ATN& InoxisParser::getATN() const {
  return *inoxisParserStaticData->atn;
}

std::string InoxisParser::getGrammarFileName() const {
  return "Inoxis.g4";
}

const std::vector<std::string>& InoxisParser::getRuleNames() const {
  return inoxisParserStaticData->ruleNames;
}

const dfa::Vocabulary& InoxisParser::getVocabulary() const {
  return inoxisParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView InoxisParser::getSerializedATN() const {
  return inoxisParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

InoxisParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::FuncDecsContext* InoxisParser::ProgramContext::funcDecs() {
  return getRuleContext<InoxisParser::FuncDecsContext>(0);
}

InoxisParser::MainContext* InoxisParser::ProgramContext::main() {
  return getRuleContext<InoxisParser::MainContext>(0);
}

InoxisParser::FuncDefsContext* InoxisParser::ProgramContext::funcDefs() {
  return getRuleContext<InoxisParser::FuncDefsContext>(0);
}

tree::TerminalNode* InoxisParser::ProgramContext::EOF() {
  return getToken(InoxisParser::EOF, 0);
}


size_t InoxisParser::ProgramContext::getRuleIndex() const {
  return InoxisParser::RuleProgram;
}

void InoxisParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void InoxisParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}

InoxisParser::ProgramContext* InoxisParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, InoxisParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(70);
    funcDecs();
    setState(71);
    main();
    setState(72);
    funcDefs();
    setState(73);
    match(InoxisParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDecsContext ------------------------------------------------------------------

InoxisParser::FuncDecsContext::FuncDecsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<InoxisParser::FuncDecContext *> InoxisParser::FuncDecsContext::funcDec() {
  return getRuleContexts<InoxisParser::FuncDecContext>();
}

InoxisParser::FuncDecContext* InoxisParser::FuncDecsContext::funcDec(size_t i) {
  return getRuleContext<InoxisParser::FuncDecContext>(i);
}


size_t InoxisParser::FuncDecsContext::getRuleIndex() const {
  return InoxisParser::RuleFuncDecs;
}

void InoxisParser::FuncDecsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDecs(this);
}

void InoxisParser::FuncDecsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDecs(this);
}

InoxisParser::FuncDecsContext* InoxisParser::funcDecs() {
  FuncDecsContext *_localctx = _tracker.createInstance<FuncDecsContext>(_ctx, getState());
  enterRule(_localctx, 2, InoxisParser::RuleFuncDecs);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(78);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(75);
        funcDec(); 
      }
      setState(80);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MainContext ------------------------------------------------------------------

InoxisParser::MainContext::MainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::StatListContext* InoxisParser::MainContext::statList() {
  return getRuleContext<InoxisParser::StatListContext>(0);
}

InoxisParser::ReturnContext* InoxisParser::MainContext::return_() {
  return getRuleContext<InoxisParser::ReturnContext>(0);
}


size_t InoxisParser::MainContext::getRuleIndex() const {
  return InoxisParser::RuleMain;
}

void InoxisParser::MainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMain(this);
}

void InoxisParser::MainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMain(this);
}

InoxisParser::MainContext* InoxisParser::main() {
  MainContext *_localctx = _tracker.createInstance<MainContext>(_ctx, getState());
  enterRule(_localctx, 4, InoxisParser::RuleMain);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    match(InoxisParser::T__0);
    setState(82);
    match(InoxisParser::T__1);
    setState(83);
    match(InoxisParser::T__2);
    setState(84);
    match(InoxisParser::T__3);
    setState(85);
    match(InoxisParser::T__4);
    setState(86);
    statList();
    setState(87);
    return_();
    setState(88);
    match(InoxisParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefsContext ------------------------------------------------------------------

InoxisParser::FuncDefsContext::FuncDefsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<InoxisParser::FuncDefContext *> InoxisParser::FuncDefsContext::funcDef() {
  return getRuleContexts<InoxisParser::FuncDefContext>();
}

InoxisParser::FuncDefContext* InoxisParser::FuncDefsContext::funcDef(size_t i) {
  return getRuleContext<InoxisParser::FuncDefContext>(i);
}


size_t InoxisParser::FuncDefsContext::getRuleIndex() const {
  return InoxisParser::RuleFuncDefs;
}

void InoxisParser::FuncDefsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDefs(this);
}

void InoxisParser::FuncDefsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDefs(this);
}

InoxisParser::FuncDefsContext* InoxisParser::funcDefs() {
  FuncDefsContext *_localctx = _tracker.createInstance<FuncDefsContext>(_ctx, getState());
  enterRule(_localctx, 6, InoxisParser::RuleFuncDefs);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(93);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == InoxisParser::T__0) {
      setState(90);
      funcDef();
      setState(95);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatListContext ------------------------------------------------------------------

InoxisParser::StatListContext::StatListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<InoxisParser::StatementContext *> InoxisParser::StatListContext::statement() {
  return getRuleContexts<InoxisParser::StatementContext>();
}

InoxisParser::StatementContext* InoxisParser::StatListContext::statement(size_t i) {
  return getRuleContext<InoxisParser::StatementContext>(i);
}


size_t InoxisParser::StatListContext::getRuleIndex() const {
  return InoxisParser::RuleStatList;
}

void InoxisParser::StatListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatList(this);
}

void InoxisParser::StatListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatList(this);
}

InoxisParser::StatListContext* InoxisParser::statList() {
  StatListContext *_localctx = _tracker.createInstance<StatListContext>(_ctx, getState());
  enterRule(_localctx, 8, InoxisParser::RuleStatList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(99);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2149062658) != 0)) {
      setState(96);
      statement();
      setState(101);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDecContext ------------------------------------------------------------------

InoxisParser::FuncDecContext::FuncDecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::PointRefContext* InoxisParser::FuncDecContext::pointRef() {
  return getRuleContext<InoxisParser::PointRefContext>(0);
}

tree::TerminalNode* InoxisParser::FuncDecContext::ID() {
  return getToken(InoxisParser::ID, 0);
}

InoxisParser::ParamContext* InoxisParser::FuncDecContext::param() {
  return getRuleContext<InoxisParser::ParamContext>(0);
}


size_t InoxisParser::FuncDecContext::getRuleIndex() const {
  return InoxisParser::RuleFuncDec;
}

void InoxisParser::FuncDecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDec(this);
}

void InoxisParser::FuncDecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDec(this);
}

InoxisParser::FuncDecContext* InoxisParser::funcDec() {
  FuncDecContext *_localctx = _tracker.createInstance<FuncDecContext>(_ctx, getState());
  enterRule(_localctx, 10, InoxisParser::RuleFuncDec);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(102);
    match(InoxisParser::T__0);
    setState(103);
    pointRef();
    setState(104);
    match(InoxisParser::ID);
    setState(105);
    match(InoxisParser::T__2);
    setState(106);
    param();
    setState(107);
    match(InoxisParser::T__3);
    setState(108);
    match(InoxisParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

InoxisParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::PointRefContext* InoxisParser::FuncDefContext::pointRef() {
  return getRuleContext<InoxisParser::PointRefContext>(0);
}

tree::TerminalNode* InoxisParser::FuncDefContext::ID() {
  return getToken(InoxisParser::ID, 0);
}

InoxisParser::ParamContext* InoxisParser::FuncDefContext::param() {
  return getRuleContext<InoxisParser::ParamContext>(0);
}

InoxisParser::StatListContext* InoxisParser::FuncDefContext::statList() {
  return getRuleContext<InoxisParser::StatListContext>(0);
}

InoxisParser::ReturnContext* InoxisParser::FuncDefContext::return_() {
  return getRuleContext<InoxisParser::ReturnContext>(0);
}


size_t InoxisParser::FuncDefContext::getRuleIndex() const {
  return InoxisParser::RuleFuncDef;
}

void InoxisParser::FuncDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDef(this);
}

void InoxisParser::FuncDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDef(this);
}

InoxisParser::FuncDefContext* InoxisParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 12, InoxisParser::RuleFuncDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    match(InoxisParser::T__0);
    setState(111);
    pointRef();
    setState(112);
    match(InoxisParser::ID);
    setState(113);
    match(InoxisParser::T__2);
    setState(114);
    param();
    setState(115);
    match(InoxisParser::T__3);
    setState(116);
    match(InoxisParser::T__4);
    setState(117);
    statList();
    setState(118);
    return_();
    setState(119);
    match(InoxisParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncCallContext ------------------------------------------------------------------

InoxisParser::FuncCallContext::FuncCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InoxisParser::FuncCallContext::ID() {
  return getToken(InoxisParser::ID, 0);
}

InoxisParser::ArgContext* InoxisParser::FuncCallContext::arg() {
  return getRuleContext<InoxisParser::ArgContext>(0);
}


size_t InoxisParser::FuncCallContext::getRuleIndex() const {
  return InoxisParser::RuleFuncCall;
}

void InoxisParser::FuncCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCall(this);
}

void InoxisParser::FuncCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCall(this);
}

InoxisParser::FuncCallContext* InoxisParser::funcCall() {
  FuncCallContext *_localctx = _tracker.createInstance<FuncCallContext>(_ctx, getState());
  enterRule(_localctx, 14, InoxisParser::RuleFuncCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    match(InoxisParser::ID);
    setState(122);
    match(InoxisParser::T__2);
    setState(123);
    arg();
    setState(124);
    match(InoxisParser::T__3);
    setState(125);
    match(InoxisParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncCallFactorContext ------------------------------------------------------------------

InoxisParser::FuncCallFactorContext::FuncCallFactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InoxisParser::FuncCallFactorContext::ID() {
  return getToken(InoxisParser::ID, 0);
}

InoxisParser::ArgContext* InoxisParser::FuncCallFactorContext::arg() {
  return getRuleContext<InoxisParser::ArgContext>(0);
}


size_t InoxisParser::FuncCallFactorContext::getRuleIndex() const {
  return InoxisParser::RuleFuncCallFactor;
}

void InoxisParser::FuncCallFactorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCallFactor(this);
}

void InoxisParser::FuncCallFactorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCallFactor(this);
}

InoxisParser::FuncCallFactorContext* InoxisParser::funcCallFactor() {
  FuncCallFactorContext *_localctx = _tracker.createInstance<FuncCallFactorContext>(_ctx, getState());
  enterRule(_localctx, 16, InoxisParser::RuleFuncCallFactor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(127);
    match(InoxisParser::ID);
    setState(128);
    match(InoxisParser::T__2);
    setState(129);
    arg();
    setState(130);
    match(InoxisParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamContext ------------------------------------------------------------------

InoxisParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::PointRefContext* InoxisParser::ParamContext::pointRef() {
  return getRuleContext<InoxisParser::PointRefContext>(0);
}

InoxisParser::MutContext* InoxisParser::ParamContext::mut() {
  return getRuleContext<InoxisParser::MutContext>(0);
}

tree::TerminalNode* InoxisParser::ParamContext::ID() {
  return getToken(InoxisParser::ID, 0);
}

InoxisParser::SubscriptContext* InoxisParser::ParamContext::subscript() {
  return getRuleContext<InoxisParser::SubscriptContext>(0);
}


size_t InoxisParser::ParamContext::getRuleIndex() const {
  return InoxisParser::RuleParam;
}

void InoxisParser::ParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam(this);
}

void InoxisParser::ParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam(this);
}

InoxisParser::ParamContext* InoxisParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 18, InoxisParser::RuleParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(132);
    match(InoxisParser::T__0);
    setState(133);
    pointRef();
    setState(134);
    mut();
    setState(135);
    match(InoxisParser::ID);
    setState(136);
    subscript();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarContext ------------------------------------------------------------------

InoxisParser::VarContext::VarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::PointRefContext* InoxisParser::VarContext::pointRef() {
  return getRuleContext<InoxisParser::PointRefContext>(0);
}

tree::TerminalNode* InoxisParser::VarContext::ID() {
  return getToken(InoxisParser::ID, 0);
}

InoxisParser::ArrayContext* InoxisParser::VarContext::array() {
  return getRuleContext<InoxisParser::ArrayContext>(0);
}


size_t InoxisParser::VarContext::getRuleIndex() const {
  return InoxisParser::RuleVar;
}

void InoxisParser::VarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar(this);
}

void InoxisParser::VarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar(this);
}

InoxisParser::VarContext* InoxisParser::var() {
  VarContext *_localctx = _tracker.createInstance<VarContext>(_ctx, getState());
  enterRule(_localctx, 20, InoxisParser::RuleVar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(138);
    pointRef();
    setState(139);
    match(InoxisParser::ID);
    setState(140);
    array();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDecContext ------------------------------------------------------------------

InoxisParser::VarDecContext::VarDecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::PointRefContext* InoxisParser::VarDecContext::pointRef() {
  return getRuleContext<InoxisParser::PointRefContext>(0);
}

InoxisParser::MutContext* InoxisParser::VarDecContext::mut() {
  return getRuleContext<InoxisParser::MutContext>(0);
}

tree::TerminalNode* InoxisParser::VarDecContext::ID() {
  return getToken(InoxisParser::ID, 0);
}

InoxisParser::ArrayContext* InoxisParser::VarDecContext::array() {
  return getRuleContext<InoxisParser::ArrayContext>(0);
}

InoxisParser::VarDecRHSContext* InoxisParser::VarDecContext::varDecRHS() {
  return getRuleContext<InoxisParser::VarDecRHSContext>(0);
}


size_t InoxisParser::VarDecContext::getRuleIndex() const {
  return InoxisParser::RuleVarDec;
}

void InoxisParser::VarDecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDec(this);
}

void InoxisParser::VarDecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDec(this);
}

InoxisParser::VarDecContext* InoxisParser::varDec() {
  VarDecContext *_localctx = _tracker.createInstance<VarDecContext>(_ctx, getState());
  enterRule(_localctx, 22, InoxisParser::RuleVarDec);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(142);
    match(InoxisParser::T__0);
    setState(143);
    pointRef();
    setState(144);
    mut();
    setState(145);
    match(InoxisParser::ID);
    setState(146);
    array();
    setState(147);
    varDecRHS();
    setState(148);
    match(InoxisParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgContext ------------------------------------------------------------------

InoxisParser::ArgContext::ArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InoxisParser::ArgContext::INT() {
  return getToken(InoxisParser::INT, 0);
}

InoxisParser::VarContext* InoxisParser::ArgContext::var() {
  return getRuleContext<InoxisParser::VarContext>(0);
}


size_t InoxisParser::ArgContext::getRuleIndex() const {
  return InoxisParser::RuleArg;
}

void InoxisParser::ArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArg(this);
}

void InoxisParser::ArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArg(this);
}

InoxisParser::ArgContext* InoxisParser::arg() {
  ArgContext *_localctx = _tracker.createInstance<ArgContext>(_ctx, getState());
  enterRule(_localctx, 24, InoxisParser::RuleArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(152);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case InoxisParser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(150);
        match(InoxisParser::INT);
        break;
      }

      case InoxisParser::T__10:
      case InoxisParser::T__11:
      case InoxisParser::ID: {
        enterOuterAlt(_localctx, 2);
        setState(151);
        var();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IndexContext ------------------------------------------------------------------

InoxisParser::IndexContext::IndexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InoxisParser::IndexContext::INT() {
  return getToken(InoxisParser::INT, 0);
}

tree::TerminalNode* InoxisParser::IndexContext::ID() {
  return getToken(InoxisParser::ID, 0);
}


size_t InoxisParser::IndexContext::getRuleIndex() const {
  return InoxisParser::RuleIndex;
}

void InoxisParser::IndexContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIndex(this);
}

void InoxisParser::IndexContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIndex(this);
}

InoxisParser::IndexContext* InoxisParser::index() {
  IndexContext *_localctx = _tracker.createInstance<IndexContext>(_ctx, getState());
  enterRule(_localctx, 26, InoxisParser::RuleIndex);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(154);
    _la = _input->LA(1);
    if (!(_la == InoxisParser::ID

    || _la == InoxisParser::INT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

InoxisParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::VarDecContext* InoxisParser::StatementContext::varDec() {
  return getRuleContext<InoxisParser::VarDecContext>(0);
}

InoxisParser::AssignContext* InoxisParser::StatementContext::assign() {
  return getRuleContext<InoxisParser::AssignContext>(0);
}

InoxisParser::WhileContext* InoxisParser::StatementContext::while_() {
  return getRuleContext<InoxisParser::WhileContext>(0);
}

InoxisParser::IfElseBlockContext* InoxisParser::StatementContext::ifElseBlock() {
  return getRuleContext<InoxisParser::IfElseBlockContext>(0);
}

InoxisParser::FuncCallContext* InoxisParser::StatementContext::funcCall() {
  return getRuleContext<InoxisParser::FuncCallContext>(0);
}


size_t InoxisParser::StatementContext::getRuleIndex() const {
  return InoxisParser::RuleStatement;
}

void InoxisParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void InoxisParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

InoxisParser::StatementContext* InoxisParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 28, InoxisParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(161);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(156);
      varDec();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(157);
      assign();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(158);
      while_();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(159);
      ifElseBlock();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(160);
      funcCall();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignContext ------------------------------------------------------------------

InoxisParser::AssignContext::AssignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::VarContext* InoxisParser::AssignContext::var() {
  return getRuleContext<InoxisParser::VarContext>(0);
}

InoxisParser::AssignRHSContext* InoxisParser::AssignContext::assignRHS() {
  return getRuleContext<InoxisParser::AssignRHSContext>(0);
}


size_t InoxisParser::AssignContext::getRuleIndex() const {
  return InoxisParser::RuleAssign;
}

void InoxisParser::AssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssign(this);
}

void InoxisParser::AssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssign(this);
}

InoxisParser::AssignContext* InoxisParser::assign() {
  AssignContext *_localctx = _tracker.createInstance<AssignContext>(_ctx, getState());
  enterRule(_localctx, 30, InoxisParser::RuleAssign);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(163);
    var();
    setState(164);
    match(InoxisParser::T__7);
    setState(165);
    assignRHS();
    setState(166);
    match(InoxisParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnContext ------------------------------------------------------------------

InoxisParser::ReturnContext::ReturnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::RetValContext* InoxisParser::ReturnContext::retVal() {
  return getRuleContext<InoxisParser::RetValContext>(0);
}


size_t InoxisParser::ReturnContext::getRuleIndex() const {
  return InoxisParser::RuleReturn;
}

void InoxisParser::ReturnContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturn(this);
}

void InoxisParser::ReturnContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturn(this);
}

InoxisParser::ReturnContext* InoxisParser::return_() {
  ReturnContext *_localctx = _tracker.createInstance<ReturnContext>(_ctx, getState());
  enterRule(_localctx, 32, InoxisParser::RuleReturn);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(168);
    match(InoxisParser::T__8);
    setState(169);
    retVal();
    setState(170);
    match(InoxisParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RetValContext ------------------------------------------------------------------

InoxisParser::RetValContext::RetValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InoxisParser::RetValContext::INT() {
  return getToken(InoxisParser::INT, 0);
}

InoxisParser::VarContext* InoxisParser::RetValContext::var() {
  return getRuleContext<InoxisParser::VarContext>(0);
}

InoxisParser::ExpressionContext* InoxisParser::RetValContext::expression() {
  return getRuleContext<InoxisParser::ExpressionContext>(0);
}


size_t InoxisParser::RetValContext::getRuleIndex() const {
  return InoxisParser::RuleRetVal;
}

void InoxisParser::RetValContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRetVal(this);
}

void InoxisParser::RetValContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRetVal(this);
}

InoxisParser::RetValContext* InoxisParser::retVal() {
  RetValContext *_localctx = _tracker.createInstance<RetValContext>(_ctx, getState());
  enterRule(_localctx, 34, InoxisParser::RuleRetVal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(175);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(172);
      match(InoxisParser::INT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(173);
      var();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(174);
      expression(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MutContext ------------------------------------------------------------------

InoxisParser::MutContext::MutContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t InoxisParser::MutContext::getRuleIndex() const {
  return InoxisParser::RuleMut;
}

void InoxisParser::MutContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMut(this);
}

void InoxisParser::MutContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMut(this);
}

InoxisParser::MutContext* InoxisParser::mut() {
  MutContext *_localctx = _tracker.createInstance<MutContext>(_ctx, getState());
  enterRule(_localctx, 36, InoxisParser::RuleMut);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(178);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InoxisParser::T__9) {
      setState(177);
      match(InoxisParser::T__9);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PointRefContext ------------------------------------------------------------------

InoxisParser::PointRefContext::PointRefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t InoxisParser::PointRefContext::getRuleIndex() const {
  return InoxisParser::RulePointRef;
}

void InoxisParser::PointRefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPointRef(this);
}

void InoxisParser::PointRefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPointRef(this);
}

InoxisParser::PointRefContext* InoxisParser::pointRef() {
  PointRefContext *_localctx = _tracker.createInstance<PointRefContext>(_ctx, getState());
  enterRule(_localctx, 38, InoxisParser::RulePointRef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(181);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InoxisParser::T__10

    || _la == InoxisParser::T__11) {
      setState(180);
      _la = _input->LA(1);
      if (!(_la == InoxisParser::T__10

      || _la == InoxisParser::T__11)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SubscriptContext ------------------------------------------------------------------

InoxisParser::SubscriptContext::SubscriptContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t InoxisParser::SubscriptContext::getRuleIndex() const {
  return InoxisParser::RuleSubscript;
}

void InoxisParser::SubscriptContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubscript(this);
}

void InoxisParser::SubscriptContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubscript(this);
}

InoxisParser::SubscriptContext* InoxisParser::subscript() {
  SubscriptContext *_localctx = _tracker.createInstance<SubscriptContext>(_ctx, getState());
  enterRule(_localctx, 40, InoxisParser::RuleSubscript);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InoxisParser::T__12) {
      setState(183);
      match(InoxisParser::T__12);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayContext ------------------------------------------------------------------

InoxisParser::ArrayContext::ArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::IndexContext* InoxisParser::ArrayContext::index() {
  return getRuleContext<InoxisParser::IndexContext>(0);
}


size_t InoxisParser::ArrayContext::getRuleIndex() const {
  return InoxisParser::RuleArray;
}

void InoxisParser::ArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArray(this);
}

void InoxisParser::ArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArray(this);
}

InoxisParser::ArrayContext* InoxisParser::array() {
  ArrayContext *_localctx = _tracker.createInstance<ArrayContext>(_ctx, getState());
  enterRule(_localctx, 42, InoxisParser::RuleArray);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(186);
      match(InoxisParser::T__13);
      setState(187);
      index();
      setState(188);
      match(InoxisParser::T__14);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AllocateContext ------------------------------------------------------------------

InoxisParser::AllocateContext::AllocateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::ArrayContext* InoxisParser::AllocateContext::array() {
  return getRuleContext<InoxisParser::ArrayContext>(0);
}


size_t InoxisParser::AllocateContext::getRuleIndex() const {
  return InoxisParser::RuleAllocate;
}

void InoxisParser::AllocateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAllocate(this);
}

void InoxisParser::AllocateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAllocate(this);
}

InoxisParser::AllocateContext* InoxisParser::allocate() {
  AllocateContext *_localctx = _tracker.createInstance<AllocateContext>(_ctx, getState());
  enterRule(_localctx, 44, InoxisParser::RuleAllocate);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(192);
    match(InoxisParser::T__15);
    setState(193);
    match(InoxisParser::T__0);
    setState(194);
    array();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDecRHSContext ------------------------------------------------------------------

InoxisParser::VarDecRHSContext::VarDecRHSContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::AssignRHSContext* InoxisParser::VarDecRHSContext::assignRHS() {
  return getRuleContext<InoxisParser::AssignRHSContext>(0);
}


size_t InoxisParser::VarDecRHSContext::getRuleIndex() const {
  return InoxisParser::RuleVarDecRHS;
}

void InoxisParser::VarDecRHSContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDecRHS(this);
}

void InoxisParser::VarDecRHSContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDecRHS(this);
}

InoxisParser::VarDecRHSContext* InoxisParser::varDecRHS() {
  VarDecRHSContext *_localctx = _tracker.createInstance<VarDecRHSContext>(_ctx, getState());
  enterRule(_localctx, 46, InoxisParser::RuleVarDecRHS);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(198);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InoxisParser::T__7) {
      setState(196);
      match(InoxisParser::T__7);
      setState(197);
      assignRHS();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignRHSContext ------------------------------------------------------------------

InoxisParser::AssignRHSContext::AssignRHSContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::ExpressionContext* InoxisParser::AssignRHSContext::expression() {
  return getRuleContext<InoxisParser::ExpressionContext>(0);
}

InoxisParser::AllocateContext* InoxisParser::AssignRHSContext::allocate() {
  return getRuleContext<InoxisParser::AllocateContext>(0);
}


size_t InoxisParser::AssignRHSContext::getRuleIndex() const {
  return InoxisParser::RuleAssignRHS;
}

void InoxisParser::AssignRHSContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignRHS(this);
}

void InoxisParser::AssignRHSContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignRHS(this);
}

InoxisParser::AssignRHSContext* InoxisParser::assignRHS() {
  AssignRHSContext *_localctx = _tracker.createInstance<AssignRHSContext>(_ctx, getState());
  enterRule(_localctx, 48, InoxisParser::RuleAssignRHS);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(202);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case InoxisParser::T__2:
      case InoxisParser::T__10:
      case InoxisParser::T__11:
      case InoxisParser::ID:
      case InoxisParser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(200);
        expression(0);
        break;
      }

      case InoxisParser::T__15: {
        enterOuterAlt(_localctx, 2);
        setState(201);
        allocate();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

InoxisParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::FactorContext* InoxisParser::ExpressionContext::factor() {
  return getRuleContext<InoxisParser::FactorContext>(0);
}

std::vector<InoxisParser::ExpressionContext *> InoxisParser::ExpressionContext::expression() {
  return getRuleContexts<InoxisParser::ExpressionContext>();
}

InoxisParser::ExpressionContext* InoxisParser::ExpressionContext::expression(size_t i) {
  return getRuleContext<InoxisParser::ExpressionContext>(i);
}


size_t InoxisParser::ExpressionContext::getRuleIndex() const {
  return InoxisParser::RuleExpression;
}

void InoxisParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void InoxisParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


InoxisParser::ExpressionContext* InoxisParser::expression() {
   return expression(0);
}

InoxisParser::ExpressionContext* InoxisParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  InoxisParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  InoxisParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, InoxisParser::RuleExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(205);
    factor();
    _ctx->stop = _input->LT(-1);
    setState(215);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(213);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(207);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(208);
          match(InoxisParser::T__16);
          setState(209);
          expression(4);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(210);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(211);
          match(InoxisParser::T__17);
          setState(212);
          expression(3);
          break;
        }

        default:
          break;
        } 
      }
      setState(217);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- FactorContext ------------------------------------------------------------------

InoxisParser::FactorContext::FactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::VarContext* InoxisParser::FactorContext::var() {
  return getRuleContext<InoxisParser::VarContext>(0);
}

tree::TerminalNode* InoxisParser::FactorContext::INT() {
  return getToken(InoxisParser::INT, 0);
}

InoxisParser::ExpressionContext* InoxisParser::FactorContext::expression() {
  return getRuleContext<InoxisParser::ExpressionContext>(0);
}

InoxisParser::FuncCallFactorContext* InoxisParser::FactorContext::funcCallFactor() {
  return getRuleContext<InoxisParser::FuncCallFactorContext>(0);
}


size_t InoxisParser::FactorContext::getRuleIndex() const {
  return InoxisParser::RuleFactor;
}

void InoxisParser::FactorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFactor(this);
}

void InoxisParser::FactorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFactor(this);
}

InoxisParser::FactorContext* InoxisParser::factor() {
  FactorContext *_localctx = _tracker.createInstance<FactorContext>(_ctx, getState());
  enterRule(_localctx, 52, InoxisParser::RuleFactor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(225);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(218);
      var();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(219);
      match(InoxisParser::INT);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(220);
      match(InoxisParser::T__2);
      setState(221);
      expression(0);
      setState(222);
      match(InoxisParser::T__3);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(224);
      funcCallFactor();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileContext ------------------------------------------------------------------

InoxisParser::WhileContext::WhileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::ConditionContext* InoxisParser::WhileContext::condition() {
  return getRuleContext<InoxisParser::ConditionContext>(0);
}

InoxisParser::StatListContext* InoxisParser::WhileContext::statList() {
  return getRuleContext<InoxisParser::StatListContext>(0);
}


size_t InoxisParser::WhileContext::getRuleIndex() const {
  return InoxisParser::RuleWhile;
}

void InoxisParser::WhileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhile(this);
}

void InoxisParser::WhileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhile(this);
}

InoxisParser::WhileContext* InoxisParser::while_() {
  WhileContext *_localctx = _tracker.createInstance<WhileContext>(_ctx, getState());
  enterRule(_localctx, 54, InoxisParser::RuleWhile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(227);
    match(InoxisParser::T__18);
    setState(228);
    match(InoxisParser::T__2);
    setState(229);
    condition();
    setState(230);
    match(InoxisParser::T__3);
    setState(231);
    match(InoxisParser::T__4);
    setState(232);
    statList();
    setState(233);
    match(InoxisParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfElseBlockContext ------------------------------------------------------------------

InoxisParser::IfElseBlockContext::IfElseBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::ConditionContext* InoxisParser::IfElseBlockContext::condition() {
  return getRuleContext<InoxisParser::ConditionContext>(0);
}

InoxisParser::StatListContext* InoxisParser::IfElseBlockContext::statList() {
  return getRuleContext<InoxisParser::StatListContext>(0);
}

InoxisParser::ElifContext* InoxisParser::IfElseBlockContext::elif() {
  return getRuleContext<InoxisParser::ElifContext>(0);
}

InoxisParser::ElseContext* InoxisParser::IfElseBlockContext::else_() {
  return getRuleContext<InoxisParser::ElseContext>(0);
}


size_t InoxisParser::IfElseBlockContext::getRuleIndex() const {
  return InoxisParser::RuleIfElseBlock;
}

void InoxisParser::IfElseBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfElseBlock(this);
}

void InoxisParser::IfElseBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfElseBlock(this);
}

InoxisParser::IfElseBlockContext* InoxisParser::ifElseBlock() {
  IfElseBlockContext *_localctx = _tracker.createInstance<IfElseBlockContext>(_ctx, getState());
  enterRule(_localctx, 56, InoxisParser::RuleIfElseBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(235);
    match(InoxisParser::T__19);
    setState(236);
    match(InoxisParser::T__2);
    setState(237);
    condition();
    setState(238);
    match(InoxisParser::T__3);
    setState(239);
    match(InoxisParser::T__4);
    setState(240);
    statList();
    setState(241);
    match(InoxisParser::T__5);
    setState(242);
    elif();
    setState(243);
    else_();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElifContext ------------------------------------------------------------------

InoxisParser::ElifContext::ElifContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<InoxisParser::ConditionContext *> InoxisParser::ElifContext::condition() {
  return getRuleContexts<InoxisParser::ConditionContext>();
}

InoxisParser::ConditionContext* InoxisParser::ElifContext::condition(size_t i) {
  return getRuleContext<InoxisParser::ConditionContext>(i);
}

std::vector<InoxisParser::StatListContext *> InoxisParser::ElifContext::statList() {
  return getRuleContexts<InoxisParser::StatListContext>();
}

InoxisParser::StatListContext* InoxisParser::ElifContext::statList(size_t i) {
  return getRuleContext<InoxisParser::StatListContext>(i);
}


size_t InoxisParser::ElifContext::getRuleIndex() const {
  return InoxisParser::RuleElif;
}

void InoxisParser::ElifContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElif(this);
}

void InoxisParser::ElifContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElif(this);
}

InoxisParser::ElifContext* InoxisParser::elif() {
  ElifContext *_localctx = _tracker.createInstance<ElifContext>(_ctx, getState());
  enterRule(_localctx, 58, InoxisParser::RuleElif);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(255);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == InoxisParser::T__20) {
      setState(245);
      match(InoxisParser::T__20);
      setState(246);
      match(InoxisParser::T__2);
      setState(247);
      condition();
      setState(248);
      match(InoxisParser::T__3);
      setState(249);
      match(InoxisParser::T__4);
      setState(250);
      statList();
      setState(251);
      match(InoxisParser::T__5);
      setState(257);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseContext ------------------------------------------------------------------

InoxisParser::ElseContext::ElseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::ConditionContext* InoxisParser::ElseContext::condition() {
  return getRuleContext<InoxisParser::ConditionContext>(0);
}

InoxisParser::StatListContext* InoxisParser::ElseContext::statList() {
  return getRuleContext<InoxisParser::StatListContext>(0);
}


size_t InoxisParser::ElseContext::getRuleIndex() const {
  return InoxisParser::RuleElse;
}

void InoxisParser::ElseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElse(this);
}

void InoxisParser::ElseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElse(this);
}

InoxisParser::ElseContext* InoxisParser::else_() {
  ElseContext *_localctx = _tracker.createInstance<ElseContext>(_ctx, getState());
  enterRule(_localctx, 60, InoxisParser::RuleElse);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(266);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InoxisParser::T__21) {
      setState(258);
      match(InoxisParser::T__21);
      setState(259);
      match(InoxisParser::T__2);
      setState(260);
      condition();
      setState(261);
      match(InoxisParser::T__3);
      setState(262);
      match(InoxisParser::T__4);
      setState(263);
      statList();
      setState(264);
      match(InoxisParser::T__5);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

InoxisParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InoxisParser::NotContext* InoxisParser::ConditionContext::not_() {
  return getRuleContext<InoxisParser::NotContext>(0);
}

tree::TerminalNode* InoxisParser::ConditionContext::ID() {
  return getToken(InoxisParser::ID, 0);
}

InoxisParser::CondOpContext* InoxisParser::ConditionContext::condOp() {
  return getRuleContext<InoxisParser::CondOpContext>(0);
}

InoxisParser::CondRHSContext* InoxisParser::ConditionContext::condRHS() {
  return getRuleContext<InoxisParser::CondRHSContext>(0);
}


size_t InoxisParser::ConditionContext::getRuleIndex() const {
  return InoxisParser::RuleCondition;
}

void InoxisParser::ConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondition(this);
}

void InoxisParser::ConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondition(this);
}

InoxisParser::ConditionContext* InoxisParser::condition() {
  ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, getState());
  enterRule(_localctx, 62, InoxisParser::RuleCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(268);
    not_();
    setState(269);
    match(InoxisParser::ID);
    setState(270);
    condOp();
    setState(271);
    condRHS();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NotContext ------------------------------------------------------------------

InoxisParser::NotContext::NotContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t InoxisParser::NotContext::getRuleIndex() const {
  return InoxisParser::RuleNot;
}

void InoxisParser::NotContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNot(this);
}

void InoxisParser::NotContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNot(this);
}

InoxisParser::NotContext* InoxisParser::not_() {
  NotContext *_localctx = _tracker.createInstance<NotContext>(_ctx, getState());
  enterRule(_localctx, 64, InoxisParser::RuleNot);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(274);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InoxisParser::T__22) {
      setState(273);
      match(InoxisParser::T__22);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondOpContext ------------------------------------------------------------------

InoxisParser::CondOpContext::CondOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t InoxisParser::CondOpContext::getRuleIndex() const {
  return InoxisParser::RuleCondOp;
}

void InoxisParser::CondOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondOp(this);
}

void InoxisParser::CondOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondOp(this);
}

InoxisParser::CondOpContext* InoxisParser::condOp() {
  CondOpContext *_localctx = _tracker.createInstance<CondOpContext>(_ctx, getState());
  enterRule(_localctx, 66, InoxisParser::RuleCondOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(276);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1056964608) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondRHSContext ------------------------------------------------------------------

InoxisParser::CondRHSContext::CondRHSContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InoxisParser::CondRHSContext::ID() {
  return getToken(InoxisParser::ID, 0);
}

tree::TerminalNode* InoxisParser::CondRHSContext::INT() {
  return getToken(InoxisParser::INT, 0);
}


size_t InoxisParser::CondRHSContext::getRuleIndex() const {
  return InoxisParser::RuleCondRHS;
}

void InoxisParser::CondRHSContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondRHS(this);
}

void InoxisParser::CondRHSContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InoxisListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondRHS(this);
}

InoxisParser::CondRHSContext* InoxisParser::condRHS() {
  CondRHSContext *_localctx = _tracker.createInstance<CondRHSContext>(_ctx, getState());
  enterRule(_localctx, 68, InoxisParser::RuleCondRHS);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(278);
    _la = _input->LA(1);
    if (!(_la == InoxisParser::ID

    || _la == InoxisParser::INT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool InoxisParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 25: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool InoxisParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

void InoxisParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  inoxisParserInitialize();
#else
  ::antlr4::internal::call_once(inoxisParserOnceFlag, inoxisParserInitialize);
#endif
}
