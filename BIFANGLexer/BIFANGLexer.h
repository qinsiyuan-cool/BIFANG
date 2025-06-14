
// Generated from C:/Users/qinsiyuan/CLionProjects/BIFANG/BIFANGLexer.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  BIFANGLexer : public antlr4::Lexer {
public:
  enum {
    CONST = 1, INT = 2, FLOAT = 3, VOID = 4, IF = 5, ELSE = 6, WHILE = 7, 
    BREAK = 8, CONTINUE = 9, RETURN = 10, PLUS = 11, MINUS = 12, MUL = 13, 
    DIV = 14, MOD = 15, ASSIGN = 16, EQ = 17, NEQ = 18, LT = 19, GT = 20, 
    LE = 21, GE = 22, NOT = 23, AND = 24, OR = 25, L_PAREN = 26, R_PAREN = 27, 
    L_BRACE = 28, R_BRACE = 29, L_BRACKT = 30, R_BRACKT = 31, COMMA = 32, 
    SEMICOLON = 33, IDENT = 34, WS = 35, LINE_COMMENT = 36, MULTILINE_COMMENT = 37, 
    FLOAT_CONST = 38, INTEGER_CONST = 39
  };

  explicit BIFANGLexer(antlr4::CharStream *input);

  ~BIFANGLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

