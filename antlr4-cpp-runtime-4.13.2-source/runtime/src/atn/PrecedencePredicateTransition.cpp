﻿/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#include <memory>
#include <string>
#include <cstddef>
#include "atn/ATNState.h"
#include "atn/TransitionType.h"
#include "atn/PrecedencePredicateTransition.h"

using namespace antlr4::atn;

PrecedencePredicateTransition::PrecedencePredicateTransition(ATNState *target, int precedence)
  : Transition(TransitionType::PRECEDENCE, target), _predicate(std::make_shared<SemanticContext::PrecedencePredicate>(precedence)) {}

bool PrecedencePredicateTransition::isEpsilon() const {
  return true;
}

bool PrecedencePredicateTransition::matches(size_t /*symbol*/, size_t /*minVocabSymbol*/, size_t /*maxVocabSymbol*/) const {
  return false;
}

std::string PrecedencePredicateTransition::toString() const {
  return "PRECEDENCE " + Transition::toString() + " { precedence: " + std::to_string(getPrecedence()) + " }";
}
