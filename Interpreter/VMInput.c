/*
file: VMInput.c
Description: Contains constructor and destructor functions for the structs in VMInput.h
*/
#include "VMInput.h"
#include <stdio.h>



// make functions for dynamically allocated structs
//makeUnaryOp
unaryOp* makeUnaryOp(OP _op, expression* _exp)
{
	// create a pointer to a new unary expression
	unaryOp* newUnaryExp = (unaryOp*)malloc(sizeof(unaryOp));

	if (newUnaryExp != NULL)
	{
		newUnaryExp->op = _op;

		newUnaryExp->exp = _exp;
	}

	else
	{
		printf("malloc failed\n");
	}

	return newUnaryExp;
}



//makeBinaryOp
BinOp* makeBinOp(OP _op, expression* _lhs, expression* _rhs)
{
	BinOp* newBinaryOp = (BinOp*)malloc(sizeof(BinOp));

	if (newBinaryOp != NULL)
	{
		newBinaryOp->op = _op;

		newBinaryOp->lhs = _lhs;

		newBinaryOp->rhs = _rhs;
	}

	else
	{
		printf("malloc failed\n");
	}

	return newBinaryOp;
}



// makeFuncCall
funcCall* makeFuncCall(unsigned  index, expression* _arg)
{
	funcCall* newFuncCall = (funcCall*)malloc(sizeof(funcCall));

	if (newFuncCall != NULL)
	{
		newFuncCall->funcIndex = index;

		newFuncCall->arg = _arg;
	}

	else
	{
		printf("malloc failed\n");
	}

	return newFuncCall;
}



// makeControlFlow
controlFlow* makeControlFlow(GArray* stats, expression condExp)
{
	controlFlow* newControl = (controlFlow*)malloc(sizeof(controlFlow));

	if (newControl != NULL)
	{
		newControl->statements = stats;

		newControl->condition = condExp;
	}

	else
	{
		printf("malloc failed\n");
	}

	return newControl;
}



// makePrint
print* makePrint(GArray* literalArray)
{
	print* newPrint = (print*)malloc(sizeof(print));

	if (newPrint != NULL)
	{
		newPrint->literals = literalArray;
	}

	else
	{
		printf("malloc failed\n");
	}

	return newPrint;
}



// makeFunction
function* makeFunction(GArray* stats, GArray* syms)
{
	function* newFunction = (function*)malloc(sizeof(function));

	if (newFunction != NULL)
	{
		newFunction->statements = stats;

		newFunction->symbols = syms;
	}

	else
	{
		printf("malloc failed\n");
	}

	return newFunction;
}




// corresponding free functions for each
// freeUnaryOp
bool  freeUnaryOp(unaryOp* uo)
{
	if(uo->exp)
		free(uo->exp);

	free(uo);

	return true;
}



// freeBinaryOp
bool  freeBinOp(BinOp* bo)
{
	if(bo->lhs)
		free(bo->lhs);

	if(bo->rhs)
		free(bo->rhs);

	free(bo);

	return true;
}



// freeFuncCall
bool  freeFuncCall(funcCall* _funcCall)
{
	if(_funcCall->arg)
		free(_funcCall->arg);

	free(_funcCall);

	return true;
}



// freeControlFlow
bool  freeControlFlow(controlFlow* cf)
{
	if (cf->statements)
		g_array_free(cf->statements, true);

	return true;
}



// freePrint
bool  freePrint(print* p)
{
	if (p->literals)
		g_array_free(p->literals, true);

	return true;
}



// freeFunction
bool freeFunction(function* func)
{
	if (func->statements)
		g_array_free(func->statements, true);

	if (func->symbols)
		g_array_free(func->symbols, true);

	return true;
}



// init functions for complex stack based structs
// initExpression for each possible union type
expression  initBinOpExpression(BinOp*  bo)
{
	expression newExp;

	newExp.kind = EXPR_BIN;

	newExp.val.binaryOp = *bo;

	return newExp;
}



expression  initUnaryOpExpression(unaryOp*  uo)
{
	expression newExp;

	newExp.kind = EXPR_UNARY;

	newExp.val.unary = *uo;

	return newExp;
}



expression  initLiteralExpression(literal  lit)
{
	expression newExp;

	newExp.kind = EXPR_LIT;

	newExp.val.litVal = lit;

	return newExp;
}



expression  initFuncCallExpression(funcCall* call)
{
	expression newExp;

	newExp.kind = EXPR_CALL;

	newExp.val.call = *call;

	return newExp;
}



// initStatement for each statement type
statement  initVarDecStatement(varDec  dec)
{
	statement newStat;

	newStat.statType = VAR_DEC;

	newStat.vals.varDecVals = dec;

	return newStat;
}



statement  initAssignStatement(assign  _assign)
{
	statement newStat;

	newStat.statType = ASSIGN;

	newStat.vals.assignVals = _assign;

	return newStat;
}



statement  initControlFlowStatement(controlFlow  flow, STAT_TYPE controlType)
{
	statement newStat;

	newStat.statType = controlType;

	newStat.vals.ctrlFlowVals = flow;

	return newStat;
}



statement  initPrintStatement(print  _print)
{
	statement newStat;

	newStat.statType = PRINT;

	newStat.vals.printVals = _print;

	return newStat;
}



statement  initFreeStatement(freeType  _free)
{
	statement newStat;

	newStat.statType = FREE;

	newStat.vals.freeVal = _free;

	return newStat;
}



statement  initReturnStatement(Return  ret)
{
	statement newStat;

	newStat.statType = RETURN;

	newStat.vals.retVal = ret;

	return newStat;
}



