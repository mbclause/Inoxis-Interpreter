/*
File: VirtualMachine.c
Description: Contains all function definitions for VirtualMachine.h
*/

#pragma once
#include "VirtualMachine.h"


inline void destroy_gstring(gpointer data) {
	g_string_free((GString*)data, TRUE);
}



/*
Function: popStack
Description: If the data stack is not empty, get the top element, remove it from the stack, and return it.
Otherwise report error.
*/
datum  popStack(GArray* dataStack)
{
	if (dataStack)
	{
		datum d = g_array_index(dataStack, datum, dataStack->len - 1);

		g_array_remove_index(dataStack, dataStack->len - 1);

		return d;
	}

	else
	{
		printf("tried to pop empty stack\n");

		exit(1);
	}
}




/*
Function: compileExpression
Description: call the appropriate compile function depending on the expression type
*/
void  compileExpression(expression e, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations)
{
	// EXPR_BIN, EXPR_LIT, EXPR_UNARY, EXPR_CALL, EXPR_NONE
	switch (e.kind)
	{
	case EXPR_BIN:
		compileBinary(e.val.binaryOp, instructions, jumpLabels, functionLocations);
		break;

	case EXPR_LIT:
		compileLiteral(e.val.litVal, instructions);
		break;

	case EXPR_UNARY:
		compileUnary(e.val.unary, instructions, jumpLabels, functionLocations);
		break;

	case EXPR_CALL:
		compileFuncCall(e.val.call, instructions, jumpLabels, functionLocations);

	default:
		break;
	}
} // end compileExpression



/*
Function: compileLiteral
Description: Depending on the literal type, either store a string or int on the data stack or move a value from 
memory to the data stack
*/
void  compileLiteral(literal l, GArray* instructions)
{
	// get the literal type
	// STRING_LIT, NUMBER_LIT, VARIABLE_LIT
	// string literal - store a string on top of the data stack
	// STORE_INT, STORE_STRING
	if (l.kind == STRING_LIT)
	{
		// make the store instruction
		storeI  newStore;

		newStore.type = STORE_STRING;

		newStore.value.str = l.val.string;

		instruction newI = initStoreI(newStore);

		// push the instruction
		g_array_append_val(instructions, newI);
	}

	// if it's a number, store the number on the data stack
	else if (l.kind == NUMBER_LIT)
	{
		// make the store instruction
		storeI  newStore;

		newStore.type = STORE_INT;

		newStore.value.intVal = l.val.number;

		instruction newI = initStoreI(newStore);

		// push the instruction
		g_array_append_val(instructions, newI);
	}


	// if it's a variable, move it's value from memory to the data stack
	// MOV_TO_STACK, MOV_TO_MEM
	else
	{
		//printf("in compile variable literal \n");

		movI  newMove = { MOV_TO_STACK, l.val.varIndex };

		instruction newI = initMovI(newMove);

		// push the instruction
		g_array_append_val(instructions, newI);
	}
}




/*
Function: compileUnary
Description: push the correct instructions for the unary operator
*/
void  compileUnary(unaryOp uo, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations)
{
	/*
	unary Expression operators:
	"*" var- dereference, go to the address stored in var's memory location, mov that data onto the stack

	& var- address, mov the memory index of var onto the stack

	MUT_REF - same as &

	not - just compile the condition and  push the not instruction
	*/

	//for pointer/ref, don't compile the expression, we need to get the index of the variable,
	// then we move whatever that variable is pointing to onto the data stack
	if (uo.op == POINTER_OP)
	{
		// get var index
		int varIndex = uo.exp->val.litVal.val.varIndex;

		movI newMov = { MOV_FROM_HEAP, varIndex };

		instruction newI = initMovI(newMov);

		g_array_append_val(instructions, newI);
	}

	//&var - address, store the index of var onto the stack
	else if (uo.op == MUT_REF)
	{
		unsigned varIndex = uo.exp->val.litVal.val.varIndex;

		storeI  newStore = initIndexStore(varIndex);

		instruction newI = initStoreI(newStore);

		g_array_append_val(instructions, newI);
	}

	// get the index of var from uo.exp, then just STORE that index
	else if (uo.op == REF_OP)
	{
		unsigned varIndex = uo.exp->val.litVal.val.varIndex;

		storeI  newStore = initIndexStore(varIndex);

		instruction newI = initStoreI(newStore);

		g_array_append_val(instructions, newI);
	}

	// not operator - compile the conditional expression, then push NOT_I instruciton
	else if (uo.op == NOT)
	{
		compileExpression(*uo.exp, instructions, jumpLabels, functionLocations);

		instruction newI = initInstructionNoOperands(NOT_I);

		g_array_append_val(instructions, newI);
	}

	else
	{
		printf("bad unary expression: ");

		printUnary(uo);

		printf("\n");
	}
}



