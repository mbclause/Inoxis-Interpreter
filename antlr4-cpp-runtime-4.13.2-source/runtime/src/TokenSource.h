/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#pragma once

#include "TokenFactory.h"

namespace antlr4 {

  /// 
  /// A source of tokens must provide a sequence of tokens via nextToken()
  /// and also must reveal it's source of characters; CommonToken's text is
  /// computed from a CharStream; it only store indices into the char
  /// stream.
  /// 
  /// Errors from the lexer are never passed to the parser. Either you want to keep
  /// going or you do not upon token recognition error. If you do not want to
  /// continue lexing then you do not want to continue parsing. Just throw an
  /// exception not under RecognitionException and Java will naturally toss
  /// you all the way out of the recognizers. If you want to continue lexing then
  /// you should not throw an exception to the parser--it has already requested a
  /// token. Keep lexing until you get a valid one. Just report errors and keep
  /// going, looking for a valid token.
  /// 
  class ANTLR4CPP_PUBLIC TokenSource {
  public:
    virtual ~TokenSource();

    /// Return a Token object from your input stream (usually a
    /// CharStream). Do not fail/return upon lexing error; keep chewing
    /// on the characters until you get a good one; errors are not passed through
    /// to the parser.
    virtual std::unique_ptr<Token> nextToken() = 0;

    /// 
    /// Get the line number for the current position in the input stream. The
    /// first line in the input is line 1.
    /// 
    /// Returns the line number for the current position in the input stream, or
    /// 0 if the current token source does not track line numbers
    virtual size_t getLine() const = 0;

    /// 
    /// Get the index into the current line for the current position in the input
    /// stream. The first character on a line has position 0.
    /// 
    /// Returns the line number for the current position in the input stream, or
    /// (sze_t)-1 if the current token source does not track character positions. 
    virtual size_t getCharPositionInLine() = 0;

    /// 
    /// Get the CharStream from which this token source is currently
    /// providing tokens.
    /// 
    /// Returns the CharStream associated with the current position in
    /// the input, or null if no input stream is available for the token
    /// source.
    virtual CharStream* getInputStream() = 0;

    /// 
    /// Gets the name of the underlying input source. This method returns a
    /// non-null, non-empty string. If such a name is not known, this method
    /// returns UNKNOWN_SOURCE_NAME.
    ///
    virtual std::string getSourceName() = 0;

    /// 
    /// Set the TokenFactory this token source should use for creating
    /// Token objects from the input.
    /// 
    /// factory: The TokenFactory to use for creating tokens. 
    template<typename T1>
    void setTokenFactory(TokenFactory<T1> * /*factory*/) {}

    /// 
    /// Gets the TokenFactory this token source is currently using for
    /// creating Token objects from the input.
    /// 
    /// Returns The TokenFactory currently used by this token source. 
    virtual TokenFactory<CommonToken>* getTokenFactory() = 0;
  };

} // namespace antlr4
