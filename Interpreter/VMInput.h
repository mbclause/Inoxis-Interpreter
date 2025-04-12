

#include <glib.h>
#include <stdbool.h>

// Forward declare
typedef struct expression expression;

// OP - Operators
typedef enum 
{
    ADD, SUBTRACT, NOT, LESS, GREATER, LESS_EQUAL, GREATER_EQUAL, DOUBLE_EQUAL, POINTER, REF, MUT_REF, BRACKETS, NONE

} OP;



// STAT_TYPE - Statement types
typedef enum 
{
    VAR_DEC, ASSIGN, IF, ELIF, ELSE, FUNC_CALL, PRINT, FREE, RETURN

} STAT_TYPE;


typedef enum
{
    EXPR_BIN, EXPR_LIT, EXPR_UNARY, EXPR_CALL
} EXPR_KIND;



// literal union - Literals
typedef union 
{
    GString* string;

    int number;

    unsigned varIndex;

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
    GArray* statements;

    expression condition;

} controlFlow;


// assign
typedef struct 
{
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

    size_t allocSize;

    expression lhs;

    expression rhs;

} varDec;


// print
typedef struct 
{
    // of type literal
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

} values;


// statement
typedef struct 
{
    enum STAT_TYPE statType;

    values vals;

} statement;



// function
typedef struct 
{
    // type statement
    GArray* statements; 

    // of type int
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





// makeExpression for each possible union type
expression*  makeBinOpExpression(BinOp*  bo);

expression*  makeUnaryOpExpression(unaryOp*  uo);

expression*  makeLiteralExpression(literal  lit);

expression*  makeFuncCallExpression(funcCall* call);


// init functions for complex stack based structs
// initStatement for each statement type
statement  initVarDecStatement(varDec  dec);

statement  initAssignStatement(assign  _assign);

statement  initControlFlowStatement(controlFlow  flow, STAT_TYPE controlType);

statement  initPrintStatement(print  _print);

statement  initFreeStatement(freeType  _free);

statement  initReturnStatement(Return  ret);

#ifdef __cplusplus
}
#endif

