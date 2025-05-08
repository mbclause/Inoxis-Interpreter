/*
File: VMInput.h
Description: Contains the C language data structure definitions that will be passed as input to the virtual machine.
It also contains helper function declarations for manipulating the data structures.
*/

#pragma once

#include <glib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Forward declare
typedef struct expression expression;

// ENUMS
// OP - Operators
typedef enum 
{
    // Binary
    ADD, SUBTRACT, LESS, GREATER, LESS_EQUAL, GREATER_EQUAL, DOUBLE_EQUAL, NOT_EQUAL, BRACKETS, EQUALS,
    // unary
    NOT, POINTER_OP, REF_OP, MUT_REF, NEW, NONE

} OP;



// STAT_TYPE - Statement types
typedef enum 
{
    VAR_DEC, ASSIGN, IF, ELIF, ELSE, FUNC_CALL, PRINT, FREE, RETURN, WHILE, IF_ELSE

} STAT_TYPE;

// expression types
typedef enum
{
    EXPR_BIN, EXPR_LIT, EXPR_UNARY, EXPR_CALL, EXPR_NONE
} EXPR_KIND;

// literal types
typedef enum
{
    STRING_LIT, NUMBER_LIT, VARIABLE_LIT
} LIT_KIND;

// memory value types
typedef enum
{
    MEM_POINTER, MEM_INT, MEM_REF
} MEM_VAL;



// STRUCTS
// struct for memory
typedef struct
{
    MEM_VAL type;

    union
    {
        int* heapPtr;

        int  intVal;

        unsigned  index;
    } val;
} memVal;



// literal union - Literals
typedef struct 
{
    LIT_KIND kind;

    union
    {
        GString* string;

        int number;

        unsigned varIndex;
    } val;

} literal;



// Expressions
// unaryOp
typedef struct 
{
    OP op;

    expression* exp;

} unaryOp;


// BinOp
typedef struct 
{
    OP op;

    expression* lhs;

    expression* rhs;

} BinOp;


// funcCall
typedef struct 
{
    unsigned funcIndex;

    expression* arg;

} funcCall;


// expression
struct expression 
{
    // kind
    EXPR_KIND kind;

    // val
    union 
    {
        BinOp binaryOp;

        literal litVal;

        unaryOp unary;

        funcCall call;
    } val;
};



// Statements
// controlFlow
typedef struct 
{
    // of type statement
    GArray* statements;

    expression condition;

} controlFlow;


// struct to store all of the blocks in an if/elif/else unit
typedef struct
{
    // of type statement
    GArray* ctrlFlowBlocks;
} ifElseBlock;


// assign
typedef struct 
{
    unsigned  lhsIndex;

    bool heapAlloc;

    size_t allocSize;

    expression lhs;

    expression rhs;

    bool  isArray;

    OP lhsDataType;

} assign;


// Return
typedef struct
{
    expression retVal;

} Return;


// freeType
typedef struct 
{
    unsigned varIndex;

} freeType;


// varDec
typedef struct 
{
    bool heapAlloc;

    bool hasRHS;

    bool isStackArray;

    size_t allocSize;

    size_t  stackArraySize;

    OP  lhsDataType;

    unsigned  lhsVarIndex;

    expression lhs;

    expression rhs;

} varDec;


// print
typedef struct 
{
    // of type expression
    GArray* literals; 
} print;


// values union
typedef union 
{
    controlFlow ctrlFlowVals;

    assign assignVals;

    print printVals;

    varDec varDecVals;

    freeType freeVal;

    Return  retVal;

    funcCall  call;

    ifElseBlock  ifElse;

} values;


// statement
typedef struct 
{
    STAT_TYPE statType;

    values vals;

} statement;



// function
typedef struct 
{
    // type statement
    GArray* statements; 

    // of type memVal
    GArray* symbols; 

} function;



