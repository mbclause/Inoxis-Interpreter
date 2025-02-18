
// Generated from Inoxis.g4 by ANTLR 4.13.2


#include "InoxisLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct InoxisLexerStaticData final {
  InoxisLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  InoxisLexerStaticData(const InoxisLexerStaticData&) = delete;
  InoxisLexerStaticData(InoxisLexerStaticData&&) = delete;
  InoxisLexerStaticData& operator=(const InoxisLexerStaticData&) = delete;
  InoxisLexerStaticData& operator=(InoxisLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag inoxislexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<InoxisLexerStaticData> inoxislexerLexerStaticData = nullptr;

void inoxislexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (inoxislexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(inoxislexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<InoxisLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
      "T__17", "T__18", "T__19", "T__20", "T__21", "T__22", "T__23", "T__24", 
      "T__25", "T__26", "T__27", "T__28", "WS", "ID", "COMMENT", "INT", 
      "SIGN"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,33,190,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,1,0,1,0,1,0,1,
  	0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,
  	1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,10,1,10,1,11,1,11,1,12,
  	1,12,1,12,1,13,1,13,1,14,1,14,1,15,1,15,1,15,1,15,1,16,1,16,1,17,1,17,
  	1,18,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,
  	1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,23,1,23,1,24,1,24,1,25,1,25,1,25,
  	1,26,1,26,1,26,1,27,1,27,1,27,1,28,1,28,1,28,1,29,1,29,1,29,1,29,1,30,
  	1,30,5,30,164,8,30,10,30,12,30,167,9,30,1,31,1,31,1,31,1,31,5,31,173,
  	8,31,10,31,12,31,176,9,31,1,31,1,31,1,31,1,31,1,32,1,32,4,32,184,8,32,
  	11,32,12,32,185,1,33,3,33,189,8,33,1,174,0,34,1,1,3,2,5,3,7,4,9,5,11,
  	6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,
  	37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,
  	30,61,31,63,32,65,33,67,0,1,0,4,3,0,9,10,13,13,32,32,2,0,65,90,97,122,
  	4,0,48,57,65,90,95,95,97,122,1,0,48,57,192,0,1,1,0,0,0,0,3,1,0,0,0,0,
  	5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,
  	0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,
  	0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,
  	1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,
  	0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,
  	0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,1,69,1,0,0,0,3,73,
  	1,0,0,0,5,78,1,0,0,0,7,80,1,0,0,0,9,82,1,0,0,0,11,84,1,0,0,0,13,86,1,
  	0,0,0,15,88,1,0,0,0,17,90,1,0,0,0,19,97,1,0,0,0,21,101,1,0,0,0,23,103,
  	1,0,0,0,25,105,1,0,0,0,27,108,1,0,0,0,29,110,1,0,0,0,31,112,1,0,0,0,33,
  	116,1,0,0,0,35,118,1,0,0,0,37,120,1,0,0,0,39,126,1,0,0,0,41,129,1,0,0,
  	0,43,134,1,0,0,0,45,139,1,0,0,0,47,141,1,0,0,0,49,143,1,0,0,0,51,145,
  	1,0,0,0,53,148,1,0,0,0,55,151,1,0,0,0,57,154,1,0,0,0,59,157,1,0,0,0,61,
  	161,1,0,0,0,63,168,1,0,0,0,65,181,1,0,0,0,67,188,1,0,0,0,69,70,5,105,
  	0,0,70,71,5,110,0,0,71,72,5,116,0,0,72,2,1,0,0,0,73,74,5,109,0,0,74,75,
  	5,97,0,0,75,76,5,105,0,0,76,77,5,110,0,0,77,4,1,0,0,0,78,79,5,40,0,0,
  	79,6,1,0,0,0,80,81,5,41,0,0,81,8,1,0,0,0,82,83,5,123,0,0,83,10,1,0,0,
  	0,84,85,5,125,0,0,85,12,1,0,0,0,86,87,5,59,0,0,87,14,1,0,0,0,88,89,5,
  	61,0,0,89,16,1,0,0,0,90,91,5,114,0,0,91,92,5,101,0,0,92,93,5,116,0,0,
  	93,94,5,117,0,0,94,95,5,114,0,0,95,96,5,110,0,0,96,18,1,0,0,0,97,98,5,
  	109,0,0,98,99,5,117,0,0,99,100,5,116,0,0,100,20,1,0,0,0,101,102,5,42,
  	0,0,102,22,1,0,0,0,103,104,5,38,0,0,104,24,1,0,0,0,105,106,5,91,0,0,106,
  	107,5,93,0,0,107,26,1,0,0,0,108,109,5,91,0,0,109,28,1,0,0,0,110,111,5,
  	93,0,0,111,30,1,0,0,0,112,113,5,110,0,0,113,114,5,101,0,0,114,115,5,119,
  	0,0,115,32,1,0,0,0,116,117,5,43,0,0,117,34,1,0,0,0,118,119,5,45,0,0,119,
  	36,1,0,0,0,120,121,5,119,0,0,121,122,5,104,0,0,122,123,5,105,0,0,123,
  	124,5,108,0,0,124,125,5,101,0,0,125,38,1,0,0,0,126,127,5,105,0,0,127,
  	128,5,102,0,0,128,40,1,0,0,0,129,130,5,101,0,0,130,131,5,108,0,0,131,
  	132,5,105,0,0,132,133,5,102,0,0,133,42,1,0,0,0,134,135,5,101,0,0,135,
  	136,5,108,0,0,136,137,5,115,0,0,137,138,5,101,0,0,138,44,1,0,0,0,139,
  	140,5,33,0,0,140,46,1,0,0,0,141,142,5,60,0,0,142,48,1,0,0,0,143,144,5,
  	62,0,0,144,50,1,0,0,0,145,146,5,61,0,0,146,147,5,61,0,0,147,52,1,0,0,
  	0,148,149,5,60,0,0,149,150,5,61,0,0,150,54,1,0,0,0,151,152,5,62,0,0,152,
  	153,5,61,0,0,153,56,1,0,0,0,154,155,5,33,0,0,155,156,5,61,0,0,156,58,
  	1,0,0,0,157,158,7,0,0,0,158,159,1,0,0,0,159,160,6,29,0,0,160,60,1,0,0,
  	0,161,165,7,1,0,0,162,164,7,2,0,0,163,162,1,0,0,0,164,167,1,0,0,0,165,
  	163,1,0,0,0,165,166,1,0,0,0,166,62,1,0,0,0,167,165,1,0,0,0,168,169,5,
  	47,0,0,169,170,5,47,0,0,170,174,1,0,0,0,171,173,9,0,0,0,172,171,1,0,0,
  	0,173,176,1,0,0,0,174,175,1,0,0,0,174,172,1,0,0,0,175,177,1,0,0,0,176,
  	174,1,0,0,0,177,178,5,10,0,0,178,179,1,0,0,0,179,180,6,31,0,0,180,64,
  	1,0,0,0,181,183,3,67,33,0,182,184,7,3,0,0,183,182,1,0,0,0,184,185,1,0,
  	0,0,185,183,1,0,0,0,185,186,1,0,0,0,186,66,1,0,0,0,187,189,5,45,0,0,188,
  	187,1,0,0,0,188,189,1,0,0,0,189,68,1,0,0,0,5,0,165,174,185,188,1,6,0,
  	0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  inoxislexerLexerStaticData = std::move(staticData);
}

}

InoxisLexer::InoxisLexer(CharStream *input) : Lexer(input) {
  InoxisLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *inoxislexerLexerStaticData->atn, inoxislexerLexerStaticData->decisionToDFA, inoxislexerLexerStaticData->sharedContextCache);
}

InoxisLexer::~InoxisLexer() {
  delete _interpreter;
}

std::string InoxisLexer::getGrammarFileName() const {
  return "Inoxis.g4";
}

const std::vector<std::string>& InoxisLexer::getRuleNames() const {
  return inoxislexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& InoxisLexer::getChannelNames() const {
  return inoxislexerLexerStaticData->channelNames;
}

const std::vector<std::string>& InoxisLexer::getModeNames() const {
  return inoxislexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& InoxisLexer::getVocabulary() const {
  return inoxislexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView InoxisLexer::getSerializedATN() const {
  return inoxislexerLexerStaticData->serializedATN;
}

const atn::ATN& InoxisLexer::getATN() const {
  return *inoxislexerLexerStaticData->atn;
}




void InoxisLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  inoxislexerLexerInitialize();
#else
  ::antlr4::internal::call_once(inoxislexerLexerOnceFlag, inoxislexerLexerInitialize);
#endif
}