/*
Function: compileBinary
Description: compile both lhs and rhs expression, then push the appropriate instructions for the binary operator
*/
void  compileBinary(BinOp  bo, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations)
{
	compileExpression(*bo.lhs, instructions, jumpLabels, functionLocations);

	compileExpression(*bo.rhs, instructions, jumpLabels, functionLocations);

	instruction newI;

	/*
	    ADD_I, SUBTRACT_I, 
    LESS_I, LESS_EQUAL_I, GREATER_I, GREATER_EQUAL_I, DOUBLE_EQUALS_I, NOT_EQUAL_I, 
	*/
	if (bo.op == ADD)
	{
		newI = initInstructionNoOperands(ADD_I);
	}

	else if (bo.op == SUBTRACT)
	{
		newI = initInstructionNoOperands(SUBTRACT_I);
	}

	// in var[index], the lhs is the index of var and will be on the stack, under the index int val
	// we push an ADDI instruction which will add the two values to get the actual index value
	// we need to move the value at that index from memory to the stack
	else if (bo.op == BRACKETS)
	{
		// add the lhs and rhs indices on the stack
		instruction newAddI = initInstructionNoOperands(ADD_I);

		g_array_append_val(instructions, newAddI);

		// pop the memory index from data stack, get the value in that index and push it onto the data stack
		movI newMove = { MOV_FROM_STACK_INDEX, 0 };

		newI = initMovI(newMove);
	}

	else if (bo.op == LESS)
	{
		newI = initInstructionNoOperands(LESS_I);
	}

	else if (bo.op == LESS_EQUAL)
		newI = initInstructionNoOperands(LESS_EQUAL_I);

	else if (bo.op == GREATER)
		newI = initInstructionNoOperands(GREATER_I);

	else if (bo.op == GREATER_EQUAL)
		newI = initInstructionNoOperands(GREATER_EQUAL_I);

	else if (bo.op == DOUBLE_EQUAL)
		newI = initInstructionNoOperands(DOUBLE_EQUALS_I);

	else if (bo.op == NOT_EQUAL)
		newI = initInstructionNoOperands(NOT_EQUAL_I);

	else
	{
		printf("bad binary op\n");

		printBinOp(bo);

		exit(1);
	}

	g_array_append_val(instructions, newI);
}



/*
Function: compileVarDec
Description: Compile the expression on the LHS (if any), get the data type of the declared variable, then push the 
appropriate moveI instruction onto the instructions stack
*/
void  compileVarDec(varDec vd, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations)
{
	/* MovI is agnostic about data type it just moves whatever is in memory location to stack and vice versa. 

	Datum struct needs a pointer to an int in it as well. 

	For both pointers and references in an expression, we just put what's in memory onto the stack. 

	var[index] - subscript, mov the data in the var plus index memory cell onto the stack. */

	// if the declaration has an rhs, then compile it
	// the result will be on top of the data stack
	if (vd.hasRHS)
	{
		int  lhsVarIndex = vd.lhsVarIndex;

		// if the heapAlloc flag is set, then the variable is a pointer
		//If theres an allocation - push allocate instruction, which will allocate from heap and push
		//the pointer onto the stack, and push a movI from stack to mem instruction
		if (vd.heapAlloc)
		{
			// varIndex, size
			// allocate the memory from the heap and push it onto the stack
			allocI  newAlloc = { lhsVarIndex, vd.allocSize };

			instruction newI = initAllocI(newAlloc);

			// push the allocate instruction
			g_array_append_val(instructions, newI);
		}

		// otherwise compile the expression on the rhs and push the appropriate move instruction after
		else
		{
			compileExpression(vd.rhs, instructions, jumpLabels, functionLocations);

		}

		// we always move whatever's on top of the stack to the new vars memory address
		movI  newMov = { MOV_TO_MEM, lhsVarIndex };

		instruction m = initMovI(newMov);

		// push the move instruction
		g_array_append_val(instructions, m);
	}

	// we don't need to do anything if there's no rhs
} // end compileVarDec



