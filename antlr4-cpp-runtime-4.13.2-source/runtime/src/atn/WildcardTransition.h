﻿/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#pragma once

#include <string>
#include <cstddef>
#include "antlr4-common.h"
#include "atn/TransitionType.h"
#include "atn/ATNState.h"
#include "atn/Transition.h"

namespace antlr4 {
namespace atn {

  class ANTLR4CPP_PUBLIC WildcardTransition final : public Transition {
  public:
    static bool is(const Transition &transition) { return transition.getTransitionType() == TransitionType::WILDCARD; }

    static bool is(const Transition *transition) { return transition != nullptr && is(*transition); }

    explicit WildcardTransition(ATNState *target);

    bool matches(size_t symbol, size_t minVocabSymbol, size_t maxVocabSymbol) const override;

    std::string toString() const override;
  };

} // namespace atn
} // namespace antlr4
