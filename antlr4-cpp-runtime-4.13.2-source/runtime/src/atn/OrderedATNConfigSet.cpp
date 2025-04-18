﻿/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#include <cstddef>
#include "atn/OrderedATNConfigSet.h"

using namespace antlr4::atn;

size_t OrderedATNConfigSet::hashCode(const ATNConfig &atnConfig) const {
  return atnConfig.hashCode();
}

bool OrderedATNConfigSet::equals(const ATNConfig &lhs, const ATNConfig &rhs) const {
  return lhs == rhs;
}
