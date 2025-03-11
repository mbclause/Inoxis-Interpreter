
#include <string>
#include <map>
#include "varSymbol.h"

using namespace std;

class funcSymbol
{
	string name;

	map<string, varSymbol> locals;
};
