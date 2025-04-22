/*
File: VirtualMachine.c
Description: Contains all function definitions for VirtualMachine.h
*/

#pragma once
#include "VirtualMachine.h"


/*
Function: compileExpression
Description: call the appropriate compile function depending on the expression type
*/
void  compileExpression(expression e, GArray* instructions)
{
	// EXPR_BIN, EXPR_LIT, EXPR_UNARY, EXPR_CALL, EXPR_NONE
	switch (e.kind)
	{
	case EXPR_BIN:
		compileBinary(e.val.binaryOp, instructions);
		break;

	case EXPR_LIT:
		compileLiteral(e.val.litVal, instructions);
		break;

	case EXPR_UNARY:
		compileUnary(e.val.unary, instructions);
		break;

	case EXPR_CALL:
		compileFuncCall(e.val.call, instructions);

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
void  compileUnary(unaryOp uo, GArray* instructions)
{
	/*
	unary Expression operators:
	"*" var- dereference, go to the address stored in var's memory location, mov that data onto the stack

	& var- address, mov the memory index of var onto the stack

	MUT_REF - same as &

	not - just compile the condition and  push the not instruction
	*/

	//for pointer/ref, don't compile the expression, we need to get the index of the variable,
	// need a dereference instruction
	if (uo.op == POINTER)
	{

	}

	else if (uo.op == MUT_REF)
	{

	}

	// get the index of var from uo.exp, then just STORE that index
	else if (uo.op == REF)
	{

	}

	// not operator - compile the conditional expression, then push NOT_I instruciton
	else if (uo.op == NOT)
	{
		compileExpression(*uo.exp, instructions);

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
void  compileBinary(BinOp  bo, GArray* instructions)
{
	compileExpression(*bo.lhs, instructions);

	compileExpression(*bo.rhs, instructions);

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
void  compileVarDec(varDec vd, GArray* instructions)
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
			compileExpression(vd.rhs, instructions);

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
void compileAssign(assign a, GArray* instructions)
{
	unsigned lhsVarIndex = a.lhsIndex;

	// if there's a heap allocation, do the same as compileVarDec
	if (a.heapAlloc)
	{
		// varIndex, size
		// allocate the memory from the heap and push it onto the stack
		allocI  newAlloc = { lhsVarIndex, a.allocSize };

		instruction newI = initAllocI(newAlloc);

		// push the allocate instruction
		g_array_append_val(instructions, newI);

		// move the pointer to the mem location
		movI  newMov = { MOV_TO_MEM, lhsVarIndex };

		instruction m = initMovI(newMov);

		// push the move instruction
		g_array_append_val(instructions, m);
	}

	else
	{
		// compile the rhs
		compileExpression(a.rhs, instructions);

		// if the lhs uses the subscript operator
		if (a.isStackArray)
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

		else
		{
			// if the lhs uses the dereference operator, move the rhs to the address in the pointer
			if (a.lhsDataType == POINTER)
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



void  compileIfElseBlock(ifElseBlock cf, GArray* instructions)
{

}



void   compileWhile(controlFlow cf, GArray* instructions)
{

}



void  compileFuncCall(funcCall fc, GArray* instructions)
{

}



void  compileReturn(Return r, GArray* instructions)
{

}



/*
Function: compilePrint
Expression: compile all of the printed expressions in reverse order, then add the print(literals.len) instruction
*/
void  compilePrint(print p, GArray* instructions)
{

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
void  crashReport(instruction badInstruction, int structnNum)
{
	printf("VM error at instruction %d", structnNum);

	// printInstruction

	// print stack
	printf("Stack contents: \n");

	// printStack()

	exit(1);
} // end crashReport



/*
Function: compileStatement
Description: use a switch statement to call the specified compile<statementType> method

Input: statement stmnt - the statement to compile
GArray* instructions - the array of instructions that will be added to during compilation of the statement
*/
void   compileStatement(statement stmnt, GArray* instructions, GArray* jumpLabels, GArray* functionLocations)
{
	// VAR_DEC, ASSIGN, IF, ELIF, ELSE, FUNC_CALL, PRINT, FREE, RETURN, WHILE
	switch (stmnt.statType)
	{
	case VAR_DEC:
		compileVarDec(stmnt.vals.varDecVals, instructions);
		break;

	case ASSIGN:
		compileAssign(stmnt.vals.assignVals, instructions);
		break;

	case IF_ELSE:
		compileIfElseBlock(stmnt.vals.ifElse, instructions);
		break;

	case FUNC_CALL:
		compileFuncCall(stmnt.vals.call, instructions);
		break;

	case PRINT:
		compilePrint(stmnt.vals.printVals, instructions);
		break;

	case FREE:
		compileFree(stmnt.vals.freeVal, instructions);
		break;

	case RETURN:
		compileReturn(stmnt.vals.retVal, instructions);
		break;

	case WHILE:
		compileWhile(stmnt.vals.ctrlFlowVals, instructions);
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
GArray* compile(GArray* functions)
{
	// initialize the instructions garray
	GArray* instructions = g_array_new(false, false, sizeof(instruction));

	if (instructions)
	{
		// create an array of jump labels
		GArray* jumpLabels = g_array_new(false, false, sizeof(jumpLabel));

		GArray* functionLocations = g_array_new(false, false, sizeof(unsigned));

		// loop through each function
		for (unsigned i = 0; i < functions->len; i++)
		{
			// get the function
			function func = g_array_index(functions, function, i);

			//GArray* locals = func.symbols;
			/*
			1. need to create a local array of jump labels, when we compile a jump, we first 
			add a label to the labels array, then we add jump(label.len).
			the jump instruction will look up the label at that location, which has the instruction index to jump to.
			*/
			if (i > 0)
			{
				// add a top level guard to the function
				jumpI newJump = { FUNCTION_DONE, jumpLabels->len };

				instruction newI = initJumpI(newJump);

				g_array_append_val(instructions, newI);
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
				jumpLabel newLabel = { FUNCTION_DONE, instructions->len };

				g_array_append_val(jumpLabels, newLabel);
			}
		}

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
void  execute(GArray* instructions, GArray* functions)
{

}




/*
Function: VMMain
Description: the interface for the virtual machine, this is called by Interpreter.run() at the very end.
Calls compile() to create a GArray of instructions, which are passed to execute() and executed.

Input: functions - a g_array of function structs created by the VMInputPass
*/
bool  VMMain(GArray* functions)
{

	// print all of the statements
	for (unsigned i = 0; i < functions->len; i++)
	{
		// get the function
		function func = g_array_index(functions, function, i);

		if (i == 0)
			printf("Main \n");

		else
			printf("Function: %d\n", i + 1);

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


	// get the array of instructions
	GArray* instructions = compile(functions);

	if (!instructions)
	{
		printf("Instructions not initialized\n");
		exit(1);

	}

	printInstructions(instructions);

	// execute the instructions, passing the local arrays for the functions
	//execute(instructions, functions);

	// free the instructions
	g_array_free(instructions, true);

	// free the data stack

	// now we need to free all of the input memory
	freeVMInput(functions);

	return true;
}



