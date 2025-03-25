
#pragma once
#include <string>
#include "memAccess.h"
#include "dataType.h"

using namespace std;



class varSymbol
{
public:



	string _name;

	bool _isMutable;

	bool _needsMemSafety;

	bool _isArray;

	//funcSymbol parentFunction;

	DataType::DATA_TYPE dataType;

	//memAccess memInfo;

	varSymbol() : _name(""), _isMutable(false), _needsMemSafety(false), _isArray(false), dataType(DataType::INT) {};

	varSymbol(string name, bool mut, bool memSafety, bool isArray, DataType::DATA_TYPE data) :
		_name(name), _isMutable(mut), _needsMemSafety(memSafety), _isArray(isArray), dataType(data)
	{};

	void printVarSymbol();
};


