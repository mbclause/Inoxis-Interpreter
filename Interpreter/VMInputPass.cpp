/*
File: VMInputPass.cpp
Description: Member function definitions for VMInputPass.
*/


#include "VMInputPass.h"


/*
Function: findControlFlowBlocks
Description: loop through all statements in a control flow block, if we find another cf block, pass depth+1 to it
*/
void  VMInputPass::findControlFlowBlocks(InoxisParser::IfElseBlockContext* ifctx,
	InoxisParser::WhileContext* whilectx, int  depth)
{
	if (ifctx)
	{
		// check if statements
		// get all of the statements for the if block only
		vector<InoxisParser::StatementContext*> ifStats = ifctx->statList()->statement();

		for (int i = 0; i < ifStats.size(); i++)
		{
			// if it's an if/else block we need to get the statements a different way
			if (ifStats[i]->ifElseBlock())
			{
				cfDepthProp.put(ifStats[i]->ifElseBlock(), depth);
			}

			else if(ifStats[i]->while_())
			{
				cfDepthProp.put(ifStats[i]->while_(), depth);
			}
		}

		// check if there are elif blocks
		if (ifctx->elif()->getText().size() > 0)
		{
			vector<InoxisParser::StatListContext*> statLists = elifStatsProp.get(ifctx->elif());

			// now get all of the elif statements, if any, and add them
			for (int i = 0; i < statLists.size(); i++)
			{
				vector<InoxisParser::StatementContext*> elifStats = statLists[i]->statement();

				for (int j = 0; j < elifStats.size(); j++)
				{
					// if it's an if/else block we need to get the statements a different way
					if (elifStats[j]->ifElseBlock())
					{
						cfDepthProp.put(elifStats[j]->ifElseBlock(), depth);
					}

					else if(elifStats[j]->while_())
					{
						cfDepthProp.put(elifStats[j]->while_(), depth);
					}
				}
			}
		}


		// get the else statement if any and check its statements
		if (ifctx->else_()->getText().size() > 0)
		{
			vector<InoxisParser::StatementContext*> elseStats = ifctx->else_()->statList()->statement();

			for (int i = 0; i < elseStats.size(); i++)
			{
				// if it's an if/else block we need to get the statements a different way
				if (elseStats[i]->ifElseBlock())
				{
					cfDepthProp.put(elseStats[i]->ifElseBlock(), depth);
				}

				else if (elseStats[i]->while_())
				{
					cfDepthProp.put(elseStats[i]->while_(), depth);
				}
			}
		}
	}

	else if (whilectx)
	{
		vector<InoxisParser::StatementContext*> whileStats = whilectx->statList()->statement();

		for (int i = 0; i < whileStats.size(); i++)
		{
			// if it's an if/else block we need to get the statements a different way
			if (whileStats[i]->ifElseBlock())
			{
				cfDepthProp.put(whileStats[i]->ifElseBlock(), depth);
			}

			else if (whileStats[i]->while_())
			{
				cfDepthProp.put(whileStats[i]->while_(), depth);
			}
		}
	}

	else
	{

	}
} // end fincControlFlowBlocks



/*
Function: enterWhile
Description: get current depth and then check if there are any cf statements in the block
*/
void VMInputPass::enterWhile(InoxisParser::WhileContext* ctx)
{
	inControlBlock = true;

	int  depth = 0;

	depth = cfDepthProp.get(ctx);

	if (depth == 0)
	{
		depth = 1;

		cfDepthProp.put(ctx, depth);
	}

	findControlFlowBlocks(NULL, ctx, depth + 1);
} // end enterWhile



/*
Function: enterIfElseBlock
Description: get current depth and then check if there are any cf statements in the block
*/
void VMInputPass::enterIfElseBlock(InoxisParser::IfElseBlockContext* ctx)
{
	inControlBlock = true;

	int  depth = 0;

	depth = cfDepthProp.get(ctx);

	if (depth == 0)
	{
		depth = 1;

		cfDepthProp.put(ctx, depth);
	}

	findControlFlowBlocks(ctx, NULL, depth + 1);

} // end enterIfElseBlock



/*
Function: exitFuncDef
Description: make a new function struct and add it to array, reset statement index
*/
void VMInputPass::exitFuncDef(InoxisParser::FuncDefContext* ctx) 
{

	function newFunction = { currentStatementsGArray, currentSymbolsGArray };

	g_array_append_val(functions, newFunction);

	statementIndex = 0;
} // end exitFuncDef