/*
Function: compileAssign
Description: compile rhs expression, then mov value into lhs var. If lhs has subscript, we compile the index, then we
store the lhs var index on the stack, then we ADD, then we need another mov instruction that pops the mem index from 
the top of the stack and then pops the stack again and moves that value to the index
*/
void compileAssign(assign a, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations)
{
	unsigned lhsVarIndex = a.lhsIndex;

	//printf("%d\n", a.lhsDataType);

	// if there's a heap allocation, do the same as compileVarDec
	if (a.heapAlloc)
	{
		// varIndex, size
		// allocate the memory from the heap and push it onto the stack
		allocI  newAlloc = { lhsVarIndex, a.allocSize };

		instruction newI = initAllocI(newAlloc);

		// push the allocate instruction
		g_array_append_val(instructions, newI);
	}

	else
	{
		// compile the rhs
		compileExpression(a.rhs, instructions, jumpLabels, functionLocations);

		// if the lhs uses the subscript operator
		if (a.isArray)
		{
			// if the lhs is a stack array
			if (a.lhsDataType == NONE)
			{
				// compile the index, which is the rhs of the binary operation
				compileLiteral(a.lhs.val.binaryOp.rhs->val.litVal, instructions);

				//store the lhs var index on the data stack
				storeI newStore = initIntStore(lhsVarIndex);

				instruction newStoreI = initStoreI(newStore);

				g_array_append_val(instructions, newStoreI);

				// add the two values to get the actual memory index
				instruction newAdd = initInstructionNoOperands(ADD_I);

				g_array_append_val(instructions, newAdd);

				// mov the rhs value to the index on top of the stack
				movI newMov = { MOV_TO_STACK_INDEX , 0 };

				instruction newMovI = initMovI(newMov);

				g_array_append_val(instructions, newMovI);

			}

			// otherwise it's a heap array
			else if(a.lhsDataType = POINTER_OP)
			{
				// now we need to get the heap memory address stored in var and push it on the stack
				// pass compile literal the literal that's the lhs of the binary expression
				compileLiteral(a.lhs.val.binaryOp.lhs->val.litVal, instructions);

				// push the index onto the stack
				// compile the index, which is the rhs of the binary operation
				compileLiteral(a.lhs.val.binaryOp.rhs->val.litVal, instructions);

				// now we need to use pointer arithmetic to add the index to the heap pointer to get the proper address
				instruction newAdd = initInstructionNoOperands(ADD_I);

				g_array_append_val(instructions, newAdd);

				// now we need to pop the stack to get heap address, then pop the stack again and move that data
				// to address
				movI newMove = { MOV_STACK_TO_HEAP, 0 };

				instruction newI = initMovI(newMove);

				g_array_append_val(instructions, newI);

			}

			else
			{
				printf("type error\n");

				exit(1);
			}
		}

		// not an array
		else
		{
			// if the lhs uses the dereference operator, move the rhs to the address in the pointer
			if (a.lhsDataType == POINTER_OP)
			{
				movI newMov = { MOV_TO_HEAP, lhsVarIndex };

				instruction newMovI = initMovI(newMov);

				g_array_append_val(instructions, newMovI);
			}

			// otherwise pop the data stack and move the value to the lhsIndex
			else
			{
				movI newMov = { MOV_TO_MEM, lhsVarIndex };

				instruction newMovI = initMovI(newMov);

				g_array_append_val(instructions, newMovI);
			}
		}
	}


}



