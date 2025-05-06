#pragma once
/*
File: VMInstruction.c
Description: Function definitions for VMInstruction.h
*/

#include "VMInstruction.h"

#include <stdio.h>


/*
Function: executeSubscript
Description: given a memory index for the first element of the array, pop the stack to get the array index,
then, if the memory val holds an int, add sub.varIndex to the popped index,
if an unsigned or pointer value, add the popped value to that value,
push the resulting value onto the stack
*/
void  executeSubscript(subscriptI  sub, GArray* dataStack, GArray* localMem)
{
	// pop stack to get array index
	datum aIndex = popStack(dataStack);

	if (aIndex.type != STACK_INT)
	{
		printf("bad array index");

		exit(1);
	}

	// get the int val
	int  arrayIndex = aIndex.value.num;

	// now check data type of sub.index in memory
	memVal mv = g_array_index(localMem, memVal, sub.varIndex);

	datum resultAddress;

	//if the memory val holds an int, add sub.varIndex to the popped index,
	if (mv.type == MEM_INT)
	{
		int  resultInt = sub.varIndex + arrayIndex;

		resultAddress.type = STACK_INDEX;

		resultAddress.value.index = resultInt;
	}

	// pointer value, add the popped value to that value,
	else if (mv.type == MEM_POINTER)
	{
		// get pointer
		int* ptr = mv.val.heapPtr;

		if (!ptr)
		{
			printf("bad pointer\n");

			exit(1);
		}

		// add index
		int* resultPtr = ptr + arrayIndex;

		resultAddress.type = STACK_PTR;

		resultAddress.value.ptr = resultPtr;
	}

	else if (mv.type == MEM_REF)
	{
		int  refIndex = mv.val.index;

		int  resultIndex = refIndex + arrayIndex;

		resultAddress.type = STACK_INDEX;

		resultAddress.value.index = resultIndex;
	}

	else
	{
		printf("bad memval\n");

		exit(1);
	}

	// push the value onto the stack
	pushStack(dataStack, resultAddress);
} // end executeSubscript




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
Description: pops a value off the stack,
if it's memory index, gets the value there and pushes it onto the data stack,
if a pointer, get the value at that memory location and push it
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

	if (d.type == STACK_STRING)
	{
		printf("bad memory lookup");

		exit(1);
	}

	// if the stack top is a heap address, get the value at that address
	else if (d.type == STACK_PTR)
	{
		int* ptr = d.value.ptr;

		if (!ptr)
		{
			printf("bad memory access\n");

			exit(1);
		}

		int  newVal = *ptr;

		datum newHeapVal = initIntDat(newVal);

		pushStack(dataStack, newHeapVal);
	}

	else
	{
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
	}


} // end executeMovFromStackIndex



/*
Function: executeMovToStackIndex
Description: pops the memory index off the data stack, pops the data stack again and moves that value to
memory index
*/
void  executeMovToStackIndex(int index, GArray* dataStack, GArray* localMem)
{
	// pop the index off top of stack
	// need to check if it's a memory address or a heap address
	datum d = popStack(dataStack);

	// get the value to move off the stack top
	datum dVal = popStack(dataStack);

	// if the top is a pointer, move the data into it
	if (d.type == STACK_PTR)
	{
		// get the address
		int* ptr = d.value.ptr;

		if (!ptr)
		{
			printf("bad stack access pointer\n");

			exit(1);
		}

		// get the value to send to address
		int  newVal = dVal.value.num;

		// add the value
		*ptr = newVal;
	}

	// otherwise, create a new memval with data and move it to index
	else
	{
		unsigned  newIndex = d.value.index;

		if (newIndex < 0 || newIndex >= localMem->len)
		{
			printf("bad local mem index\n");

			exit(1);
		}

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
	}

} // end executeMovToStackIndex



