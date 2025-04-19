/*
File: VirtualMachine.h
Description: Contains the data structs and function declarations in C for the virtual machine back-end.
*/
#pragma once

#include "VMInput.h"
#include "VMInstruction.h"


// ENUMS
// stack data type enum
typedef enum
{
	STACK_STRING, STACK_INT
} STACK_DATA_TYPE;



// DATA
// data stack will be a struct that either contains a gstring or an it
typedef struct
{
	STACK_DATA_TYPE type;

	union
	{
		GString* str;

		int  num;

	} value;
} datum;





// FUNCTION DECLARATIONS
// since this program is called by C++ code, needs these wrappers
#ifdef __cplusplus
extern "C" {
#endif

/*
	Function: VMMain
	Description: the interface for the virtual machine, this is called by Interpreter.run() at the very end.
	Calls compile() to create a GArray of instructions, which are passed to execute() and executed.

	Input: functions - a g_array of function structs created by the VMInputPass
*/
bool  VMMain(GArray* functions);

#ifdef __cplusplus
}
#endif


/*
Function: compile
Description: Takes the VMInput and converts it into a GPtrArray of instructions
*/
GArray*   compile(GArray* functions);


/*
Function: compileStatement
Description: use a switch statement to call the specified compile<statementType> method

Input: statement stmnt - the statement to compile
GArray* instructions - the array of instructions that will be added to during compilation of the statement
*/
void   compileStatement(statement stmnt, GArray* instructions);



/*
Function: crashReport
Description: If we hit an error in the virtual machine, dump the top of the stack and the instruction we are on
*/
void  crashReport(GArray* stack, instruction badInstruction, int structnNum);



/*
Function: execute
Description: execute all of the instructions in the instructions array
Input: instructions = the array of instruction structs to execute
functions - the garray of function structs, need the symbols data member for each
*/
void  execute(GArray* instructions, GArray* functions);





// compile_ functions
// VAR_DEC, ASSIGN, IF, ELIF, ELSE, FUNC_CALL, PRINT, FREE, RETURN, WHILE
void  compileVarDec(varDec vd, GArray* instructions);

void compileAssign(assign a, GArray* instructions);

void  compileIf(controlFlow cf, GArray* instructions);

void  compileElif(controlFlow cf, GArray* instructions);

void  compileFuncCall(funcCall fc, GArray* instructions);

// the index for the print function will be functions.len
// 
void  compilePrint(print p, GArray* instructions);

void compileFree(freeType f, GArray* instructions);

void  compileReturn(Return r, GArray* instructions);

void   compileWhile(controlFlow cf, GArray* instructions);




// helper functions for datum
// init
inline datum  initIntDat(int val) { datum d; d.type = STACK_INT; d.value.num = val; return d; }

inline datum  initStrDat(GString* str) { datum d; d.type = STACK_STRING; d.value.str = str; return d; }


// GET
inline int   getIntDat(datum d) { return d.value.num; }

inline GString* getStrDat(datum d) { return d.value.str; }


// PRINT
inline void  printDatum(datum d) { 
	if (d.type == STACK_INT) 
		printIntDat(d.value.num); 
	else 
		printStrDat(d.value.str); 
}

inline void  printIntDat(int val) { printf("INTVAL = %d\n", val); }

inline void  printStrDat(GString* str) { g_print("STRING = %s", str); }