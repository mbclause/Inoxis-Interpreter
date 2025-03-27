
#pragma once
#include <string>
#include "dataType.h"

using namespace std;


enum MemFlags {
	none = 0,
	read = 1,
	write = 2,
	own = 4,
	flow = 8
};

// code taken from StackOverflow user eidolon
inline MemFlags operator|(MemFlags a, MemFlags b)
{
	return static_cast<MemFlags>(static_cast<int>(a) | static_cast<int>(b));
};


class varSymbol
{
public:


	string _name;

	bool _isMutable;

	bool _needsMemSafety;

	bool _isArray;

	//funcSymbol parentFunction;

	DataType::DATA_TYPE dataType;

	MemFlags memPermissions;

	varSymbol() : _name(""), _isMutable(false), _needsMemSafety(false), _isArray(false), dataType(DataType::INT), 
		memPermissions(none) {};

	varSymbol(string name, bool mut, bool memSafety, bool isArray, DataType::DATA_TYPE data, MemFlags memflags) :
		_name(name), _isMutable(mut), _needsMemSafety(memSafety), _isArray(isArray), dataType(data), memPermissions(memflags)
	{};

	void printVarSymbol();

	void setPermissions(MemFlags permissions) { memPermissions = permissions; };
};