/*
Function: executeMovToHeap
Description: pops the value off the data stack and moves it to the address stored in memory INDEX
*/
void  executeMovToHeap(int index, GArray* dataStack, GArray* localMem)
{
	// pop stack
	datum d = popStack(dataStack);

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
Description: gets the value stored at the address/mem location in memory INDEX and pushes it onto the stack
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

	int  newVal;

	// if the location holds a pointer...
	if (mv.type == MEM_POINTER)
	{
		// get the pointer
		int* ptr = mv.val.heapPtr;

		if (!ptr)
		{
			printf("bad local memory access pointer\n");

			exit(1);
		}

		// get the value pointed to
		newVal = *ptr;
	}

	// if it contains an index...
	else if (mv.type == MEM_REF)
	{
		int  refIndex = mv.val.index;

		// get the memval at that index
		if (refIndex < 0 || refIndex >= localMem->len)
		{
			printf("bad local mem index\n");

			exit(1);
		}

		memVal mv = g_array_index(localMem, memVal, refIndex);

		if (mv.type != MEM_INT)
		{
			printf("can only reference integer types\n");

			exit(1);
		}

		// assign the value
		newVal = mv.val.intVal;
	}

	else
	{
		printf("trying to access heap with non pointer\n");

		exit(1);
	}

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

	else if (stor.type == STORE_PTR)
	{
		int* ptr = stor.value.ptr;

		if (!ptr)
		{
			printf("bad stor pointer\n");

			exit(1);
		}

		d.type = STACK_PTR;

		d.value.ptr = ptr;
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



/*
Function: executeAdd
Description: pop two numbers off the stack, add them, and push the result on the stack
*/
void  executeAdd(GArray* dataStack)
{
	// get the two operands off the stack
	datum a = popStack(dataStack);

	datum b = popStack(dataStack);

	datum resultDatum;

	if (a.type == STACK_PTR)
	{
		int* aPtr = a.value.ptr;

		if (!aPtr)
		{
			printf("bad pointer\n");

			exit(1);
		}

		if (b.type == STACK_PTR)
		{
			printf("cannot add two pointers\n");

			exit(1);
		}

		// add an integer to a pointer
		else if (b.type == STACK_INT)
		{
			int  bInt = b.value.num;

			int* resultPtr = aPtr + bInt;

			resultDatum.type = STACK_PTR;

			resultDatum.value.ptr = resultPtr;
		}

		// add unsigned to a pointer
		else if (b.type == STACK_INDEX)
		{
			int  bIndex = b.value.index;

			int* resultPtr = aPtr + bIndex;

			resultDatum.type = STACK_PTR;

			resultDatum.value.ptr = resultPtr;
		}

		else
		{
			printf("cannot add current stack val\n");

			exit(1);
		}
	}

	else if (a.type == STACK_INT)
	{
		int aInt = a.value.num;

		// add int to a pointer
		if (b.type == STACK_PTR)
		{
			int* bPtr = b.value.ptr;

			if (!bPtr)
			{
				printf("bad pointer addition\n");

				exit(1);
			}

			int* resultPtr = bPtr + aInt;

			resultDatum.type = STACK_PTR;

			resultDatum.value.ptr = resultPtr;
		}

		// add two ints
		else if (b.type == STACK_INT)
		{
			int  bInt = b.value.num;

			int  resultInt = aInt + bInt;

			resultDatum.type = STACK_INT;

			resultDatum.value.num = resultInt;
		}

		// add unsigned + int to get an int
		else if (b.type == STACK_INDEX)
		{
			unsigned  bIndex = b.value.num;

			int  resultInt = aInt + bIndex;

			resultDatum.type = STACK_INT;

			resultDatum.value.num = resultInt;
		}

		else
		{
			printf("cannot add current stack val\n");

			exit(1);
		}
	}

	else if (a.type == STACK_INDEX)
	{
		unsigned aIndex = a.value.index;

		// add unsigned to pointer
		if (b.type = STACK_PTR)
		{
			int* bPtr = b.value.ptr;

			if (!bPtr)
			{
				printf("bad pointer addition\n");

				exit(1);
			}

			int* resultPtr = bPtr + aIndex;

			resultDatum.type = STACK_PTR;

			resultDatum.value.ptr = resultPtr;
		}

		// add unsigned to int to get an int
		else if (b.type == STACK_INT)
		{
			int  bInt = b.value.num;

			int  resultInt = aIndex + bInt;

			resultDatum.type = STACK_INT;

			resultDatum.value.num = resultInt;
		}

		// add unsigned + unsigned
		else if (b.type == STACK_INDEX)
		{
			unsigned bIndex = b.value.index;

			unsigned resultIndex = aIndex + bIndex;

			resultDatum.type = STACK_INDEX;

			resultDatum.value.index = resultIndex;
		}

		else
		{
			printf("cannot add current stack val\n");

			exit(1);
		}
	}

	else
	{
		printf("cannot add current stack val\n");

		exit(1);
	}

	// push the result onto the stack
	pushStack(dataStack, resultDatum);
} // end executeAdd



/*
Function: executeSubtract
Description: pop two values, subtract them and push result
*/
void  executeSubtract(GArray* dataStack)
{
	// get the two operands off the stack
	datum right = popStack(dataStack);

	datum left = popStack(dataStack);

	datum resultDatum;

	if (right.type == STACK_PTR)
	{
		int* rightPtr = right.value.ptr;

		if (!rightPtr)
		{
			printf("bad pointer\n");

			exit(1);
		}

		// subtract two pointers
		if (left.type == STACK_PTR)
		{
			printf("cannot subtract two pointers\n");
			
			exit(1);
		}

		// subtract an integer from a pointer
		else if (left.type == STACK_INT)
		{
			printf("can't subtract a pointer from an int\n");

			exit(1);
		}

		// add unsigned to a pointer
		else if (left.type == STACK_INDEX)
		{
			printf("can't subtract a pointer from an int\n");

			exit(1);
		}

		else
		{
			printf("cannot add current stack val\n");

			exit(1);
		}
	}

	else if (right.type == STACK_INT)
	{
		int rightInt = right.value.num;

		// subtract int from pointer
		if (left.type == STACK_PTR)
		{
			int* leftPtr = left.value.ptr;

			if (!leftPtr)
			{
				printf("bad pointer addition\n");

				exit(1);
			}

			int* resultPtr = leftPtr - rightInt;

			resultDatum.type = STACK_PTR;

			resultDatum.value.ptr = resultPtr;
		}

		// subtract two ints
		else if (left.type == STACK_INT)
		{
			int  leftInt = left.value.num;

			int  resultInt = leftInt - rightInt;

			resultDatum.type = STACK_INT;

			resultDatum.value.num = resultInt;
		}

		// subtract int from unsigned
		else if (left.type == STACK_INDEX)
		{
			printf("can't subtract int from unsigned\n");

			exit(1);
		}

		else
		{
			printf("cannot add current stack val\n");

			exit(1);
		}
	}

	else if (right.type == STACK_INDEX)
	{
		unsigned rightIndex = right.value.index;

		// subtract unsigned from ptr
		if (left.type = STACK_PTR)
		{
			int* leftPtr = left.value.ptr;

			if (!leftPtr)
			{
				printf("bad pointer addition\n");

				exit(1);
			}

			int* resultPtr = leftPtr - rightIndex;

			resultDatum.type = STACK_PTR;

			resultDatum.value.ptr = resultPtr;
		}

		// subtract unsigned from int
		else if (left.type == STACK_INT)
		{
			int  leftInt = left.value.num;

			int  resultInt = leftInt - rightIndex;

			resultDatum.type = STACK_INT;

			resultDatum.value.num = resultInt;
		}

		// subtract two unsigned
		else if (left.type == STACK_INDEX)
		{
			printf("cannot subtract two unsigned values\n");

			exit(1);
		}

		else
		{
			printf("cannot add current stack val\n");

			exit(1);
		}
	}

	else
	{
		printf("cannot add current stack val\n");

		exit(1);
	}

	// push the result onto the stack
	pushStack(dataStack, resultDatum);
} // end executeSubtract



/*
Function: executeLess
Description: pop the two operands, if a < b, push 0, 1 otherwise
*/
void  executeLess(GArray* dataStack)
{
	// pop the two operands
	datum right = popStack(dataStack);

	datum left = popStack(dataStack);

	int result;

	if (!(right.type == STACK_INT && left.type == STACK_INT))
	{
		printf("bad data types for comparison operator\n");

		exit(1);
	}

	int  rightInt = right.value.num;

	int  leftInt = left.value.num;

	// push 0 for true and 1 for false
	if (leftInt < rightInt)
		result = 0;
	else
		result = 1;

	datum resDat = initIntDat(result);

	pushStack(dataStack, resDat);
} // end executeLess



void  executeLessEqual(GArray* dataStack)
{
	// pop the two operands
	datum right = popStack(dataStack);

	datum left = popStack(dataStack);

	int result;

	if (!(right.type == STACK_INT && left.type == STACK_INT))
	{
		printf("bad data types for comparison operator\n");

		exit(1);
	}

	int  rightInt = right.value.num;

	int  leftInt = left.value.num;

	// push 0 for true and 1 for false
	if (leftInt <= rightInt)
		result = 0;
	else
		result = 1;

	datum resDat = initIntDat(result);

	pushStack(dataStack, resDat);
}



void executeGreater(GArray* dataStack)
{
	// pop the two operands
	datum right = popStack(dataStack);

	datum left = popStack(dataStack);

	int result;

	if (!(right.type == STACK_INT && left.type == STACK_INT))
	{
		printf("bad data types for comparison operator\n");

		exit(1);
	}

	int  rightInt = right.value.num;

	int  leftInt = left.value.num;

	// push 0 for true and 1 for false
	if (leftInt > rightInt)
		result = 0;
	else
		result = 1;

	datum resDat = initIntDat(result);

	pushStack(dataStack, resDat);
}



void  executeGreaterEqual(GArray* dataStack)
{
	// pop the two operands
	datum right = popStack(dataStack);

	datum left = popStack(dataStack);

	int result;

	if (!(right.type == STACK_INT && left.type == STACK_INT))
	{
		printf("bad data types for comparison operator\n");

		exit(1);
	}

	int  rightInt = right.value.num;

	int  leftInt = left.value.num;

	// push 0 for true and 1 for false
	if (leftInt >= rightInt)
		result = 0;
	else
		result = 1;

	datum resDat = initIntDat(result);

	pushStack(dataStack, resDat);
}



void  executeDoubleEqual(GArray* dataStack)
{
	// pop the two operands
	datum right = popStack(dataStack);

	datum left = popStack(dataStack);

	int result;

	if (!(right.type == STACK_INT && left.type == STACK_INT))
	{
		printf("bad data types for comparison operator\n");

		exit(1);
	}

	int  rightInt = right.value.num;

	int  leftInt = left.value.num;

	// push 0 for true and 1 for false
	if (leftInt == rightInt)
		result = 0;
	else
		result = 1;

	datum resDat = initIntDat(result);

	pushStack(dataStack, resDat);
}



void  executeNotEqual(GArray* dataStack)
{
	// pop the two operands
	datum right = popStack(dataStack);

	datum left = popStack(dataStack);

	int result;

	if (!(right.type == STACK_INT && left.type == STACK_INT))
	{
		printf("bad data types for comparison operator\n");

		exit(1);
	}

	int  rightInt = right.value.num;

	int  leftInt = left.value.num;

	// push 0 for true and 1 for false
	if (leftInt != rightInt)
		result = 0;
	else
		result = 1;

	datum resDat = initIntDat(result);

	pushStack(dataStack, resDat);
}



/*
Function: executeNot
Description: pop the stack, if the value is 1, change it to 0 and vice versa
*/
void  executeNot(GArray* dataStack)
{
	// pop stack
	datum d = popStack(dataStack);

	// check value
	if (d.type != STACK_INT)
	{
		printf("bad data types for not operator\n");

		exit(1);
	}

	int val = d.value.num;

	if (!(val == 0 || val == 1))
	{
		printf("can only negate 0 or 1\n");

		exit(1);
	}

	int  result;

	// flip the value
	if (val == 0)
		result = 1;
	// val == 1
	else
		result = 0;

	datum notDat = initIntDat(result);

	// push it onto the stack
	pushStack(dataStack, notDat);
}



/*
Function: executeCall
Description: first, pop the argument val off the stack, then get local memory from functions array, then
set the paramemter (index 0) to val.
push the frame pointer and the program counter onto the stack, then get the function location from the
jump hash table and set the pc, also set the fp to the function index
*/
void  executeCall(callI c, GArray* dataStack, int* pc, int* fp, GHashTable* jumpLabels, GArray*  functions)
{

	// get the local memory for the called function
	if (c.funcIndex >= functions->len || c.funcIndex < 0)
	{
		printf("bad fp\n");

		exit(1);
	}

	function  currentFunc = g_array_index(functions, function, c.funcIndex);

	// of type memVal
	GArray* localMem = currentFunc.symbols;

	if (!localMem)
	{
		printf("bad memory\n");

		exit(1);
	}

	// set localMem[0] which is the parameter to stack top (argument), use executeMovToMem
	executeMovToMem(0, dataStack, localMem);



	// push the frame pointer and pc + 1
	datum fpDat = initIntDat(*fp);

	datum pcDat = initIntDat((*pc) + 1);

	pushStack(dataStack, fpDat);

	pushStack(dataStack, pcDat);

	// set the frame pointer to the new function index

	*fp = c.funcIndex;

	// lookup the function call label
	gpointer val = g_hash_table_lookup(jumpLabels, c.label->str);

	// check the pointer
	if (!val)
	{
		printf("bad hash lookup\n");

		exit(1);
	}

	// convert to integer
	int  newPc = GPOINTER_TO_INT(val);

	// check new pc
	if (newPc < 0)
	{
		printf("bad instruction index\n");

		exit(1);
	}

	// set the pc
	*pc = newPc;
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



/*
Function: executeJump
Description: lookup the jump label and get the new pc and set it
*/
void  executeJump(jumpI  j, int* pc, GHashTable* jumpLabels)
{
	if (!pc)
	{
		printf("bad pc\n");

		exit(1);
	}

	// get the value paired with the jump label
	gpointer val = g_hash_table_lookup(jumpLabels, j.jumpLabel->str);

	if (!val)
	{
		printf("bad hash lookup\n");

		exit(1);
	}

	// convert to integer
	int  newPc = GPOINTER_TO_INT(val);

	if (newPc < 0)
	{
		printf("bad instruction index\n");

		exit(1);
	}

	// set the pc
	*pc = newPc;
} // end executeJump



/*
Function: executeJumpNotZero
Description: pop the stack, if 0 (true) - just increment pc, if 1(false) - jump to the location at jnz.jumpLabel
*/
void  executeJumpNotZero(jumpNotZeroI jnz, GArray* dataStack, int* pc, GHashTable* jumpLabels)
{
	if (!pc)
	{
		printf("bad pc\n");

		exit(1);
	}

	datum d = popStack(dataStack);

	if (d.type != STACK_INT)
	{
		printf("bad stack top\n");

		exit(1);
	}

	int test = d.value.num;

	if (!(test == 0 || test == 1))
	{
		printf("need 0 or 1 to jump\n");

		exit(1);
	}

	// if true, just increment pc
	if (test == 0)
	{
		int currentPc = *pc;

		currentPc++;

		*pc = currentPc;
	}

	// otherwise false, jump
	else
	{
		// get the value paired with the jump label
		gpointer val = g_hash_table_lookup(jumpLabels, jnz.jumpLabel->str);

		if (!val)
		{
			printf("bad hash lookup\n");

			exit(1);
		}

		// convert to integer
		int  newPc = GPOINTER_TO_INT(val);

		if (newPc < 0)
		{
			printf("bad instruction index\n");

			exit(1);
		}

		// set the pc
		*pc = newPc;
	}
} // end executeJumpNotZero



/*
Function: executeAllocate
Description: make an a.size heap allocation using malloc, then move the pointer into a.varIndex
*/
void  executeAllocate(allocI a, GArray* localMem)
{
	// make the a.size heap allocation
	int* ptr = (int*)malloc(a.size * sizeof(int));

	if (!ptr)
	{
		printf("bad heap allocation\n");

		exit(1);
	}

	// store the pointer in a.varIndex
	memVal newVal = makePtrMemVal(ptr);

	if (a.varIndex < 0 || a.varIndex >= localMem->len)
	{
		printf("bad local mem index\n");

		exit(1);
	}

	g_array_index(localMem, memVal, a.varIndex) = newVal;
} // end executeAllocate




/*
Function: executeFree
Description: Free the pointer at localMem[f.varIndex]
*/
void  executeFree(freeI  f, GArray* localMem)
{
	// check index
	if (f.varIndex < 0 || f.varIndex >= localMem->len)
	{
		printf("bad local mem index\n");

		exit(1);
	}

	// get pointer at localMem[f.varIndex]
	memVal val = g_array_index(localMem, memVal, f.varIndex);

	if (val.type != MEM_POINTER)
	{
		printf("can't free non pointers\n");

		exit(1);
	}

	int* ptr = val.val.heapPtr;

	if (!ptr)
	{
		printf("bad free\n");

		exit(1);
	}

	else
	{
		free(ptr);
	}
} // end executeFree




/*
Function: executeRef
Description: creates a pointer to ref.varIndex's data and pushes it onto the stack.
If var is a pointer, just copy the pointer. 
Otherwise, push varIndex onto the stack.
*/
void  executeRef(refI  ref, GArray* localMem, GArray* dataStack)
{
	// get the memval at ref.index
	// check index
	int  varIndex = ref.rhsVarIndex;

	if (varIndex < 0 || varIndex >= localMem->len)
	{
		printf("bad mem index\n");

		exit(1);
	}

	memVal mv = g_array_index(localMem, memVal, varIndex);

	datum d;

	// check the vals type
	// if a pointer, make and new pointer and copy the address
	if (mv.type == MEM_POINTER)
	{
		// get the pointer to copy
		int* oldPtr = mv.val.heapPtr;

		if (!oldPtr)
		{
			printf("bad pointer\n");

			exit(1);
		}

		// make the copy
		int* newPtr = oldPtr;

		if (!newPtr)
		{
			printf("bad pointer\n");

			exit(1);
		}

		d.type = STACK_PTR;

		d.value.ptr = newPtr;
	}

	// Otherwise, we push the index of the rhs var on the stack
	else if (mv.type == STACK_INT)
	{
		d.type = STACK_INDEX;

		d.value.index = varIndex;
	}

	else
	{
		printf("bad reference data type\n");
	}

	// push value onto the stack
	pushStack(dataStack, d);

} // end executeRef











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

	case REF_I:
		printRefI(i.values.ref);
		break;

	case SUBSCRIPT_I:
		printSubscriptI(i.values.subscript);
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