/*
Function: exitMain
Description: make a new function struct and add it to array, reset statement index
*/
void VMInputPass::exitMain(InoxisParser::MainContext* ctx) 
{

	statementIndex = 0;

	function newFunction = { currentStatementsGArray, currentSymbolsGArray };

	g_array_append_val(functions, newFunction);
} // end exitMain



/*
Function: exitReturn
Description: make the return statement and add it to stat list
*/
void VMInputPass::exitReturn(InoxisParser::ReturnContext* ctx)
{
	// get the return value
	expression rVal = expProp.get(ctx->retVal());

	// make the return stat
	Return  r{ rVal };

	statement newReturn = initReturnStatement(r);

	//printStatement(newReturn);

	g_array_append_val(currentStatementsGArray, newReturn);

	incrementStatements();
} // end exitReturn



/*
Function: exitWhile
Description: create a while statement and add it to statement list
*/
void VMInputPass::exitWhile(InoxisParser::WhileContext* ctx)
{
	// get the conditional expression for the if block
	expression condition = expProp.get(ctx->condition());

	GArray* whileStats = g_array_new(false, false, sizeof(statement));

	// get all of the statements in the block
	for (int i = 0; i < ctx->statList()->statement().size(); i++)
	{

			statement newStatement = stmntProp.get(ctx->statList()->statement()[i]);

			g_array_append_val(whileStats, newStatement);
		
	}

	// create a new if statement and add it to statement list
	controlFlow* newWhile = makeControlFlow(whileStats, condition);

	statement whileStat = initControlFlowStatement(*newWhile, WHILE);

	//printStatement(whileStat);

	int depth = cfDepthProp.get(ctx);

	if (depth == 1)
	{

		g_array_append_val(currentStatementsGArray, whileStat);

		inControlBlock = false;
	}

	else if (depth > 1)
	{
		stmntProp.put(ctx, whileStat);
	}
} // end exitwhile



/*
Function: exitElse
Descrition: create the else statement and pass it up the tree
*/
void VMInputPass::exitElse(InoxisParser::ElseContext* ctx)
{
	if (ctx->statList() == NULL)
		return;

	// there's no condition, empty expression
	expression elseCond = initEmptyExpression();

	// get all of the statements
	GArray* elseStats = g_array_new(false, false, sizeof(statement));

	for (int i = 0; i < ctx->statList()->statement().size(); i++)
	{
		// if it's an if/else block we need to get the statements a different way
		if (ctx->statList()->statement()[i]->ifElseBlock())
		{
			// call our custom function to get all of the statements
			GArray* s = getIfElseBlocks(ctx->statList()->statement()[i]->ifElseBlock());

			g_array_append_vals(elseStats, s->data, s->len);
		}

		else
		{
			statement newStatement = stmntProp.get(ctx->statList()->statement()[i]);

			g_array_append_val(elseStats, newStatement);
		}
	}

	controlFlow* newElse = makeControlFlow(elseStats, elseCond);

	statement elseStat = initControlFlowStatement(*newElse, ELSE);

	stmntProp.put(ctx, elseStat);
} // end exitElse



/*
Function: exitElif
Descrition: pass the vector of statLists and conditions up the parse tree
*/
void VMInputPass::exitElif(InoxisParser::ElifContext* ctx)
{
	if (ctx)
	{
		elifCondsProp.put(ctx, ctx->condition());

		elifStatsProp.put(ctx, ctx->statList());
	}
} // end exitElif