/*
Function: compileIfElseBlock
Description: For each block, compile the condition, then push a jnz instruction that jumps to the appropriate place.
Then compile the statements in the block.
*/
void  compileIfElseBlock(ifElseBlock cf, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations)
{
	// at the end of the statements for each block, 
	// we need an unconditional jump that goes to the end of the last block
	GString* newExitBlockLabel = g_string_new("");

	g_string_printf(newExitBlockLabel, "EXIT_IF_ELSE_BLOCK(%d)", instructions->len);

	// loop through all blocks
	for (unsigned i = 0; i < cf.ctrlFlowBlocks->len; i++)
	{
		// get the block
		statement stat = g_array_index(cf.ctrlFlowBlocks, statement, i);

		controlFlow block = stat.vals.ctrlFlowVals;

		// at the beginning of each block, we either enter it or jump to the beginning of the next block

		// case: IF
		// there's always one. 
		if (stat.statType == IF)
		{
			// at the beginning of each block, we either enter it or jump to the beginning of the next block
			GString* newIfLabel = g_string_new("");

			g_string_printf(newIfLabel, "IF(%d)", instructions->len);

			// compile the condition
			compileExpression(block.condition, instructions, jumpLabels, functionLocations);

			// add the jnz(newIfLabel)
			jumpNotZeroI jnz = { newIfLabel };

			instruction newI = initJumpNotZeroI(jnz);

			g_array_append_val(instructions, newI);

			// compile all of the statements in the block
			for (unsigned j = 0; j < block.statements->len; j++)
			{
				statement s = g_array_index(block.statements, statement, j);

				compileStatement(s, instructions, jumpLabels, functionLocations);
			}

			// add an unconditional jump to the end of the entire block
			jumpI newJump = { newExitBlockLabel };

			instruction newJumpI = initJumpI(newJump);

			g_array_append_val(instructions, newJumpI);

			// add the ifLabel to the jumpLabels hash map
			g_hash_table_insert(jumpLabels, newIfLabel, GINT_TO_POINTER(instructions->len));
		}

		else if (stat.statType == ELIF)
		{
			// at the beginning of each block, we either enter it or jump to the beginning of the next block
			GString* newElifLabel = g_string_new("");

			g_string_printf(newElifLabel, "ELIF(%d)", instructions->len);

			// compile the condition
			compileExpression(block.condition, instructions, jumpLabels, functionLocations);

			// add the jnz(newIfLabel)
			jumpNotZeroI jnz = { newElifLabel };

			instruction newI = initJumpNotZeroI(jnz);

			g_array_append_val(instructions, newI);

			// compile all of the statements in the block
			for (unsigned j = 0; j < block.statements->len; j++)
			{
				statement s = g_array_index(block.statements, statement, j);

				compileStatement(s, instructions, jumpLabels, functionLocations);
			}

			// add an unconditional jump to the end of the entire block
			jumpI newJump = { newExitBlockLabel };

			instruction newJumpI = initJumpI(newJump);

			g_array_append_val(instructions, newJumpI);

			// add the ifLabel to the jumpLabels hash map
			g_hash_table_insert(jumpLabels, newElifLabel, GINT_TO_POINTER(instructions->len));
		}

		else if (stat.statType == ELSE)
		{
			// Else - no condition,we always enter it if we arrive at it
			// we also don't need to jump to the end of the block
			
			// compile all of the statements in the block
			for (unsigned j = 0; j < block.statements->len; j++)
			{
				statement s = g_array_index(block.statements, statement, j);

				compileStatement(s, instructions, jumpLabels, functionLocations);
			}
		}

		else
		{
			printf("BAD CONTROL BLOCK\n");

			exit(1);
		}
	}

	// add the jumplable to the hash map
	g_hash_table_insert(jumpLabels, newExitBlockLabel, GINT_TO_POINTER(instructions->len));
}



