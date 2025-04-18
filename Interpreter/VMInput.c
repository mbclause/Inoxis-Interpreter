/*
file: VMInput.c
Description: Contains constructor and destructor functions for the structs in VMInput.h
*/
#include "VMInput.h"
#include <stdio.h>


expression  initEmptyExpression()
{
	expression newExp;

	newExp.kind = EXPR_NONE;

	return newExp;
}


// init literal types
literal  initNumberLiteral(int num)
{
	literal newLit;

	newLit.kind = NUMBER_LIT;

	newLit.val.number = num;

	return newLit;
}


literal  initStringLiteral(GString* newString)
{
	literal newLit;

	newLit.kind = STRING_LIT;

	newLit.val.string = newString;

	return newLit;
}


literal  initVarLiteral(unsigned  index)
{
	literal newLit;

	newLit.kind = VARIABLE_LIT;

	newLit.val.varIndex = index;

	return newLit;
}


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








// init functions for complex stack based structs
// initExpression for each possible union type
expression*  makeBinOpExpression(BinOp*  bo)
{
	expression* newExp = (expression*)malloc(sizeof(expression));

	if (newExp)
	{
		newExp->kind = EXPR_BIN;

		newExp->val.binaryOp = *bo;
	}

	else
	{
		printf("malloc failed\n");
	}

	return newExp;
}

expression   initBinOpExpression(BinOp* bo)
{
	expression newExp;

	newExp.kind = EXPR_BIN;

	newExp.val.binaryOp = *bo;

	return  newExp;
}



expression*  makeUnaryOpExpression(unaryOp*  uo)
{

	expression* newExp = (expression*)malloc(sizeof(expression));

	if (newExp)
	{
		newExp->kind = EXPR_UNARY;

		newExp->val.unary = *uo;
	}

	else
	{
		printf("malloc failed\n");
	}

	return newExp;
}


expression   initUnaryOpExpression(unaryOp* uo)
{
	expression newExp;

	newExp.kind = EXPR_UNARY;

	newExp.val.unary = *uo;

	return  newExp;
}



expression*  makeLiteralExpression(literal  lit)
{
	expression* newExp = (expression*)malloc(sizeof(expression));

	if (newExp)
	{
		newExp->kind = EXPR_LIT;

		newExp->val.litVal = lit;
	}

	else
	{
		printf("malloc failed\n");
	}

	return newExp;
}



expression   initLiteralExpression(literal lit)
{
	expression newExp;

	newExp.kind = EXPR_LIT;

	newExp.val.litVal = lit;

	return  newExp;
}



expression*  makeFuncCallExpression(funcCall* call)
{
	expression* newExp = (expression*)malloc(sizeof(expression));

	if (newExp)
	{
		newExp->kind = EXPR_CALL;

		newExp->val.call = *call;
	}

	else
	{
		printf("malloc failed\n");
	}

	return newExp;
}

expression  initFuncCallExpression(funcCall* call)
{
	expression newExp;

	newExp.kind = EXPR_CALL;

	newExp.val.call = *call;

	return  newExp;
}


expression* makeExpression(expression exp)
{
	expression* newExp = (expression*)malloc(sizeof(expression));

	if (newExp)
	{
		*newExp = exp;
	}

	else
	{
		printf("malloc failed\n");
	}

	return newExp;
}



// corresponding free functions for each

// free expression
bool freeExpression(expression* exp)
{
	if(exp)
		free(exp);

	return true;
}



// freeUnaryOp
bool  freeUnaryOp(unaryOp* uo)
{
	if (uo->exp)
		free(uo->exp);

	if(uo)
		free(uo);

	return true;
}



// freeBinaryOp
bool  freeBinOp(BinOp* bo)
{
	if (bo->lhs)
		free(bo->lhs);

	if (bo->rhs)
		free(bo->rhs);

	if(bo)
		free(bo);

	return true;
}