/*
Function: getIfElseBlocks
Description: since Inoxis treats all of the blocks in an if/else block as one statement, we need to get
all of the separate blocks, add them to a GArray of statements and return that array. This ensures they are in order.
*/
GArray* VMInputPass::getIfElseBlocks(InoxisParser::IfElseBlockContext* ctx)
{
	GArray* blockStats = g_array_new(false, false, sizeof(statement));

	// get the conditional expression for the if block
	expression condition = expProp.get(ctx->condition());

	GArray* ifStats = g_array_new(false, false, sizeof(statement));

	// get all of the statements for the if block only
	for (int i = 0; i < ctx->statList()->statement().size(); i++)
	{

			statement newStatement = stmntProp.get(ctx->statList()->statement()[i]);

			g_array_append_val(ifStats, newStatement);
		
	}

	// create a new if statement and add it to statement list
	controlFlow* newIf = makeControlFlow(ifStats, condition);

	statement ifStat = initControlFlowStatement(*newIf, IF);

	//printStatement(ifStat);

	g_array_append_val(blockStats, ifStat);

	if (ctx->elif()->getText().size() > 0)
	{
		vector<InoxisParser::StatListContext*> statLists = elifStatsProp.get(ctx->elif());

		vector<InoxisParser::ConditionContext*> conditions = elifCondsProp.get(ctx->elif());

		// now get all of the elif statements, if any, and add them
		for (int i = 0; i < conditions.size(); i++)
		{
			expression elifCondition = expProp.get(conditions[i]);

			GArray* elifStats = g_array_new(false, false, sizeof(statement));

			for (int j = 0; j < statLists[i]->statement().size(); j++)
			{

					statement newStatement = stmntProp.get(statLists[i]->statement()[j]);

					g_array_append_val(elifStats, newStatement);
				
			}

			controlFlow* newElif = makeControlFlow(elifStats, elifCondition);

			statement elifStat = initControlFlowStatement(*newElif, ELIF);

			//printStatement(elifStat);

			g_array_append_val(blockStats, elifStat);
		}
	}


	// get the else statement if any and add it
	if (ctx->else_()->getText().size() > 0)
	{

		statement elseStat = stmntProp.get(ctx->else_());

		g_array_append_val(blockStats, elseStat);

		//printStatement(elseStat);
	}

	return blockStats;
} // end getIFElseBlocks



/*
Function: exitStatement
Description: get the statement an pass it up the tree
*/
void VMInputPass::exitStatement(InoxisParser::StatementContext* ctx) 
{
	incrementStatements();

	statement s;

	// statement: varDec | assign | while | ifElseBlock | funcCall | print;
	if (ctx->assign())
	{
		s = stmntProp.get(ctx->assign());

		stmntProp.put(ctx, s);
	}

	else if (ctx->varDec())
	{
		s = stmntProp.get(ctx->varDec());
		stmntProp.put(ctx, s);
	}

	else if (ctx->while_())
	{
		s = stmntProp.get(ctx->while_());
		stmntProp.put(ctx, s);
	}

	// this won't work
	else if (ctx->ifElseBlock())
	{
		s = stmntProp.get(ctx->ifElseBlock());
		stmntProp.put(ctx, s);
	}

	else if (ctx->funcCall())
	{
		s = stmntProp.get(ctx->funcCall());
		stmntProp.put(ctx, s);
	}

	// else print
	else if (ctx->print())
	{
		s = stmntProp.get(ctx->print());
		stmntProp.put(ctx, s);
	}

	else
	{
		
	}

} // end exitStatement



/*
Function: exitIfElseBlock
Description: create an if statement
*/
void VMInputPass::exitIfElseBlock(InoxisParser::IfElseBlockContext* ctx)
{
	// the list of if/elif/else statements
	GArray* s = getIfElseBlocks(ctx);

	// create a new ifelse statement
	ifElseBlock ieb = initIfElseBlock(s);

	// make the statement
	statement newStat = initIfElseBlockStatement(ieb);

	int depth = cfDepthProp.get(ctx);

	if (depth == 1)
	{
		// add them to the function statement list
		g_array_append_val(currentStatementsGArray, newStat);

		inControlBlock = false;
	}

	else if (depth > 1)
	{
		stmntProp.put(ctx, newStat);
	}

} // end exitIfElseBlock



/*
Function: exitPrintLiteral
Description: get the expression that's being printed and pass it up the tree
*/
void VMInputPass::exitPrintLiteral(InoxisParser::PrintLiteralContext* ctx)
{
	expression newExp;

	if (ctx->STRING_LITERAL())
	{
		string s = ctx->STRING_LITERAL()->getText();

		const char* cs = s.c_str();

		GString* gs = g_string_new(cs);

		literal stringLit = initStringLiteral(gs);

		newExp = initLiteralExpression(stringLit);
	}

	else if (ctx->var())
	{
		newExp = expProp.get(ctx->var());
	}

	// cout << endl
	else
	{
		GString* gs = g_string_new("\n");

		literal stringLit = initStringLiteral(gs);

		newExp = initLiteralExpression(stringLit);
	}

	expProp.put(ctx, newExp);
} // end exitPrintLiteral



