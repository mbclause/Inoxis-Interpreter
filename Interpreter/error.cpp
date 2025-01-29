#include "error.h"
#include <string>

int error_count = 0;

void report_error(ERROR_TYPE type, int line)
{
	string error_type;

	if (type == SYNTAX_ERROR)
		error_type = "SYNTAX ERROR";
	else
		error_type = "MEMORY SAFETY ERROR";

	cerr << error_type << " at line " << line << ".\n";

	error_count++;
}