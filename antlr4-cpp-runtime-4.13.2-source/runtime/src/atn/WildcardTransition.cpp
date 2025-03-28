﻿/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#include <string>
#include <cstddef>
#include "atn/ATNState.h"

#include "atn/TransitionType.h"
#include "atn/WildcardTransition.h"

using namespace antlr4::atn;

WildcardTransition::WildcardTransition(ATNState *target) : Transition(TransitionType::WILDCARD, target) {
}

bool WildcardTransition::matches(size_t symbol, size_t minVocabSymbol, size_t maxVocabSymbol) const {
  return symbol >= minVocabSymbol && symbol <= maxVocabSymbol;
}

std::string WildcardTransition::toString() const {
  return "WILDCARD " + Transition::toString() + " {}";
}