/*
Function: exitPrint
Description: get the first literal, if there are more, get them from exitOut
*/
void VMInputPass::exitPrint(InoxisParser::PrintContext* ctx)
{
	GArray* newLiterals = g_array_new(false, false, sizeof(expression));

	expression newExp = expProp.get(ctx->printLiteral());

	g_array_append_val(newLiterals, newExp);

	// if there's more to the print statement
	if (ctx->out()->getText().length() > 0)
	{
		print outStatement = PrintProp.get(ctx->out());

		guint len = outStatement.literals->len;

		g_array_append_vals(newLiterals, outStatement.literals->data, len);
	}

	print *newPrint = makePrint(newLiterals);

	statement  newStatement = initPrintStatement(*newPrint);

	//printPrintStat(*newPrint);

	if(!inControlBlock)
		g_array_append_val(currentStatementsGArray, newStatement);

	stmntProp.put(ctx, newStatement);
} // end exitPrint



/*
Function: exitOut
Description: get all of the literals for the rest of the print statement and pass them up to exitPrint
*/
void VMInputPass::exitOut(InoxisParser::OutContext* ctx)
{
	GArray* newLiterals = g_array_new(false, false, sizeof(expression));

	for (int i = 0; i < ctx->printLiteral().size(); i++)
	{
		expression newExp = expProp.get(ctx->printLiteral()[i]);

		g_array_append_val(newLiterals, newExp);
	}

	print* p = makePrint(newLiterals);

	PrintProp.put(ctx, *p);
} // end exitOut



/*
Function: exitAssign
Description: get the lhs and rhs from respective children.
Get allocation size, if any. Create an assign statement and add it to statements garry for function
*/
void VMInputPass::exitAssign(InoxisParser::AssignContext* ctx)
{
	expression lhs = expProp.get(ctx->var());

	expression rhs = expProp.get(ctx->assignRHS());

	size_t  allocSize = allocationSizeProp.get(ctx->assignRHS());

	// get the lhs variable name
	string lhsVarName = ctx->var()->ID()->getText();

	// get it's memory index
	unsigned lhsVarIndex = currentLocalsMap[lhsVarName];

	bool isArray = false;

	bool heapAlloc = false;

	OP lhsDataType = NONE;

	if (ctx->var()->array()->getText().size() > 0)
		isArray = true;

	if (ctx->var()->pointRef()->getText().size() > 0)
	{
		if (ctx->var()->pointRef()->getText() == "*")
			lhsDataType = POINTER_OP;
		else
			lhsDataType = REF_OP;
	}

	if (currentFunction.locals[lhsVarName].dataType == POINTER)
		lhsDataType = POINTER_OP;

	if (allocSize > 0)
		heapAlloc = true;

	/*    bool heapAlloc; size_t allocSize; expression lhs; expression rhs;*/
	assign newAssign{ lhsVarIndex, heapAlloc, allocSize, lhs, rhs, isArray, lhsDataType };

	//printAssign(newAssign);

	statement newStatement = initAssignStatement(newAssign);

	if (!inControlBlock)
		g_array_append_val(currentStatementsGArray, newStatement);

	stmntProp.put(ctx, newStatement);
} // end exitAssign



/*
Function: exitAllocate
Description: make an allocation expression and get the allocation size to pass up the tree
*/
void VMInputPass::exitAllocate(InoxisParser::AllocateContext* ctx)
{

	expression exp;

	if (ctx->array()->getText().size() > 0)
	{
		allocationSizeProp.put(ctx, allocationSizeProp.get(ctx->array()));

		exp = expProp.get(ctx->array());
	}

	else
	{
		allocationSizeProp.put(ctx, 1);

		exp = initEmptyExpression();
	}

	expression* expPtr = makeExpression(exp);

	unaryOp* uo = makeUnaryOp(NEW, expPtr);

	expression* newExp = makeUnaryOpExpression(uo);

	expProp.put(ctx, *newExp);
} // end exitAllocate



/*
Function: exitAssignRHS
Description: pass the rhs expression up the tree
*/
void VMInputPass::exitAssignRHS(InoxisParser::AssignRHSContext* ctx)
{
	int allocationSize = 0;

	if (ctx->expression())
	{
		expProp.put(ctx, expProp.get(ctx->expression()));
	}

	else if (ctx->rhsRef())
	{
		expProp.put(ctx, expProp.get(ctx->rhsRef()));
	}

	// otherwise allocation
	else
	{
		expProp.put(ctx, expProp.get(ctx->allocate()));

		allocationSize = allocationSizeProp.get(ctx->allocate());
	}

	allocationSizeProp.put(ctx, allocationSize);
} // end exitAssignRHS



