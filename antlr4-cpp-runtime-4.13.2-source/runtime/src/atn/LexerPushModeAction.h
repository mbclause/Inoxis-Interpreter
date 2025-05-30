/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#pragma once

#include <string>
#include <cstddef>
#include "atn/LexerAction.h"
#include "antlr4-common.h"
#include "atn/LexerActionType.h"

namespace antlr4 {
namespace atn {

  /// <summary>
  /// Implements the {@code pushMode} lexer action by calling
  /// <seealso cref="Lexer#pushMode"/> with the assigned mode.
  ///
  /// @author Sam Harwell
  /// @since 4.2
  /// </summary>
  class ANTLR4CPP_PUBLIC LexerPushModeAction final : public LexerAction {
  public:
    static bool is(const LexerAction &lexerAction) { return lexerAction.getActionType() == LexerActionType::PUSH_MODE; }

    static bool is(const LexerAction *lexerAction) { return lexerAction != nullptr && is(*lexerAction); }

    /// <summary>
    /// Constructs a new {@code pushMode} action with the specified mode value. </summary>
    /// <param name="mode"> The mode value to pass to <seealso cref="Lexer#pushMode"/>. </param>
    explicit LexerPushModeAction(int mode);

    /// <summary>
    /// Get the lexer mode this action should transition the lexer to.
    /// </summary>
    /// <returns> The lexer mode for this {@code pushMode} command. </returns>
    int getMode() const { return _mode; }

    /// <summary>
    /// {@inheritDoc}
    ///
    /// <para>This action is implemented by calling <seealso cref="Lexer#pushMode"/> with the
    /// value provided by <seealso cref="#getMode"/>.</para>
    /// </summary>
    void execute(Lexer *lexer) const override;

    bool equals(const LexerAction &obj) const override;
    std::string toString() const override;

  protected:
    size_t hashCodeImpl() const override;

  private:
    const int _mode;
  };

} // namespace atn
} // namespace antlr4