#ifdef __cplusplus
extern "C" {
#endif

// function declarations
// make functions for dynamically allocated structs
//makeUnaryOp
unaryOp* makeUnaryOp(OP _op, expression* _exp);

//makeBinaryOp
BinOp* makeBinOp(OP _op, expression* _lhs, expression* _rhs);

// makeFuncCall
funcCall* makeFuncCall(unsigned  index, expression* _arg);

// makeControlFlow
controlFlow* makeControlFlow(GArray* stats, expression condExp);

// makePrint
print* makePrint(GArray* literalArray);

// makeFunction
function* makeFunction(GArray* stats, GArray* syms);


// init an ifElseBlock
inline ifElseBlock  initIfElseBlock(GArray* blocks) {
    ifElseBlock newBlock = { blocks };
    return newBlock;
}


// make and init functions for memVal
memVal   initIntMemVal(int  val);

memVal   initRefMemVal(unsigned index);

memVal makePtrMemVal(int* ptr);




// corresponding free functions for each


// freeUnaryOp
bool  freeUnaryOp(unaryOp* uo);

// freeBinaryOp
bool  freeBinOp(BinOp* bo);

// freeFuncCall
bool  freeFuncCall(funcCall* _funcCall);

// freeControlFlow
bool  freeControlFlow(controlFlow* cf);

// freePrint
bool  freePrint(print* p);

// freeFunction
bool freeFunction(function func);

// free all of the VM input memory, so the garray of function structs
inline void  freeVMInput(GArray* functions) {
    if (functions)
    {
        for (unsigned i = 0; i < functions->len; i++)
        {
            freeFunction(g_array_index(functions, function, i));
        }
    }
}

bool freeExpression(expression* exp);

bool freeStringLiteral(literal lit);

bool  freeMemVal(memVal mv);

inline bool freeIfElseBlock(ifElseBlock i) {
    if (i.ctrlFlowBlocks)
        g_array_free(i.ctrlFlowBlocks, true);
}





// makeExpression and initExpression for each possible union type
expression*  makeBinOpExpression(BinOp*  bo);

expression   initBinOpExpression(BinOp* bo);

expression*  makeUnaryOpExpression(unaryOp*  uo);

expression   initUnaryOpExpression(unaryOp* uo);

expression*  makeLiteralExpression(literal  lit);

expression   initLiteralExpression(literal lit);

expression*  makeFuncCallExpression(funcCall* call);

expression  initFuncCallExpression(funcCall* call);

// initialize a pointer to an expression with another (local) expression
expression* makeExpression(expression exp);


expression  initEmptyExpression();


// init functions for complex stack based structs
// initStatement for each statement type
statement  initVarDecStatement(varDec  dec);

statement  initAssignStatement(assign  _assign);

statement  initControlFlowStatement(controlFlow  flow, STAT_TYPE controlType);

statement  initPrintStatement(print  _print);

statement  initFreeStatement(freeType  _free);

statement  initReturnStatement(Return  ret);

statement  initFuncCallStatement(funcCall* call);

inline statement initIfElseBlockStatement(ifElseBlock block) {
    statement s;

    s.statType = IF_ELSE;

    s.vals.ifElse = block;

    return s;
}


// init literal types
literal  initNumberLiteral(int num);


literal  initStringLiteral(GString* newString);


literal  initVarLiteral(unsigned  index);



// functions for printing expression and statement structs
void  printExpression(expression exp);

void  printStatement(statement stat);

// expression types
void printBinOp(BinOp bo);

void printUnary(unaryOp uo);

void PrintLiteral(literal  lit);

void printFuncCall(funcCall func);


// statement types
void printAssign(assign  a);

void printVarDec(varDec  vd);

void printControlFlow(controlFlow  cf);

void  printFree(freeType f);

void  printPrintStat(print p);

void  printReturn(Return r);

// print mem val
void  printMemVal(memVal  mv);

void  printIntMemVal(memVal  mv);

void  printPtrMemVal(memVal  mv);

void  printRefMemVal(memVal  mv);

inline void printIfElseBlock(ifElseBlock ieb) {
    for (unsigned i = 0; i < ieb.ctrlFlowBlocks->len; i++)
    {
        printStatement(g_array_index(ieb.ctrlFlowBlocks, statement, i));
    }
}


// print the operator
void  printOperator(OP op);







// get methods
// for memVal
inline int  getIntMemVal(memVal mv) { return mv.val.intVal; };

inline unsigned  getRefMemVal(memVal mv) { return mv.val.index; };

inline int* getPtrMemVal(memVal mv) {
    if (mv.val.heapPtr)
        return mv.val.heapPtr;

    else
        return NULL;
}

#ifdef __cplusplus
}
#endif