/*
Function: exitVarDec
Description: create the expression for the lhs of the declaration and if there's an assignment, get the rhs from child.
Get allocation size, if any. Create a varDec statement and add it to statements garry for function
*/
void VMInputPass::exitVarDec(InoxisParser::VarDecContext* ctx)
{
	// make the var literal expression
	expression* newLitExp;

	string varName = ctx->ID()->getText();

	unsigned index = currentLocalsMap[varName];

	literal varLit = initVarLiteral(index);

	newLitExp = makeLiteralExpression(varLit);

	// now create the lhs expression
	expression* lhs;

	expression rhs;

	size_t allocSize = 0;

	bool hasAllocation = false;

	bool hasRHS = false;

	bool isStackArray = false;

	size_t stackArraySize = 0;

	OP  op = NONE;

	// if there's a * or &

		if (ctx->pointRef()->getText().size() > 0)
		{

			if (ctx->pointRef()->getText() == "&")
			{
				op = REF_OP;
			}

			else
			{
				op = POINTER_OP;
			}
			

			unaryOp* newUnary = makeUnaryOp(op, newLitExp);

			lhs = makeUnaryOpExpression(newUnary);

			//freeUnaryOp(newUnary);

			//free(unExp);
		}
	

	// if the subscript operator is used...
	else if (ctx->array()->getText().size() > 0)
	{
		expression indexExp = expProp.get(ctx->array());

		expression* indexPtr = makeExpression(indexExp);

		BinOp* newBinOp = makeBinOp(BRACKETS, newLitExp, indexPtr);

		lhs = makeBinOpExpression(newBinOp);

		op = BRACKETS;

		// get array size for variable
		stackArraySize = currentFunction.locals[varName].arraySize;
	}

	// otherwise just use the literal expression
	else
	{
		lhs = newLitExp;
	}

	// now check if the declaration has an assignment...
	if (ctx->varDecRHS()->getText().size() > 0)
	{
		// get the rhs from child node
		rhs = expProp.get(ctx->varDecRHS());

		// check if there's an allocation
		if(ctx->varDecRHS()->assignRHS())
			if (ctx->varDecRHS()->assignRHS()->allocate())
			{
				// get the allocation size from the descendant node
				allocSize = allocationSizeProp.get(ctx->varDecRHS());

				hasAllocation = true;
			}

		hasRHS = true;
	}

	else
	{
		rhs = initEmptyExpression();
	}

	/*
	    bool heapAlloc; bool hasRHS; bool isStackArray; size_t allocSize;size_t  stackArraySize;OP  lhsDataType;unsigned  lhsVarIndex;expression lhs;expression rhs;
	*/
	varDec newVarDec{ hasAllocation, hasRHS, isStackArray, allocSize, stackArraySize, op, index, *lhs, rhs };

	statement newStatement = initVarDecStatement(newVarDec);

	//printVarDec(newVarDec);

	// add statement to statements array
	if (!inControlBlock)
		g_array_append_val(currentStatementsGArray, newStatement);

	stmntProp.put(ctx, newStatement);
} // end exitVarDec





/*
Function: exitCondRHS
Description: create the rhs of a conditional expression, pass it up tree
*/
void VMInputPass::exitCondRHS(InoxisParser::CondRHSContext* ctx)
{
	expression* newExp;

	if (ctx->INT() != NULL)
	{
		int num = stoi(ctx->INT()->getText());

		literal numLit = initNumberLiteral(num);

		newExp = makeLiteralExpression(numLit);
	}

	else
	{
		string varName = ctx->ID()->getText();

		unsigned index = currentLocalsMap[varName];

		literal varLit = initVarLiteral(index);

		newExp = makeLiteralExpression(varLit);
	}

	expProp.put(ctx, *newExp);
} // end exitCondRHS