// freeFuncCall
bool  freeFuncCall(funcCall* _funcCall)
{
	if (_funcCall->arg)
		free(_funcCall->arg);

	if(_funcCall)
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


bool freeStringLiteral(literal lit)
{
	if (lit.val.string)
		g_string_free(lit.val.string, true);

	return true;
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



statement  initFuncCallStatement(funcCall* call)
{
	statement newStat;

	newStat.statType = FUNC_CALL;

	newStat.vals.call = *call;

	return newStat;
}




/*
Function: printExpression
Description: print all the fields of the expression, calling print_ on the val type
*/
void  printExpression(expression exp)
{
	EXPR_KIND exprType = exp.kind;

	// EXPR_BIN, EXPR_LIT, EXPR_UNARY, EXPR_CALL
	switch (exprType)
	{
	case EXPR_BIN:
		printBinOp(exp.val.binaryOp);
		break;

	case EXPR_LIT:
		PrintLiteral(exp.val.litVal);
		break;

	case EXPR_UNARY:
		printUnary(exp.val.unary);
		break;

	case EXPR_CALL:
		printFuncCall(exp.val.call);
		break;

	case EXPR_NONE:
		break;

	default:
		break;
	}
}


// expression types
void printBinOp(BinOp bo)
{
	// print the lhs of the operation
	if(bo.lhs)
		printExpression(*bo.lhs);

	// print the operator
	printOperator(bo.op);

	// print rhs
	if(bo.rhs)
		printExpression(*bo.rhs);

}



void printUnary(unaryOp uo)
{
	// print operator
	printOperator(uo.op);

	// print expression
	if (uo.exp)
		printExpression(*uo.exp);
}



void PrintLiteral(literal  lit)
{
	if (lit.kind == VARIABLE_LIT)
	{
		printf(" variable at index %d ", lit.val.varIndex);
	}

	else if (lit.kind == NUMBER_LIT)
	{
		printf(" %d ", lit.val.number);
	}

	else
	{
		g_print(" %s ", lit.val.string->str);
	}
}



void printFuncCall(funcCall func)
{
	// print the function index
	printf(" Function index: %d (", func.funcIndex);

	printExpression(*func.arg);

	printf(") ");
}




/*
Function: printStatement
*/
void  printStatement(statement stat)
{
	// VAR_DEC, ASSIGN, IF, ELIF, ELSE, FUNC_CALL, PRINT, FREE, RETURN
	switch (stat.statType)
	{
	case VAR_DEC:
		printVarDec(stat.vals.varDecVals);
		break;

	case ASSIGN:
		printAssign(stat.vals.assignVals);
		break;

	case IF:
		printf("If ");
		printControlFlow(stat.vals.ctrlFlowVals);
		break;

	case ELIF:
		printf("Elif ");
		printControlFlow(stat.vals.ctrlFlowVals);
		break;

	case ELSE:
		printf("else ");
		printControlFlow(stat.vals.ctrlFlowVals);
		break;

	case WHILE:
		printf("while ");
		printControlFlow(stat.vals.ctrlFlowVals);
		break;

	case FUNC_CALL:
		printFuncCall(stat.vals.call);
		break;

	case PRINT:
		printPrintStat(stat.vals.printVals);
		break;

	case FREE:
		printFree(stat.vals.freeVal);
		break;

	case RETURN:
		printReturn(stat.vals.retVal);
		break;

	default:
		break;
	}
}


// statement types
void printAssign(assign  a)
{
	printExpression(a.lhs);

	printf(" = ");

	printExpression(a.rhs);

	printf("\n");
}



void printVarDec(varDec  vd)
{
	printf("int ");

	printExpression(vd.lhs);

	if (vd.rhs.kind != EXPR_NONE)
	{
		printf(" = ");

		printExpression(vd.rhs);
	}

	printf("\n");
}



void printControlFlow(controlFlow  cf)
{

	printExpression(cf.condition);

	printf("{\n");

	for (unsigned i = 0; i < cf.statements->len; i++)
	{
		statement stat = g_array_index(cf.statements, statement, i);

		printStatement(stat);
	}

	printf("}\n");
}



void  printFree(freeType f)
{
	printf("Free variable at index %d\n", f.varIndex);
}



void  printPrintStat(print p)
{
	printf("cout ");

	for (unsigned i = 0; i < p.literals->len; i++)
	{
		printf(" << ");

		expression lit = g_array_index(p.literals, expression, i);

		printExpression(lit);
	}

	printf("\n");
}



void  printReturn(Return r)
{
	printf("return ");

	printExpression(r.retVal);

	printf("\n");
}



// print operator
void  printOperator(OP op)
{
	/*    ADD, SUBTRACT, NOT, LESS, GREATER, LESS_EQUAL, GREATER_EQUAL, DOUBLE_EQUAL, 
    POINTER, REF, MUT_REF, BRACKETS, NOT_EQUAL, NONE*/
	switch (op)
	{
	case ADD:
		printf(" + ");
		break;

	case SUBTRACT:
		printf(" - ");
		break;

	case NOT:
		printf("! ");
		break;

	case LESS:
		printf(" < ");
		break;

	case GREATER:
		printf(" > ");
		break;

	case LESS_EQUAL:
		printf(" <= ");
		break;

	case GREATER_EQUAL:
		printf(" >= ");
		break;

	case DOUBLE_EQUAL:
		printf(" == ");
		break;

	case POINTER:
		printf("* ");
		break;

	case MUT_REF:
		printf("mut & ");
		break;

	case REF:
		printf("& ");
		break;

	case BRACKETS:
		printf(" [] ");
		break;

	case NOT_EQUAL:
		printf(" != ");
		break;

	case NEW:
		printf(" allocate ");
		break;

	case EQUALS:
		printf(" = ");
		break;

	default:
		break;
	}
}



