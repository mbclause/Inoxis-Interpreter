#pragma once
/*
File: VMInstruction.c
Description: Function definitions for VMInstruction.h
*/

#include "VMInstruction.h"


/*
Function: executeMovI
Description: get the move type and call the appropriate executeMov_ function
*/
void  executeMovI(movI  mov, GArray* dataStack, GArray* localMem)
{
	MOV_TYPE  type = mov.type;

	int  index = mov.index;

	switch (type)
	{
	case MOV_TO_STACK:
		executeMovToStack(index, dataStack, localMem);
		break;

	case MOV_TO_MEM:
		executeMovToMem(index, dataStack, localMem);
		break;

	case MOV_FROM_STACK_INDEX:
		executeMovFromStackIndex(index, dataStack, localMem);
		break;

	case MOV_TO_HEAP:
		executeMovToHeap(index, dataStack, localMem);
		break;

	case MOV_TO_STACK_INDEX:
		executeMovToStackIndex(index, dataStack, localMem);
		break;

	case MOV_FROM_HEAP:
		executeMovFromHeap(index, dataStack, localMem);
		break;

	case MOV_STACK_TO_HEAP:
		executeMovStackToHeap(index, dataStack, localMem);
		break;

	default:
		printf("bad move\n");
		break;
	}
} // end executeMovI



/*
Function: executeMovToStack
Description: gets the value at memory INDEX and pushes it onto the data stack
*/
void  executeMovToStack(int index, GArray* dataStack, GArray* localMem)
{
	if (localMem)
	{
		if (index >= localMem->len || index < 0)
		{
			printf("bad local mem index\n");

			exit(1);
		}

		// get the value at the indexed location
		memVal mv = g_array_index(localMem, memVal, index);

		datum d;

		// MEM_POINTER, MEM_INT, MEM_REF
		if (mv.type == MEM_POINTER)
		{
			int* ptr = getPtrMemVal(mv);

			// error
			if (ptr == NULL)
			{
				printf("bad local memory access pointer\n");

				exit(1);
			}

			d.type = STACK_PTR;

			d.value.ptr = ptr;
		}

		else if (mv.type == MEM_INT)
		{
			int  num = getIntMemVal(mv);

			d.type = STACK_INT;

			d.value.num = num;
		}

		else if (mv.type == MEM_REF)
		{
			unsigned  i = getRefMemVal(mv);

			d.type = STACK_INDEX;

			d.value.index = i;
		}

		// error
		else
		{
			printf("bad memory type\n");

			exit(1);
		}

		// push the value onto the stack
		pushStack(dataStack, d);

	}

	// error
	else
	{
		printf("no local memory\n");

		exit(1);
	}

} // end executeMovToStack



/*
Function: executeMovToMem
Description: pops the value off the data stack top and moves it to the memory INDEX
*/
void  executeMovToMem(int index, GArray* dataStack, GArray* localMem)
{

	if (index < 0 || index >= localMem->len)
	{
		printf("bad local mem index\n");

		exit(1);
	}

	datum d = popStack(dataStack);

	memVal mv;

	if (d.type == STACK_STRING)
	{
		printf("can't move strings into local memory\n");

		exit(1);
	}

	else if (d.type == STACK_INT)
	{
		int num = d.value.num;

		mv.type = MEM_INT;

		mv.val.intVal = num;
	}

	else if (d.type == STACK_PTR)
	{
		int* ptr = d.value.ptr;

		if (!ptr)
		{
			printf("bad local memory access pointer\n");

			exit(1);
		}

		mv.type = MEM_POINTER;

		mv.val.heapPtr = ptr;
	}

	else if (d.type == STACK_INDEX)
	{
		unsigned i = d.value.index;

		mv.type = MEM_REF;

		mv.val.index = i;
	}

	else
	{
		printf("bad stack data type\n");

		exit(1);
	}

	// put the popped value into memory
	g_array_index(localMem, memVal, index) = mv;


} // end executeMovToMem



/*
Function: executeMovFromStackIndex
Description: pops the memory index off the data stack, gets the value there and pushes it onto the data stack
*/
void  executeMovFromStackIndex(int index, GArray* dataStack, GArray* localMem)
{
	if (index < 0 || index >= localMem->len)
	{
		printf("bad local mem index\n");

		exit(1);
	}

	// pop the index off top of stack
	datum d = popStack(dataStack);

	if (d.type != STACK_INDEX)
	{
		printf("popped value needs to be stack_index\n");

		exit(1);
	}

	unsigned  newIndex = d.value.index;

	if (newIndex < 0 || newIndex >= localMem->len)
	{
		printf("bad local mem index\n");

		exit(1);
	}

	// get the value at the new index
	memVal mv = g_array_index(localMem, memVal, newIndex);

	datum dVal;

	// MEM_POINTER, MEM_INT, MEM_REF
	if (mv.type == MEM_POINTER)
	{
		int* ptr = getPtrMemVal(mv);

		// error
		if (ptr == NULL)
		{
			printf("bad local memory access pointer\n");

			exit(1);
		}

		dVal.type = STACK_PTR;

		dVal.value.ptr = ptr;
	}

	else if (mv.type == MEM_INT)
	{
		int  num = getIntMemVal(mv);

		dVal.type = STACK_INT;

		dVal.value.num = num;
	}

	else if (mv.type == MEM_REF)
	{
		unsigned  i = getRefMemVal(mv);

		dVal.type = STACK_INDEX;

		dVal.value.index = i;
	}

	// error
	else
	{
		printf("bad memory type\n");

		exit(1);
	}

	// push the value onto the stack
	pushStack(dataStack, dVal);

} // end executeMovFromStackIndex



