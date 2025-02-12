/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#pragma once

#include "IntStream.h"
#include "misc/Interval.h"

namespace antlr4 {

  /// A source of characters for an ANTLR lexer.
  class ANTLR4CPP_PUBLIC CharStream : public IntStream {
  public:
    virtual ~CharStream();

    /// This method returns the text for a range of characters within this input
    /// stream. This method is guaranteed to not throw an exception if the
    /// specified interval lies entirely within a marked range. For more
    /// information about marked ranges, see IntStream::mark.
    ///
    /// param: interval - an interval within the stream
    /// 
    /// Return the text of the specified interval
    /// 
    /// NullPointerException if interval is null
    /// 
    /// IllegalArgumentException if interval.a < 0 or if
    /// interval.b < interval.a - 1, or if interval.b lies at or
    /// past the end of the stream
    /// 
    /// UnsupportedOperationException if the stream does not support
    /// getting the text of the specified interval
    virtual std::string getText(const misc::Interval &interval) = 0;

    virtual std::string toString() const = 0;
  };

} // namespace antlr4