/*
Function: exitCondition
Description: create a condition expression and pass it up the tree
*/
void VMInputPass::exitCondition(InoxisParser::ConditionContext* ctx)
{
	OP op;

	// first get the condition operator
	string s = ctx->condOp()->getText();

	if (s == "<")
		op = LESS;

	else if (s == ">")
		op = GREATER;

	else if (s == "==")
		op = DOUBLE_EQUAL;

	else if (s == "<=")
		op = LESS_EQUAL;

	else if(s == ">=")
		op = GREATER_EQUAL;

	else if(s == "!=")
		op = NOT_EQUAL;

	else
	{
		op = NONE;
	}


	// make the lhs of the condition, which is a variable name
	// condition: not ID condOp condRHS;
	expression* lhs;

	string varName = ctx->ID()->getText();

	unsigned index = currentLocalsMap[varName];

	literal varLit = initVarLiteral(index);

	lhs = makeLiteralExpression(varLit);

	// now get the rhs from the child node
	expression* rhsExp = makeExpression(expProp.get(ctx->condRHS()));

	// make a new binary expression
	BinOp* bo = makeBinOp(op, lhs, rhsExp);

	expression* condExp = makeBinOpExpression(bo);

	// check if the condition is negated
	if (ctx->not_()->getText().size() > 0)
	{
		OP notOp = NOT;

		unaryOp* uo = makeUnaryOp(notOp, condExp);

		expression* notExp = makeUnaryOpExpression(uo);

		expProp.put(ctx, *notExp);
	}

	else
	{
		expProp.put(ctx, *condExp);
	}

} // end exitCondition



/*
Function: exitRhsRef
Description: create a unary epxression that's a mutable or regular reference and pass it up the tree
*/
void VMInputPass::exitRhsRef(InoxisParser::RhsRefContext* ctx)
{
	OP op;

	expression* newLitExp;

	string varName = ctx->ID()->getText();

	unsigned index = currentLocalsMap[varName];

	literal varLit = initVarLiteral(index);

	newLitExp = makeLiteralExpression(varLit);

	// if it's a mutable reference
	if (ctx->mut()->getText().size() > 0)
	{
		op = MUT_REF;
	}

	else
	{
		op = REF_OP;
	}

	unaryOp* uo = makeUnaryOp(op, newLitExp);

	expression* newUnaryExp = makeUnaryOpExpression(uo);

	expProp.put(ctx, *newUnaryExp);
} // end exitRhsRef



/*
Function: exitArg
Description: pass the expression made by the function argument up the tree
*/
void VMInputPass::exitArg(InoxisParser::ArgContext* ctx)
{
	expression* newExp;

	// if the argument is just a number
	if (ctx->INT() != NULL)
	{
		int num = stoi(ctx->INT()->getText());

		literal numLit = initNumberLiteral(num);

		newExp = makeLiteralExpression(numLit);
	}

	// else, the argument is a variable
	else
	{
		// get the expression from the child var() node
		newExp = makeExpression(expProp.get(ctx->var()));
	}

	expProp.put(ctx, *newExp);
} // end exitArg



/*
Function: exitVar
Description: either create a new literal expression or a unary expression if & or * are used, pass it up the tree
*/
void VMInputPass::exitVar(InoxisParser::VarContext* ctx)
{
	expression* newLitExp;

	string varName = ctx->ID()->getText();

	unsigned index = currentLocalsMap[varName];

	literal varLit = initVarLiteral(index);

	newLitExp = makeLiteralExpression(varLit);

	// if there's a * or &
	if (ctx->pointRef()->getText().size() > 0)
	{
		OP op;

		if (ctx->pointRef()->getText() == "&")
		{
			op = REF_OP;
		}

		else
		{
			op = POINTER_OP;
		}

		unaryOp* newUnary = makeUnaryOp(op, newLitExp);

		expression* unExp = makeUnaryOpExpression(newUnary);

		expProp.put(ctx, *unExp);

	}

	// if the subscript operator is used...
	else if (ctx->array()->getText().size() > 0)
	{
		expression indexExp = expProp.get(ctx->array());

		expression* indexPtr = makeExpression(indexExp);

		BinOp* newBinOp = makeBinOp(BRACKETS, newLitExp, indexPtr);

		expression* newExp = makeBinOpExpression(newBinOp);

		expProp.put(ctx, *newExp);
	}

	else
	{
		expProp.put(ctx, *newLitExp);
	}
} // end exitVar



