

#include <string>
#include "memAccess.h"

using namespace std;

class varSymbol
{
	string name;

	bool isMutable;

	bool needsMemSafety;

	memAccess memInfo;
};
