﻿/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#include <string>
#include <cstddef>
#include "Vocabulary.h"

#include "dfa/LexerDFASerializer.h"

using namespace antlr4::dfa;

LexerDFASerializer::LexerDFASerializer(const DFA *dfa) : DFASerializer(dfa, Vocabulary()) {
}

std::string LexerDFASerializer::getEdgeLabel(size_t i) const {
  return std::string("'") + static_cast<char>(i) + "'";
}
