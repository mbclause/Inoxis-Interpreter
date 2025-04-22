#pragma once
/*
File: VMInstruction.c
Description: Function definitions for VMInstruction.h
*/

#include "VMInstruction.h"


// print instruction helper functions
void  printInstruction(instruction i)
{
	printf("Instruction - ");

	/* MOVE_I, STORE_I,ADD_I, SUBTRACT_I,LESS_I, LESS_EQUAL_I, GREATER_I, GREATER_EQUAL_I, EQUALS_I, NOT_EQUAL_I, 
    NOT_I,CALL_I, RETURN_I,  JUMP_I, JUMP_NOT_ZERO_I, ALLOCATE_I, FREE_I
	*/
	switch (i.type)
	{
	case MOVE_I:
		printMovI(i.values.mov);
		break;

	case STORE_I:
		printStoreI(i.values.store);
		break;

	case ADD_I:
		printf("ADD");
		break;

	case SUBTRACT_I:
		printf("SUBTRACT");
		break;

	case LESS_I:
		printf("LESS");
		break;

	case LESS_EQUAL_I:
		printf("LESS_EQUAL");
		break;

	case GREATER_I:
		printf("GREATER_EQUAL");
		break;

	case GREATER_EQUAL_I:
		printf("GREATER_EQUAL");
		break;

	case DOUBLE_EQUALS_I:
		printf("DOUBLE_EQUALS");
		break;

	case NOT_EQUAL_I:
		printf("NOT_EQUAL");
		break;

	case NOT_I:
		printf("NOT");
		break;

	case CALL_I:
		printCallI(i.values.call);
		break;

	case RETURN_I:
		printf("RETURN");
		break;

	case JUMP_I:
		printJumpI(i.values.jump);
		break;

	case JUMP_NOT_ZERO_I:
		printJNZI(i.values.jnz);
		break;

	case ALLOCATE_I:
		printAllocI(i.values.alloc);
		break;

	case FREE_I:
		printFreeI(i.values.Free);
		break;

	case PRINT_I:
		printPrintI(i.values.pr);
		break;

	default:
		printf("bad instruction");
		break;
	}

	printf("\n");
}



void printJumpI(jumpI  j)
{
	printf("JUMP(");

	// FUNCTION_DONE, IF, ELIF, ELSE
	switch (j.type)
	{
	case FUNCTION_DONE:
		printf("FUNCTION_DONE(%d)", j.index);
		break;

	case IF_LABEL:
		printf("IF(%d)", j.index);
		break;

	case ELIF_LABEL:
		printf("ELIF(%d)", j.index);
		break;

	case ELSE_LABEL:
		printf("ELSE(%d)", j.index);
		break;

	default:
		printf("bad jump");
		break;
	}

	printf(")");
}



void printJNZI(jumpNotZeroI jnz)
{
	printf("JUMP_IF_NOT_ZERO(");

	// FUNCTION_DONE, IF, ELIF, ELSE
	switch (jnz.type)
	{
	case FUNCTION_DONE:
		printf("FUNCTION_DONE(%d)", jnz.index);
		break;

	case IF_LABEL:
		printf("IF(%d)", jnz.index);
		break;

	case ELIF_LABEL:
		printf("ELIF(%d)", jnz.index);
		break;

	case ELSE_LABEL:
		printf("ELSE(%d)", jnz.index);
		break;

	default:
		printf("bad jump");
		break;
	}

	printf(")");
}



void  printStoreI(storeI s)
{
	if (s.type == STORE_INT)
		printf("STORE(%d)", s.value.intVal);

	else
		g_print("STORE(%s)", s.value.str);
}



void  printCallI(callI c)
{
	printf("CALL(%d)", c.funcIndex);
}



void  printMovI(movI  m)
{
	switch (m.type)
	{
	case MOV_TO_MEM:
		printf("MOVE_TO_MEM(%d)", m.index);
		break;

	case MOV_TO_STACK:
		printf("MOVE_TO_STACK(%d)", m.index);
		break;

	case MOV_FROM_STACK_INDEX:
		printf("MOV_FROM_STACK_INDEX");
		break;

	case MOV_TO_HEAP:
		printf("MOV_TO_HEAP(%d)", m.index);
		break;

	case MOV_TO_STACK_INDEX:
		printf("MOV_TO_STACK_INDEX");
		break;

	default:
		printf("bad mov");
		break;
	}
}



void  printAllocI(allocI  a)
{
	printf("ALLOC(%zd)", a.size);
}



void  printFreeI(freeI f)
{
	printf("FREE(%d)", f.varIndex);
}