/*
Function: compileWhile
Description: compile the condition, then jnz either into the block or to the end. If we enter the block, we have an
unconditional jump back to before the beginning of the conditional
*/
void   compileWhile(controlFlow cf, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations)
{
	// make the unconditional jump to the beginning of the loop
	GString* newBeginWhileLabel = g_string_new("");

	g_string_printf(newBeginWhileLabel, "BACK_TO_BEGINNING_WHILE(%d)", instructions->len);

	// add it to the hash table
	g_hash_table_insert(jumpLabels, newBeginWhileLabel, GINT_TO_POINTER(instructions->len));

	// compile the condition
	compileExpression(cf.condition, instructions, jumpLabels, functionLocations);

	// add the conditional jump instruction
	// create label
	GString* newEndWhileLabel = g_string_new("");

	g_string_printf(newEndWhileLabel, "TEST_WHILE(%d)", instructions->len);

	// add the instruction
	jumpNotZeroI jnz = { newEndWhileLabel };

	instruction newJNZ = initJumpNotZeroI(jnz);

	g_array_append_val(instructions, newJNZ);

	// now compile the statements in the block
	for (unsigned i = 0; i < cf.statements->len; i++)
	{
		statement stat = g_array_index(cf.statements, statement, i);

		compileStatement(stat, instructions, jumpLabels, functionLocations);
	}

	// add the unconditional jump to beginning of while loop
	jumpI newJump = { newBeginWhileLabel };

	instruction newJumpI = initJumpI(newJump);

	g_array_append_val(instructions, newJumpI);

	// now add the jnz label to the hash table
	g_hash_table_insert(jumpLabels, newEndWhileLabel, GINT_TO_POINTER(instructions->len));
}



/*
Function: compileFuncCall
Description: compile the argument, look up the instruction number for the beginning of the called function,
then add the call instruction to that location
*/
void  compileFuncCall(funcCall fc, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations)
{
	// compile argument
	compileExpression(*fc.arg, instructions, jumpLabels, functionLocations);

	// get instruction location for called function
	unsigned funcLocation = fc.funcIndex;

	// add a label for calling the current function, includes it's index
	GString* newFuncCallLabel = g_string_new("");

	g_string_printf(newFuncCallLabel, "CALL_FUNCTION(%d)", funcLocation);

	// add the call instruction to that location
	callI newCall = { newFuncCallLabel, funcLocation };

	instruction newI = initCallI(newCall);

	g_array_append_val(instructions, newI);
} // end compileFuncCall



/*
Function: compileReturn
Description: compile the return value and add a return instruction
*/
void  compileReturn(Return r, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations)
{
	compileExpression(r.retVal, instructions, jumpLabels, functionLocations);

	instruction newRetI = initInstructionNoOperands(RETURN_I);

	g_array_append_val(instructions, newRetI);
} // end compileReturn



/*
Function: compilePrint
Expression: compile all of the printed expressions in reverse order, then add the print(literals.len) instruction
*/
void  compilePrint(print p, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations)
{
	int numValsPrinted = p.literals->len;

	// compile the expressions in reverse order
	for (int i = p.literals->len - 1; i >= 0; i--)
	{
		expression e = g_array_index(p.literals, expression, i);

		compileExpression(e, instructions, jumpLabels, functionLocations);
	}

	// add the print instruction
	printI newPrint = { numValsPrinted };

	instruction newI = initPrintI(newPrint);

	g_array_append_val(instructions, newI);
}



/*
Function: compilFree
Description: just add a freeI instruction at the varIndex
*/
void compileFree(freeType f, GArray* instructions)
{
	freeI newFree = { f.varIndex };

	instruction newI = initFreeI(newFree);

	g_array_append_val(instructions, newI);
}



/*
Function: crashReport
Description: If we hit an error in the virtual machine, dump the top of the stack and the instruction we are on and exit program.
*/
/*void  crashReport(instruction badInstruction, int structnNum)
{
	printf("VM error at instruction %d", structnNum);

	// printInstruction

	// print stack
	printf("Stack contents: \n");

	// printStack()

	exit(1);
} // end crashReport*/



/*
Function: compileStatement
Description: use a switch statement to call the specified compile<statementType> method

Input: statement stmnt - the statement to compile
GArray* instructions - the array of instructions that will be added to during compilation of the statement
*/
void   compileStatement(statement stmnt, GArray* instructions, GHashTable* jumpLabels, GArray* functionLocations)
{
	// VAR_DEC, ASSIGN, IF, ELIF, ELSE, FUNC_CALL, PRINT, FREE, RETURN, WHILE
	switch (stmnt.statType)
	{
	case VAR_DEC:
		compileVarDec(stmnt.vals.varDecVals, instructions, jumpLabels, functionLocations);
		break;

	case ASSIGN:
		compileAssign(stmnt.vals.assignVals, instructions, jumpLabels, functionLocations);
		break;

	case IF_ELSE:
		compileIfElseBlock(stmnt.vals.ifElse, instructions, jumpLabels, functionLocations);
		break;

	case FUNC_CALL:
		compileFuncCall(stmnt.vals.call, instructions, jumpLabels, functionLocations);
		break;

	case PRINT:
		compilePrint(stmnt.vals.printVals, instructions, jumpLabels, functionLocations);
		break;

	case FREE:
		compileFree(stmnt.vals.freeVal, instructions);
		break;

	case RETURN:
		compileReturn(stmnt.vals.retVal, instructions, jumpLabels, functionLocations);
		break;

	case WHILE:
		compileWhile(stmnt.vals.ctrlFlowVals, instructions, jumpLabels, functionLocations);
		break;

	default:
		printf("bad statement");
		exit(1);
		break;
	}
}



