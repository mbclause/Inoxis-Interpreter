﻿/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#pragma once

#include <string>
#include <cstddef>
#include "antlr4-common.h"
#include "misc/IntervalSet.h"
#include "atn/TransitionType.h"
#include "atn/ATNState.h"
#include "atn/Transition.h"

namespace antlr4 {
namespace atn {

  class ANTLR4CPP_PUBLIC RangeTransition final : public Transition {
  public:
    static bool is(const Transition &transition) { return transition.getTransitionType() == TransitionType::RANGE; }

    static bool is(const Transition *transition) { return transition != nullptr && is(*transition); }

    const size_t from;
    const size_t to;

    RangeTransition(ATNState *target, size_t from, size_t to);

    misc::IntervalSet label() const override;
    bool matches(size_t symbol, size_t minVocabSymbol, size_t maxVocabSymbol) const override;

    std::string toString() const override;
  };

} // namespace atn
} // namespace antlr4
