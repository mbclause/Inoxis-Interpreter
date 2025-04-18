﻿/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#pragma once

#include "antlr4-common.h"
#include "atn/ATNStateType.h"
#include "atn/ATNState.h"

namespace antlr4 {
namespace atn {

  class ANTLR4CPP_PUBLIC StarLoopbackState final : public ATNState {
  public:
    static bool is(const ATNState &atnState) { return atnState.getStateType() == ATNStateType::STAR_LOOP_BACK; }

    static bool is(const ATNState *atnState) { return atnState != nullptr && is(*atnState); }

    StarLoopbackState() : ATNState(ATNStateType::STAR_LOOP_BACK) {}

    StarLoopEntryState *getLoopEntryState() const;
  };

} // namespace atn
} // namespace antlr4