/*
Function: executeMovToStackIndex
Description: pops the memory index off the data stack, pops the data stack again and moves that value to
memory index
*/
void  executeMovToStackIndex(int index, GArray* dataStack, GArray* localMem)
{
	// pop the index off top of stack
	datum d = popStack(dataStack);

	if (d.type != STACK_INDEX)
	{
		printf("popped value needs to be stack_index\n");

		exit(1);
	}

	unsigned  newIndex = d.value.index;

	if (newIndex < 0 || newIndex >= localMem->len)
	{
		printf("bad local mem index\n");

		exit(1);
	}

	// get the value to move off the stack top
	datum dVal = popStack(dataStack);

	memVal mv;

	if (dVal.type == STACK_STRING)
	{
		printf("can't move strings into local memory\n");

		exit(1);
	}

	else if (dVal.type == STACK_INT)
	{
		int num = dVal.value.num;

		mv.type = MEM_INT;

		mv.val.intVal = num;
	}

	else if (dVal.type == STACK_PTR)
	{
		int* ptr = dVal.value.ptr;

		if (!ptr)
		{
			printf("bad local memory access pointer\n");

			exit(1);
		}

		mv.type = MEM_POINTER;

		mv.val.heapPtr = ptr;
	}

	else if (dVal.type == STACK_INDEX)
	{
		unsigned i = dVal.value.index;

		mv.type = MEM_REF;

		mv.val.index = i;
	}

	else
	{
		printf("bad stack data type\n");

		exit(1);
	}

	// put the popped value into memory at the popped index
	g_array_index(localMem, memVal, newIndex) = mv;

} // end executeMovToStackIndex



/*
Function: executeMovToHeap
Description: pops the value off the data stack and moves it to the address stored in memory INDEX
*/
void  executeMovToHeap(int index, GArray* dataStack, GArray* localMem)
{
	// pop stack
	datum d = popStack(dataStack);

	if (d.type != STACK_INT)
	{
		printf("can only move ints into heap memory");

		exit(1);
	}

	if (index < 0 || index >= localMem->len)
	{
		printf("bad local mem index\n");

		exit(1);
	}

	// get the value to add at address
	int  newHeapVal = d.value.num;

	// get the heap address/pointer from local memory
	memVal mv = g_array_index(localMem, memVal, index);

	if (mv.type != MEM_POINTER)
	{
		printf("trying to access heap with non pointer\n");

		exit(1);
	}

	int* ptr = mv.val.heapPtr;

	if (!ptr)
	{
		printf("bad local memory access pointer\n");

		exit(1);
	}

	// set the heap value
	*ptr = newHeapVal;

} // end executeMovToHeap



/*
Function: executeMovFromHeap
Description: gets the value stored at the address in memory INDEX and pushes it onto the stack
*/
void  executeMovFromHeap(int index, GArray* dataStack, GArray* localMem)
{
	if (index < 0 || index >= localMem->len)
	{
		printf("bad local mem index\n");

		exit(1);
	}

	// get the memVal at index
	memVal mv = g_array_index(localMem, memVal, index);

	if (mv.type != MEM_POINTER)
	{
		printf("trying to access heap with non pointer\n");

		exit(1);
	}
	
	// get the pointer
	int* ptr = mv.val.heapPtr;

	if (!ptr)
	{
		printf("bad local memory access pointer\n");

		exit(1);
	}

	// get the value pointed to
	int newVal = *ptr;

	// push it onto the stack
	datum d = initIntDat(newVal);

	pushStack(dataStack, d);
} // end executeMovFromHeap



/*
Function: executeMovStackToHeap
Description: pops the heap address off the data stack, pops the data stack again and moves that value to
that address
*/
void  executeMovStackToHeap(int index, GArray* dataStack, GArray* localMem)
{
	// pop stack
	datum d = popStack(dataStack);

	if (d.type != STACK_PTR)
	{
		printf("trying to access heap with non pointer\n");

		exit(1);
	}

	// get the address
	int* ptr = d.value.ptr;

	if (!ptr)
	{
		printf("bad stack access pointer\n");

		exit(1);
	}

	// pop the stack again
	datum dVal = popStack(dataStack);

	if (dVal.type != STACK_INT)
	{
		printf("can only move ints into heap memory");

		exit(1);
	}

	// get the value to send to address
	int  newVal = dVal.value.num;

	// add the value
	*ptr = newVal;
} // end executeMovStackToHeap