/*
Function: compile
Description: Takes the VMInput and converts it into a GPtrArray of instructions
*/
GArray* compile(GArray* functions, GHashTable* jumpLabels)
{
	// initialize the instructions garray
	GArray* instructions = g_array_new(false, false, sizeof(instruction));

	if (instructions)
	{
		// create an array of jump labels
		//GArray* jumpLabels = g_array_new(false, false, sizeof(jumpLabel));

		// array containing the location of the first instruction for function i
		GArray* functionLocations = g_array_new(false, false, sizeof(unsigned));

		// loop through each function
		for (unsigned i = 0; i < functions->len; i++)
		{
			// get the function
			function func = g_array_index(functions, function, i);

			GString* newFuncLabel = g_string_new("");

			g_string_printf(newFuncLabel, "FUNCTION_DONE(%d)", instructions->len);

			// add a label for calling the current function, includes it's index
			GString* newFuncCallLabel = g_string_new("");

			g_string_printf(newFuncCallLabel, "CALL_FUNCTION(%d)", i);


			if (i > 0)
			{
				// add a top level guard to the function
				jumpI newJump = { newFuncLabel };

				instruction newI = initJumpI(newJump);

				g_array_append_val(instructions, newI);

				// add the call label
				g_hash_table_insert(jumpLabels, newFuncCallLabel, GINT_TO_POINTER(instructions->len));

				// now move the argument val on top of the stack into localMem[0]
				movI newMov = { MOV_TO_MEM, 0 };

				instruction  newMovI = initMovI(newMov);

				g_array_append_val(instructions, newMovI);
			}

			// add the location of the current function in instructions to the locations array
			g_array_append_val(functionLocations, instructions->len);

			// loop through all statements and compile each
			for (unsigned j = 0; j < func.statements->len; j++)
			{
				statement stat = g_array_index(func.statements, statement, j);

				compileStatement(stat, instructions, jumpLabels, functionLocations);
			}

			if (i > 0)
			{

				// add a label that points to the end of the current function in instructions
				g_hash_table_insert(jumpLabels, newFuncLabel, GINT_TO_POINTER(instructions->len));
			}
		}

		// print function instruction locations
		for (unsigned i = 0; i < functionLocations->len; i++)
		{
			//printf("Function %d starts at instruction - %d\n", i + 1, g_array_index(functionLocations, unsigned, i) + 1);
		}

		printf("LABEL TABLE\n");

		g_hash_table_foreach(jumpLabels, printLabelHashMap, NULL);

		return instructions;
	}

	else
		return NULL;

}



