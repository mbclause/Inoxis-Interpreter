
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
// set flags with |
inline MemFlags operator|(MemFlags a, MemFlags b)
{
	return static_cast<MemFlags>(static_cast<int>(a) | static_cast<int>(b));
};

// use & to check if flag is set
inline MemFlags operator&(MemFlags a, MemFlags b)
{
	return static_cast<MemFlags>(static_cast<int>(a) & static_cast<int>(b));
};


class varSymbol
{
public:


	string _name;

	bool _isMutable;

	bool _needsMemSafety;

	bool _isArray;

	bool hasBeenDropped;

	//funcSymbol parentFunction;

	DataType::DATA_TYPE dataType;

	MemFlags memPermissions;

	// permissions for the heap data itself, only used if isBorrow = true
	MemFlags placeMemPermissions;

	bool isBorrow;

	// the name of the variable that is borrowed from (if isBorrow is set)
	string  borrowee;



	varSymbol() : _name(""), _isMutable(false), _needsMemSafety(false), _isArray(false), dataType(DataType::INT), 
		memPermissions(none), placeMemPermissions(none), isBorrow(false), borrowee(""), hasBeenDropped(false) {};

	varSymbol(string name, bool mut, bool memSafety, bool isArray, DataType::DATA_TYPE data, 
		MemFlags memflags, MemFlags place, bool borrow) :
		_name(name), _isMutable(mut), _needsMemSafety(memSafety), _isArray(isArray), 
		dataType(data), memPermissions(memflags), placeMemPermissions(place), isBorrow(borrow), hasBeenDropped(false)
	{};

	void printVarSymbol();

	// drop all of variables permissions, including its place's if applicable
	void dropPermissions() {
		setPermissions(none, false);

		if (isBorrow)
			setPermissions(none, true);
	}






	void  regainPermissions();

	void setPermissions(MemFlags permissions, bool forPlace) { 
		if (forPlace)
			placeMemPermissions = permissions;

		else
			memPermissions = permissions; 
	};

	// functions to check which flags are set
	// need to test these
	bool  hasReadPermissions(bool place) {
		if (place)
			return placeMemPermissions & read;
		else
			return memPermissions & read;
	}

	bool  hasWritePermissions(bool place) {
		if (place)
			return placeMemPermissions & write;
		else
			return memPermissions & write;
	}

	bool  hasOwnPermissions(bool place) {
		if (place)
			return placeMemPermissions & own;
		else
			return memPermissions & own;
	}
};


