﻿/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#include <string>
#include <cstddef>
#include "antlr4-common.h"
#include "atn/TransitionType.h"
#include "atn/ATNState.h"
#include "atn/ActionTransition.h"

using namespace antlr4::atn;

ActionTransition::ActionTransition(ATNState *target, size_t ruleIndex)
  : Transition(TransitionType::ACTION, target), ruleIndex(ruleIndex), actionIndex(INVALID_INDEX), isCtxDependent(false) {
}

ActionTransition::ActionTransition(ATNState *target, size_t ruleIndex, size_t actionIndex, bool isCtxDependent)
  : Transition(TransitionType::ACTION, target), ruleIndex(ruleIndex), actionIndex(actionIndex), isCtxDependent(isCtxDependent) {
}

bool ActionTransition::isEpsilon() const {
  return true; // we are to be ignored by analysis 'cept for predicates
}

bool ActionTransition::matches(size_t /*symbol*/, size_t /*minVocabSymbol*/, size_t /*maxVocabSymbol*/) const {
  return false;
}

std::string ActionTransition::toString() const {
  return " ACTION " + Transition::toString() + " { ruleIndex: " + std::to_string(ruleIndex) + ", actionIndex: " +
  std::to_string(actionIndex) + ", isCtxDependent: " + std::to_string(isCtxDependent) + " }";
}
