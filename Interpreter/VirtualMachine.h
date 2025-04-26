/*
File: VirtualMachine.h
Description: Contains the data structs and function declarations in C for the virtual machine back-end.
*/
#pragma once
#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include "VMInput.h"
#include "VMInstruction.h"

#include <stdio.h>


// ENUMS
// stack data type enum
typedef enum
{
	STACK_STRING, STACK_INT, STACK_PTR, STACK_INDEX
} STACK_DATA_TYPE;



// DATA
// data stack will be a struct that either contains a gstring, an integer, an index into local memory (also an int),
// or a pointer to heap memory
typedef struct
{
	STACK_DATA_TYPE type;

	union
	{
		GString* str;

		int  num;

		int* ptr;

		unsigned index;

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
GArray*   compile(GArray* functions, GHashTable* jumpLabels);


/*
Function: compileStatement
Description: use a switch statement to call the specified compile<statementType> method

Input: statement stmnt - the statement to compile
GArray* instructions - the array of instructions that will be added to during compilation of the statement
*/
void   compileStatement(statement stmnt, GArray* instructions, GHashTable* jumpLabels, GArray*  functionLocations);



/*
Function: crashReport
Description: If we hit an error in the virtual machine, dump the top of the stack and the instruction we are on
*/
//void  crashReport(instruction badInstruction, int structnNum);



/*
Function: execute
Description: execute all of the instructions in the instructions array
Input: instructions = the array of instruction structs to execute
functions - the garray of function structs, need the symbols data member for each
*/
void  execute(GArray* instructions, GArray* functions, GHashTable* jumpLabels);






// compile_ functions
// compile expression functions
void  compileExpression(expression e, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations);

void  compileLiteral(literal l, GArray* instructions);

void  compileUnary(unaryOp uo, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations);

void  compileBinary(BinOp  bo, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations);


// compile statement functions
// VAR_DEC, ASSIGN, IF, ELIF, ELSE, FUNC_CALL, PRINT, FREE, RETURN, WHILE
void  compileVarDec(varDec vd, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations);

void compileAssign(assign a, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations);

void  compileIfElseBlock(ifElseBlock cf, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations);

//void  compileElif(controlFlow cf, GArray* instructions);

//void  compileElse(controlFlow cf, GArray* instructions);

void  compileFuncCall(funcCall fc, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations);

// the index for the print function will be functions.len
// 
void  compilePrint(print p, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations);

void compileFree(freeType f, GArray* instructions);

void  compileReturn(Return r, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations);

void   compileWhile(controlFlow cf, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations);




// helper functions for datum
// function to pop the top of data stack and return the value
datum  popStack(GArray* dataStack);




// init
inline datum  initIntDat(int val) { datum d; d.type = STACK_INT; d.value.num = val; return d; }

inline datum  initStrDat(GString* str) { datum d; d.type = STACK_STRING; d.value.str = str; return d; }

inline datum  initPtrDat(int* ptr) { datum d; d.type = STACK_PTR; d.value.ptr = ptr; return d; }

inline datum  initIndexDat(unsigned index) { datum d; d.type = STACK_INDEX; d.value.index = index; return d; }


// GET
inline int   getIntDat(datum d) { return d.value.num; }

inline GString* getStrDat(datum d) { return d.value.str; }

inline int* getPtrDat(datum d) { return d.value.ptr; }


// PRINT
inline void  printIntDat(int val) { printf("INTVAL = %d\n", val); }

inline void  printStrDat(GString* str) { g_print("STRING = %s\n", str->str); }

inline void  printPtrDat(int* ptr) { printf("HEAP_POINTER = %p\n", (void*)ptr); }

inline void  printIndexDat(unsigned index) { printf("MEMORY INDEX = %d\n", index); }

inline void  printDatum(datum d) { 
	if (d.type == STACK_INT)
		printIntDat(d.value.num);
	else if (d.type == STACK_PTR)
		printPtrDat(d.value.ptr);
	else if (d.type == STACK_INDEX)
		printIndexDat(d.value.index);
	else 
		printStrDat(d.value.str); 
}


// push a value on top of the stack
inline void  pushStack(GArray* dataStack, datum d) {
	g_array_append_val(dataStack, d);
}

/*
Print each datum in the data stack
*/
inline  void  printDataStack(GArray* stack) {
	if (!stack)
	{
		printf("data stack empty\n");

		return;
	}

	printf("Data Stack\n");

	for (int i = stack->len - 1; i >= 0; i--)
	{
		printf("index - %d: ", i);
		printDatum(g_array_index(stack, datum, i));
	}
}



// function to print the label hash map
inline void printLabelHashMap(gpointer key, gpointer value, gpointer user_data) {
	int  num = GPOINTER_TO_INT(value);

	const char* k = (const char*)key;

	printf("<%s, %d>\n", k, num + 1);
}

#endif