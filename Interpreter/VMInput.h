#pragma once
#include <glib.h>

union expression;

// statement types in Inoxis
enum STAT_TYPE
{
	VAR_DEC, ASSIGN, IF, ELIF, ELSE, FUNC_CALL, PRINT
};


// operators in Inoxis
enum OP
{
	ADD, SUBTRACT, NOT, LESS, GREATER, LESS_EQUAL, GREATER_EQUAL, DOUBLE_EQUAL, POINTER, REF, BRACKETS, NONE
};



// helper structs
union literal
{
	GString* string;

	int   number;

	unsigned varIndex;
};

struct unaryOp
{
	OP  op;

	expression  *exp;
};

// binary expression
struct  BinOp
{
	OP  op;

	// dynamically allocated
	expression *lhs;

	expression  *rhs;
};

struct funcCall
{
	unsigned  funcIndex;

	expression *arg;
};

union expression
{
	BinOp  binaryOp;

	literal  litVal;

	unaryOp  unary;

	funcCall  call;
};


// structs for each statement type
struct controlFlow
{
	// has type statement
	GArray*  statements;

	expression condition;
};

struct  assign
{
	expression lhs;

	expression rhs;
};

struct Return
{
	expression retVal;
};

struct freeType
{
	unsigned  varIndex;
};

struct varDec
{
	bool heapAlloc;

	size_t  allocSize;

	expression lhs;

	expression rhs;
};

struct print
{
	// has type literal
	GArray* literals;
};



// values of the statement
union values
{
	controlFlow ctrlFlowVals;
	assign   assginVals;
	print  printVals;
	varDec  varDecVals;
	freeType   freeVal;
};


// statement struct
struct  statement
{
	STAT_TYPE  statType;

	values  vals;
};

// function struct
struct function
{
	// has type statement
	GArray* statements;

	// has type int
	GArray* symbols;
};