/*
Function: exitIndex
Description: pass the index literal expression up the tree
*/
void VMInputPass::exitIndex(InoxisParser::IndexContext* ctx)
{
	expression* newExp;

	if (ctx->INT() != NULL)
	{
		int num = stoi(ctx->INT()->getText());

		literal numLit = initNumberLiteral(num);

		newExp = makeLiteralExpression(numLit);

		allocationSizeProp.put(ctx, num);
	}

	else
	{
		string varName = ctx->ID()->getText();

		unsigned index = currentLocalsMap[varName];

		literal varLit = initVarLiteral(index);

		newExp = makeLiteralExpression(varLit);

		allocationSizeProp.put(ctx, 0);
	}

	expProp.put(ctx, *newExp);

} // end exitIndex




/*
Function: exitFuncCall
Description: a solitary function call, get the argument expression and use it to create a funcCall
*/
void VMInputPass::exitFuncCall(InoxisParser::FuncCallContext* ctx)
{
	string funcName = ctx->ID()->getText();

	int funcIndex = functionMap[funcName];

	// get the argument expression from the child node
	expression* argExp = makeExpression(expProp.get(ctx->arg()));

	// make the func call
	funcCall* newFuncCall = makeFuncCall(funcIndex, argExp);

	// use this to create a statement object
	statement newStatement = initFuncCallStatement(newFuncCall);

	//freeFuncCall(newFuncCall);

	//printFuncCall(*newFuncCall);

	if (!inControlBlock)
		g_array_append_val(currentStatementsGArray, newStatement);

	stmntProp.put(ctx, newStatement);
} // end exitFuncCall



/*
Function: exitFuncCallExp
Description: a function call that's part of an expression, get the argument expression and use it to create a funcCall
*/
void VMInputPass::exitFuncCallFactor(InoxisParser::FuncCallFactorContext* ctx)
{
	string funcName = ctx->ID()->getText();

	int funcIndex = functionMap[funcName];

	// get the argument expression from the child node
	expression* argExp = makeExpression(expProp.get(ctx->arg()));

	// make the func call
	funcCall* newFuncCall = makeFuncCall(funcIndex, argExp);

	expression* funcExp = makeFuncCallExpression(newFuncCall);

	expProp.put(ctx, *funcExp);
}



/*
Function: exitNumLiteral
Description: get the number and create a new literal struct with it, then add it to the rule context for it's parent
*/
void VMInputPass::exitNumLiteral(InoxisParser::NumLiteralContext* ctx)
{
	// get the number
	int num = stoi(ctx->INT()->getText());

	literal numLiteral = initNumberLiteral(num);

	expression exp = initLiteralExpression(numLiteral);

	expProp.put(ctx, exp);
}



/*
Function: exitVarLiteral
Description: lookup index for variable in locals garray, use that to create an expression and pass it up
*/
void VMInputPass::exitVarLiteral(InoxisParser::VarLiteralContext* ctx)
{
	expression newExp = expProp.get(ctx->var());

	expProp.put(ctx, newExp);
}



/*
Function: exitAdd
Description: get the two expression operands and store them in a new BinOp expression
*/
void VMInputPass::exitAdd(InoxisParser::AddContext* ctx)
{
	expression left = expProp.get(ctx->expression(0));

	expression* leftPtr = makeExpression(left);

	expression right = expProp.get(ctx->expression(1));

	expression* rightPtr = makeExpression(right);

	BinOp* newBinOp = makeBinOp(ADD, leftPtr, rightPtr);

	expression* newExp = makeBinOpExpression(newBinOp);

	// nestle data into ast
	expProp.put(ctx, *newExp);
}



/*
Function: exitSubtract
Description: same as addition, just change OP
*/
void VMInputPass::exitSubtract(InoxisParser::SubtractContext* ctx)
{
	expression left = expProp.get(ctx->expression(0));

	expression* leftPtr = makeExpression(left);

	expression right = expProp.get(ctx->expression(1));

	expression* rightPtr = makeExpression(right);

	BinOp* newBinOp = makeBinOp(SUBTRACT, leftPtr, rightPtr);

	expression* newExp = makeBinOpExpression(newBinOp);

	// nestle data into ast
	expProp.put(ctx, *newExp);
}



