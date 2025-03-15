
#include <string>
#include <map>
#include "varSymbol.h"

using namespace std;

enum DATA_TYPE { POINTER, REF, INT };


class funcSymbol
{
public:

	string _name;

	string _paramName;

	bool paramIsMut;

	DATA_TYPE _returnType;

	DATA_TYPE _paramType;
	
	map<string, varSymbol> locals;



	funcSymbol(string name, string paramName, bool mut, DATA_TYPE returnType, DATA_TYPE paramType) : 
		_name(name), _paramName(paramName), paramIsMut(mut), _returnType(returnType), _paramType(paramType) {};

	funcSymbol() : _name(""), _paramName(""), paramIsMut(false), _returnType(INT), _paramType(INT) {};



	string  getName() { return _name; };

	map<string, varSymbol> getLocals() { return locals; };
};
