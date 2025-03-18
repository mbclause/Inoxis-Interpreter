

#include <string>
#include "memAccess.h"

using namespace std;

class varSymbol
{
	string _name;

	bool _isMutable;

	bool _needsMemSafety;

	funcSymbol parentFunction;

	//memAccess memInfo;

	varSymbol() : _name(""), _isMutable(false), _needsMemSafety(false) {};

	varSymbol(string name, bool mut, bool memSafety, funcSymbol parent) : 
		_name(name), _isMutable(mut), _needsMemSafety(memSafety), parentFunction(parent) {};
};
