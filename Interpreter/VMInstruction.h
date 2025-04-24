#pragma once
/*
File: VMInstruction.h
Description: Contains the struct definitions and helper method declarations for the VM instruction type
*/
#include "VMInput.h"
#include <stdio.h>


// enum: INSTRUCTION_TYPE
typedef enum
{
    // moving and storing values
    MOVE_I, STORE_I,
    // arithmetic operations
    ADD_I, SUBTRACT_I, 
    // conditional operations
    LESS_I, LESS_EQUAL_I, GREATER_I, GREATER_EQUAL_I, DOUBLE_EQUALS_I, NOT_EQUAL_I, 
    NOT_I,
    // changing functions
    CALL_I, RETURN_I, PRINT_I,
    // jumps
    JUMP_I, JUMP_NOT_ZERO_I,
    // heap memory actions
    ALLOCATE_I, FREE_I

} INSTRUCTION_TYPE;


/*
Move types:
MOV_TO_STACK: gets the value at memory INDEX and pushes onto the data stack
MOV_TO_MEM: pops the value off the data stack and moves it to the memory INDEX
MOV_FROM_STACK_INDEX: pops the memory index off the data stack, gets the value there and pushes it onto the data stack
MOV_TO_STACK_INDEX: pops the memory index off the data stack, pops the data stack again and moves that value to
memory index
MOV_TO_HEAP: pops the value off the data stack and moves it to the address stored in memory INDEX
MOV_FROM_HEAP: gets the value stored at the address in memory INDEX and pushes it onto the stack
MOV_STACK_TO_HEAP: pops the heap address off the data stack, pops the data stack again and moves that value to
that address
*/
typedef enum
{
    MOV_TO_STACK, MOV_TO_MEM, MOV_FROM_STACK_INDEX, MOV_TO_HEAP, MOV_TO_STACK_INDEX, MOV_FROM_HEAP,
    MOV_STACK_TO_HEAP
} MOV_TYPE;


// types of labels for jumping
typedef enum
{
    FUNCTION_DONE, IF_LABEL, ELIF_LABEL, ELSE_LABEL
} LABEL_TYPE;


typedef enum
{
    STORE_INT, STORE_STRING, STORE_INDEX
} STORE_TYPE;


typedef struct
{
    LABEL_TYPE type;

    int  jumpTableIndex;
} jumpLabel;


typedef struct
{
    GString* jumpLabel;
} jumpI;



typedef struct
{
    GString* jumpLabel;
} jumpNotZeroI;


// push an int onto the data stack
typedef struct
{
    STORE_TYPE type;

    union
    {
        int  intVal;

        GString* str;

        unsigned index;
    } value;
} storeI;



typedef struct
{
    GString* label;
} callI;


// move an int from memory at index to the stack or move an int from the data stack to memory at index
// MOV_FROM_STACK_INDEX gets the memory index from the top of the stack and then pushes the value there back on the stack
typedef struct
{
    MOV_TYPE type;

    int  index;
} movI;


typedef struct
{
    int varIndex;

    size_t size;
} allocI;



typedef struct
{
    int varIndex;
} freeI;


typedef struct
{
    int  numLiterals;
} printI;



// union: operands
typedef union
{
    jumpI    jump;

    jumpNotZeroI   jnz;

    storeI  store;

    callI call;

    movI  mov;

    allocI alloc;

    freeI  Free;

    printI  pr;

    int  nill;

} operands;


// struct: instruction
typedef struct
{
    INSTRUCTION_TYPE type;

    operands   values;

} instruction;



// FUNCTION DECLARATIONS
// create an init_ function for each instruction.operands type
inline instruction  initJumpI(jumpI j) { instruction i; i.type = JUMP_I; i.values.jump = j; return i; }

inline instruction  initJumpNotZeroI(jumpNotZeroI jnz) { instruction i;
i.type = JUMP_NOT_ZERO_I; i.values.jnz = jnz; return i; }

inline instruction  initStoreI(storeI s) { instruction i; i.type = STORE_I; i.values.store = s; return i; }

inline instruction  initCallI(callI  c) { instruction i; i.type = CALL_I; i.values.call = c; return i; }

inline instruction  initMovI(movI  m) { instruction i; i.type = MOVE_I; i.values.mov = m; return i; }

inline instruction  initAllocI(allocI  a) { instruction i; i.type = ALLOCATE_I; i.values.alloc = a; return i; }

inline instruction  initFreeI(freeI  f) { instruction i; i.type = FREE_I; i.values.Free = f; return i; }

inline instruction  initPrintI(printI p) { instruction i; i.type = PRINT_I; i.values.pr = p; return i; };

// initialize an instruction that doesn't have operands, just an operator
inline instruction initInstructionNoOperands(INSTRUCTION_TYPE type) {
    instruction i;
    i.type = type;
    i.values.nill = 0;
    return i;
}


// init helpers for storeI
inline storeI  initIntStore(int val) { storeI s; s.type = STORE_INT; s.value.intVal = val; return s; }

inline storeI  initStringStore(GString* str) { storeI s; s.type = STORE_STRING; s.value.str = str; return s; }

inline storeI  initIndexStore(unsigned index) { storeI s; s.type = STORE_INDEX; s.value.index = index; return s; }

// helper functions for printing instructions
void  printInstruction(instruction i);

void printJumpI(jumpI  j);

void printJNZI(jumpNotZeroI jnz);

void  printStoreI(storeI s);

void  printCallI(callI c);

void  printMovI(movI  m);

void  printAllocI(allocI  a);

void  printFreeI(freeI f);

inline void  printPrintI(printI p) { printf("PRINT(%d) values", p.numLiterals); };

// instructions have type instruction
inline void printInstructions(GArray* instructions) {
    for (int i = (instructions->len) - 1; i >= 0; i--)
    {
        printf("Instruction %d:", i + 1);
        printInstruction(g_array_index(instructions, instruction, i));
    }
}





// get methods for each instruction with operands
//inline int   getJumpI(instruction i) { return i.values.jump.index; }

//inline int  getJNZ(instruction i) { return i.values.jnz.index; }

//inline int  getCallI(instruction i) { return i.values.call.funcIndex; };

inline int  getMoveI(instruction i) { return i.values.mov.index; };

//inline int   getAllocI(instruction i) { return i.values.alloc.size; };

inline int   getFreeI(instruction i) { return i.values.Free.varIndex; };

inline int   getPrintI(instruction i) { return i.values.pr.numLiterals;  }



// get store types
inline int   getIntStore(storeI  s) { return s.value.intVal;}

inline GString*   getStringStore(storeI  s) { return s.value.str; }

inline  STORE_TYPE  getStoreType(storeI s) { return s.type;}