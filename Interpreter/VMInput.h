#pragma once

#include <glib.h>
#include <stdbool.h>

// Forward declare
typedef struct expression expression;

// ENUMS
// OP - Operators
typedef enum 
{
    ADD, SUBTRACT, NOT, LESS, GREATER, LESS_EQUAL, GREATER_EQUAL, DOUBLE_EQUAL, 
    POINTER, REF, MUT_REF, BRACKETS, NOT_EQUAL, NEW, EQUALS, NONE

} OP;



// STAT_TYPE - Statement types
typedef enum 
{
    VAR_DEC, ASSIGN, IF, ELIF, ELSE, FUNC_CALL, PRINT, FREE, RETURN, WHILE

} STAT_TYPE;


typedef enum
{
    EXPR_BIN, EXPR_LIT, EXPR_UNARY, EXPR_CALL, EXPR_NONE
} EXPR_KIND;


typedef enum
{
    STRING_LIT, NUMBER_LIT, VARIABLE_LIT
} LIT_KIND;


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


// assign
typedef struct 
{
    bool heapAlloc;

    size_t allocSize;

    expression lhs;

    expression rhs;

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

    size_t allocSize;

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
bool freeFunction(function* func);

bool freeExpression(expression* exp);

bool freeStringLiteral(literal lit);

bool  freeMemVal(memVal mv);





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

