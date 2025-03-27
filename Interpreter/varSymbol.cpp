#include "varSymbol.h"
#include <iostream>

using namespace DataType;

void  varSymbol::printVarSymbol()
{
	string type;

	string array = "/!array";

	string memSafety = "/!memSafety";

	string mut = "/mutable";

	if (dataType == POINTER)
		type = "/*";

	else if (dataType == INT)
		type = "/INT";

	else
		type = "/&";

	if (_isArray)
		array = "/array";

	if (_needsMemSafety)
		memSafety = "/memSafety";

	if (!_isMutable)
		mut = "/immutable";

	cout << _name << type << array << memSafety << mut << memPermissions << endl;
}