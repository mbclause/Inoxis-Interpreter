﻿/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#include <utility>
#include <string>
#include <cstddef>
#include "atn/NotSetTransition.h"
#include "atn/TransitionType.h"
#include "atn/ATNState.h"
#include "misc/IntervalSet.h"

using namespace antlr4;
using namespace antlr4::atn;

NotSetTransition::NotSetTransition(ATNState *target, misc::IntervalSet set) : SetTransition(TransitionType::NOT_SET, target, std::move(set)) {}

bool NotSetTransition::matches(size_t symbol, size_t minVocabSymbol, size_t maxVocabSymbol) const {
  return symbol >= minVocabSymbol && symbol <= maxVocabSymbol
    && !SetTransition::matches(symbol, minVocabSymbol, maxVocabSymbol);
}

std::string NotSetTransition::toString() const {
  return "NOT_SET " + Transition::toString() + " { " + SetTransition::toString() + " }";
}
