
#include <string>
#include <map>
#include "varSymbol.h"

using namespace std;

class funcSymbol
{
public:
	string _name;

	map<string, varSymbol> locals;



	funcSymbol(string name) : _name(name) {};

	funcSymbol() : _name("") {};



	string  getName() { return _name; };

	map<string, varSymbol> getLocals() { return locals; };
};
