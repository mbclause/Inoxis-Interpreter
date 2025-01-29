#ifndef ERROR_H
#define ERROR_H
#include <iostream>

using namespace std;

enum ERROR_TYPE{SYNTAX_ERROR, MEM_SAFETY_ERROR};


// global variable to keep track of number of errors
extern int error_count;

void report_error(ERROR_TYPE type, int line);

#endif