/*
Function: enterFuncDef
Description: create new GArrays for the local memory and the function statements.
Then, loop through all the locals and add a memVal entry for each to local memory.
*/
void VMInputPass::enterFuncDef(InoxisParser::FuncDefContext* ctx)
{

	string funcName = ctx->ID()->getText();

	GArray*  localSymbols = g_array_new(false, false, sizeof(memVal));

	// create a new statements garry for the function
	GArray* funcStatements = g_array_new(false, false, sizeof(statement));

	vector<varSymbol>  varList = varListProp.get(ctx);

	// get the function symbol
	currentFunction = symbolTables.get(ctx);

	// create a new map from var names to array indices
	map<string, unsigned>  locals;

	unsigned index = 0;

	// loop through the locals and make a new array from their names
	for (int i = 0; i < varList.size(); i++)
	{
		varSymbol v = varList[i];

		string varName = v._name;

		locals[varName] = index;

		// if the variable is an array, we need to increment i
		if (v._isArray)
		{
			index += v.arraySize;
		}

		else
		{
			index++;
		}
	}


	for (unsigned k = 0; k < index; k++)
	{
		memVal  newMemVal = initIntMemVal(0);

		g_array_append_val(localSymbols, newMemVal);
	}

	currentLocalsMap = locals;

	currentStatementsGArray = funcStatements;


	currentSymbolsGArray = localSymbols;

	currentStatList = statLists.get(ctx); 
} // end enterFuncDef



/*
Function: enterMain
Description:  create new GArrays for the local memory and the function statements.
Then, loop through all the locals and add a memVal entry for each to local memory.
*/
void VMInputPass::enterMain(InoxisParser::MainContext* ctx)
{

	currentFunction = symbolTables.get(ctx);

	vector<varSymbol>  varList = varListProp.get(ctx);

	// create a new statements garry for the function
	GArray* funcStatements = g_array_new(false, false, sizeof(statement));

	GArray* localSymbols = g_array_new(false, false, sizeof(memVal));

	// create a new map from var names to array indices
	map<string, unsigned>  locals;

	unsigned index = 0;

	// loop through the locals and make a new array from their names
	for (int i = 0; i < varList.size(); i++)
	{
		varSymbol v = varList[i];

		string varName = v._name;

		locals[varName] = index;

		// if the variable is an array, we need to increment i
		if (v._isArray)
		{
			index += v.arraySize;
		}

		else
		{
			index++;
		}
	}

	for (unsigned k = 0; k < index; k++)
	{
		memVal newMemVal = initIntMemVal(0);

		g_array_append_val(localSymbols, newMemVal);
	}

	currentLocalsMap = locals;

	currentSymbolsGArray = localSymbols;

	currentStatementsGArray = funcStatements;
	
	currentStatList = statLists.get(ctx);
} // end enterMain








// function: incrementStatements
// every time this is called by exitStatement, we need to print that statement, then loop through any following
// sentinels, dropping all of those permissions
void  VMInputPass::incrementStatements()
{
	bool statementPrinted = false;

	// make sure we haven't reached the end of the list
	// this will happen if we've reached the end of the function and there are no sentinals left
	if (statementIndex < currentStatList.size())
	{

		// if the variant holds a statement, print it
		if (holds_alternative<string>(currentStatList[statementIndex]))
		{
			try
			{

			}

			catch (std::bad_variant_access const& ex)
			{

				cout << "Exception: " << ex.what() << endl;
			}

			// go to next variant to check if it's a sentinal
			statementIndex++;

			statementPrinted = true;
		}

		// while the current variant is a sentinel...
		while (true)
		{
			if (statementIndex >= currentStatList.size())
				break;

			if (!holds_alternative<sentinal>(currentStatList[statementIndex]))
				break;

			try
			{
				// get the name of the dropped var and then drop its permissions
				sentinal currentSentinal = get<sentinal>(currentStatList[statementIndex]);

				string varName = currentSentinal.varName;

				// if the variable that's dropped owns heap data...
				if (currentSentinal.heapAllocation)
				{
					// add a call to free(varName) to the list of statements
					// get index for variable first
					unsigned index = currentLocalsMap[varName];

					freeType newFree{ index };

					statement newStatement = initFreeStatement(newFree);

					g_array_append_val(currentStatementsGArray, newStatement);
				}
			}

			catch (std::bad_variant_access const& ex)
			{
				cout << "Exception: " << ex.what() << endl;
			}

			// go to next statement
			statementIndex++;
		}

		if (statementIndex < currentStatList.size() && !statementPrinted)
		{
			if (holds_alternative<string>(currentStatList[statementIndex]))
			{
				try
				{

				}

				catch (std::bad_variant_access const& ex)
				{
					cout << "Exception: " << ex.what() << endl;
				}

				// go to next variant to check if it's a sentinal
				statementIndex++;

				statementPrinted = true;
			}
		}
	}
} // end IncrementStatements









