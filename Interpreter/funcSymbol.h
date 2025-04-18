#pragma once
#include <string>
#include <map>
#include "varSymbol.h"
#include "dataType.h"

using namespace std;




class funcSymbol
{
public:

	string _name;

	string _paramName;

	bool paramIsMut;

	DataType::DATA_TYPE _returnType;

	DataType::DATA_TYPE _paramType;
	
	map<string, varSymbol> locals;

	vector<varSymbol>  variablesList;



	funcSymbol(string name, string paramName, bool mut, DataType::DATA_TYPE returnType, DataType::DATA_TYPE paramType) : 
		_name(name), _paramName(paramName), paramIsMut(mut), _returnType(returnType), _paramType(paramType) {};

	funcSymbol() : _name(""), _paramName(""), paramIsMut(false), _returnType(DataType::INT), _paramType(DataType::INT) {};



	string  getName() { return _name; };

	map<string, varSymbol> getLocals() { return locals; };
};
