﻿/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#pragma once

#include "support/Any.h"

namespace antlr4 {
namespace tree {

  /// 
  /// This interface defines the basic notion of a parse tree visitor. Generated
  /// visitors implement this interface and the XVisitor interface for
  /// grammar X.
  /// 
  /// param <T> The return type of the visit operation. Use Void for
  /// operations with no return type. 
  // ml: no template parameter here, to avoid the need for virtual template functions. Instead we have our Any class.
  class ANTLR4CPP_PUBLIC ParseTreeVisitor {
  public:
    virtual ~ParseTreeVisitor();

    /// 
    /// Visit a parse tree, and return a user-defined result of the operation.
    /// 
    /// param name="tree"  The ParseTree to visit. 
    /// returns  The result of visiting the parse tree.
    virtual std::any visit(ParseTree *tree) = 0;

    /// 
    /// Visit the children of a node, and return a user-defined result of the
    /// operation.
    /// 
    /// param name="node" The ParseTree whose children should be visited.
    /// returns The result of visiting the children of the node. 
    virtual std::any visitChildren(ParseTree *node) = 0;

    /// 
    /// Visit a terminal node, and return a user-defined result of the operation.
    /// 
    /// param name="node" The TerminalNode to visit. 
    /// returns The result of visiting the node. 
    virtual std::any visitTerminal(TerminalNode *node) = 0;

    /// 
    /// Visit an error node, and return a user-defined result of the operation.
    /// 
    /// param name="node"  The ErrorNode to visit.
    /// returns  The result of visiting the node. 
    virtual std::any visitErrorNode(ErrorNode *node) = 0;

  };

} // namespace tree
} // namespace antlr4