/*
Function: executeStore
Description: Push a literal onto the data stack
*/
void  executeStore(storeI  stor, GArray* dataStack)
{
	datum d;

	// get the store value
	if (stor.type == STORE_INDEX)
	{
		unsigned index = stor.value.index;

		d.type = STACK_INDEX;

		d.value.index = index;
	}

	else if (stor.type == STORE_INT)
	{
		int num = stor.value.intVal;

		d.type = STACK_INT;

		d.value.num = num;
	}

	else if (stor.type == STORE_STRING)
	{
		GString* str = stor.value.str;

		if (!str)
		{
			printf("bad string\n");

			exit(1);
		}

		d.type = STACK_STRING;

		d.value.str = str;
	}

	else
	{
		printf("bad store\n");

		exit(1);
	}

	// push literal onto stack
	pushStack(dataStack, d);
} // end executeStore



void  executeAdd(GArray* dataStack)
{

}

void  executeSubtract(GArray* dataStack)
{

}

void  executeLess(GArray* dataStack)
{

}

void  executeLessEqual(GArray* dataStack)
{

}

void executeGreater(GArray* dataStack)
{

}

void  executeGreaterEqual(GArray* dataStack)
{

}

void  executeDoubleEqual(GArray* dataStack)
{

}

void  executeNotEqual(GArray* dataStack)
{

}

void  executeNot(GArray* dataStack)
{

}

void  executeCall(callI c, GArray* dataStack, int* pc, int* fp)
{

}



/*
Function: executeReturn
Description: It pops return value off of the data stack, restores the program counter and frame pointer,
Then it pushes the return value.
*/
void  executeReturn(GArray* dataStack, int* pc, int* fp)
{
	// get the return value
	datum retVal = popStack(dataStack);

	// get the program counter
	datum newPc = popStack(dataStack);

	if (newPc.type != STACK_INT)
	{
		printf("bad pc\n");

		exit(1);
	}

	// set program counter
	*pc = newPc.value.num;

	// get frame pointer
	datum newFp = popStack(dataStack);

	if (newPc.type != STACK_INT)
	{
		printf("bad pc\n");

		exit(1);
	}

	// set fp
	*fp = newFp.value.num;

	// push the return value onto the stack
	pushStack(dataStack, retVal);
} // end executeReturn



/*
Function: executePrint
Description: pop the stack p.numLiterals times and print each value
*/
void  executePrint(printI  p, GArray* dataStack)
{
	for (int i = 0; i < p.numLiterals; i++)
	{
		// pop the stack
		datum d = popStack(dataStack);

		// STACK_STRING, STACK_INT, STACK_PTR, STACK_INDEX
		// get the popped value and print it
		if (d.type == STACK_STRING)
		{
			GString* str = d.value.str;

			if (!str)
			{
				printf("bad string\n");

				exit(1);
			}

			g_string_replace(str, "\"", "", 0);

			g_print("%s", str->str);
		}

		else if (d.type == STACK_INT)
		{
			int num = d.value.num;

			printf("%d", num);
		}

		else if (d.type == STACK_PTR)
		{
			int* ptr = d.value.ptr;

			printf("%p", (void*)ptr);
		}

		else if (d.type == STACK_INDEX)
		{
			unsigned index = d.value.index;

			printf("%d", index);
		}

		else
		{
			printf("bad stack value\n");

			exit(1);
		}
	}
} // end executePrint



void  executeJump(jumpI  j, int* pc)
{

}

void  executeJumpNotZero(jumpNotZeroI jnz, GArray* dataStack, int* pc)
{

}

void  executeAllocate(allocI a, GArray* localMem)
{

}

void  executeFree(freeI  f, GArray* localMem)
{

}

















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
		printf("GREATER");
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
	printf("JUMP(%s)", j.jumpLabel->str);
}



void printJNZI(jumpNotZeroI jnz)
{
	printf("JUMP_IF_NOT_ZERO(%s)", jnz.jumpLabel->str);
}



void  printStoreI(storeI s)
{
	if (s.type == STORE_INT)
		printf("STORE(%d)", s.value.intVal);

	else if (s.type == STORE_INDEX)
		printf("STORE(%d)", s.value.index);

	else
		g_print("STORE(%s)", s.value.str->str);
}



void  printCallI(callI c)
{
	printf("CALL(%s)", c.label->str);
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

	case MOV_FROM_HEAP:
		printf("MOV_FROM_HEAP(%d)", m.index);
		break;

	case MOV_TO_STACK_INDEX:
		printf("MOV_TO_STACK_INDEX");
		break;

	case MOV_STACK_TO_HEAP:
		printf("MOV_STACK_TO_HEAP");
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
