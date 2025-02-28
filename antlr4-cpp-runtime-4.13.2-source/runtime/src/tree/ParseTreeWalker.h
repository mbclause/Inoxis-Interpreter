/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#pragma once

#include "antlr4-common.h"

namespace antlr4 {
namespace tree {

  class ANTLR4CPP_PUBLIC ParseTreeWalker {
  public:
    static ParseTreeWalker &DEFAULT;

    virtual ~ParseTreeWalker() = default;

    /**
    * 
    * Performs a walk on the given parse tree starting at the root and going down recursively
	* with depth-first search. On each node, ParseTreeWalker#enterRule is called before
    * recursively walking down into child nodes, then
    * ParseTreeWalker#exitRule is called after the recursive call to wind up.
	* 
    * param name=listener: The listener used by the walker to process grammar rules
	* param name=t :  The parse tree to be walked on
    */
    virtual void walk(ParseTreeListener *listener, ParseTree *t) const;

  protected:

    /**
    * 
    * Enters a grammar rule by first triggering the generic event ParseTreeListener.enterEveryRule
	* then by triggering the event specific to the given parse tree node
	* 
    * param name='listener' The listener responding to the trigger events 
	* param name='r' The grammar rule containing the rule context 
    */
    virtual void enterRule(ParseTreeListener *listener, ParseTree *r) const;

    /**
    * 
    * Exits a grammar rule by first triggering the event specific to the given parse tree node
	* then by triggering the generic event ParseTreeListener.exitEveryRule
	* 
    * param name='listener' The listener responding to the trigger events
	* param name='r'  The grammar rule containing the rule context
    */
    virtual void exitRule(ParseTreeListener *listener, ParseTree *r) const;
  };

} // namespace tree
} // namespace antlr4