/*
Function: execute
Description: execute all of the instructions in the instructions array
Input: instructions = the array of instruction structs to execute
functions - the garray of function structs, need the symbols data member for each
*/
void  execute(GArray* instructions, GArray* functions, GHashTable* jumpLabels)
{
	// set up the data stack
	GArray* dataStack = g_array_new(false, false, sizeof(datum));

	// set up the frame pointer and the program counter
	int pc = 0;

	// this is the index into the functions array to get the locals memory
	int fp = 0;

	// push the location of the end of the program onto the data stack, this is where we'll return to when main ends
	// to exit the program

	datum fpd = initIntDat(fp);

	datum pcd = initIntDat(instructions->len);

	pushStack(dataStack, fpd);

	pushStack(dataStack, pcd);

	printf("\nEXECUTE\n");

	//printf("Data Stack before execution:\n");

	//printDataStack(dataStack);

	// loop through the program until we reach the end
	while (pc < instructions->len)
	{
		// execute the instruction at program counter
		instruction currentI = g_array_index(instructions, instruction, pc);

		INSTRUCTION_TYPE iType = currentI.type;

		// get the local memory for the function we are in currently
		function  currentFunc = g_array_index(functions, function, fp);

		// of type memVal
		GArray* localMem = currentFunc.symbols;

		if (!localMem)
		{
			printf("bad memory\n");

			exit(1);
		}

		//printInstruction(currentI);

		// call the appropriate execute_x function for the instruction
		switch (iType)
		{
		case MOVE_I:
			executeMovI(currentI.values.mov, dataStack, localMem);
			pc++;
			break;

		case STORE_I:
			executeStore(currentI.values.store, dataStack);
			pc++;
			break;

		case ADD_I:
			executeAdd(dataStack);
			pc++;
			break;

		case SUBTRACT_I:
			executeSubtract(dataStack);
			pc++;
			break;

		case LESS_I:
			executeLess(dataStack);
			pc++;
			break;

		case LESS_EQUAL_I:
			executeLessEqual(dataStack);
			pc++;
			break;

		case GREATER_I:
			executeGreater(dataStack);
			pc++;
			break;

		case GREATER_EQUAL_I:
			executeGreaterEqual(dataStack);
			pc++;
			break;

		case DOUBLE_EQUALS_I:
			executeDoubleEqual(dataStack);
			pc++;
			break;

		case NOT_EQUAL_I:
			executeNotEqual(dataStack);
			pc++;
			break;

		case NOT_I:
			executeNot(dataStack);
			pc++;
			break;

		case CALL_I:
			executeCall(currentI.values.call, dataStack, &pc, &fp);
			break;

		case RETURN_I:
			executeReturn(dataStack, &pc, &fp);
			break;

		case PRINT_I:
			executePrint(currentI.values.pr, dataStack);
			pc++;
			break;

		case JUMP_I:
			executeJump(currentI.values.jump, &pc);
			break;

		case JUMP_NOT_ZERO_I:
			executeJumpNotZero(currentI.values.jnz, dataStack, &pc);
			break;

		case ALLOCATE_I:
			executeAllocate(currentI.values.alloc, localMem);
			break;

		case FREE_I:
			executeFree(currentI.values.Free, localMem);
			break;

		default:
			printf("bad instruction\n");
			exit(1);
			break;
		}

		//printDataStack(dataStack);

		//printf("\n");
	}
}




/*
Function: VMMain
Description: the interface for the virtual machine, this is called by Interpreter.run() at the very end.
Calls compile() to create a GArray of instructions, which are passed to execute() and executed.

Input: functions - a g_array of function structs created by the VMInputPass
*/
bool  VMMain(GArray* functions)
{
	if (!functions)
	{
		printf("functions array is null\n");

		exit(1);
	}


	// print all of the statements
	for (unsigned i = 0; i < functions->len; i++)
	{
		// get the function
		function func = g_array_index(functions, function, i);

		if (i == 0)
			printf("Main \n");

		else
			printf("Function: %d\n", i + 1);

		if (func.statements == NULL || func.symbols == NULL)
		{
			printf("function unanitialized\n");

			exit(1);
		}

		// print the size of the locals array
		printf("Size of function locals: %d\n", func.symbols->len);

		// loop through all statements
		for (unsigned j = 0; j < func.statements->len; j++)
		{
			statement stat = g_array_index(func.statements, statement, j);

			printStatement(stat);

			printf("\n");
		}

		printf("\n");
	}

	GHashTable* jumpLabels = g_hash_table_new_full(g_str_hash, g_str_equal, destroy_gstring, NULL);


	// get the array of instructions
	GArray* instructions = compile(functions, jumpLabels);

	if (!instructions)
	{
		printf("Instructions not initialized\n");
		exit(1);

	}

	if (!jumpLabels)
	{
		exit(1);
	}

	printInstructions(instructions);

	// execute the instructions, passing the local arrays for the functions
	execute(instructions, functions, jumpLabels);

	// free the instructions
	g_array_free(instructions, true);

	

	// free the data stack

	// now we need to free all of the input memory
	freeVMInput(functions);

	// free the jumpLabels hash table
	g_hash_table_destroy(jumpLabels);

	return true;
}



