/*
File: VirtualMachine.c
Description: Contains all function definitions for VirtualMachine.h
*/

#pragma once
#include "VirtualMachine.h"






/*
Function: crashReport
Description: If we hit an error in the virtual machine, dump the top of the stack and the instruction we are on and exit program.
*/
void  crashReport(GArray* stack, instruction badInstruction, int structnNum)
{
	printf("VM error at instruction %d", structnNum);

	// printInstruction

	// print stack
	printf("Stack contents: \n");

	// printStack()

	exit(1);
}



/*
Function: compileStatement
Description: use a switch statement to call the specified compile<statementType> method

Input: statement stmnt - the statement to compile
GArray* instructions - the array of instructions that will be added to during compilation of the statement
*/
void   compileStatement(statement stmnt, GArray* instructions)
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

	case IF:
		compileIf(stmnt.vals.ctrlFlowVals, instructions);
		break;

	case ELIF:
		compileElif(stmnt.vals.ctrlFlowVals, instructions);
		break;

	case ELSE:
		compileElse(stmnt.vals.ctrlFlowVals, instructions);
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
	GPtrArray* instructions = g_array_new(false, false, sizeof(instruction));

	if (instructions)
	{
		// loop through each function
		for (unsigned i = 0; i < functions->len; i++)
		{
			// get the function
			function func = g_array_index(functions, function, i);

			GArray* locals = g_array_index(functions, int, i);

			// loop through all statements and compile each
			for (unsigned j = 0; j < func.statements->len; j++)
			{
				statement stat = g_array_index(func.statements, statement, j);

				compileStatement(stat, instructions);
			}
		}

		return instructions;
	}

	else
		return NULL;

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

	// execute the instructions, passing the local arrays for the functions
	execute(instructions, functions);

	return true;
}