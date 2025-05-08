/*
File: varSymbol.h
Description: The class definition for varSymbol. 
It represents a local variable in a function, containing all of its information.
This includes the variable's memory permissions.
*/

#pragma once
#include <string>
#include "dataType.h"

using namespace std;


// an enum representing the memory permission types for a variable
enum MemFlags {
	none = 0,
	read = 1,
	write = 2,
	own = 4,
	flow = 8
};



// code taken from StackOverflow user eidolon
// overloaded & and | operators used with the MemFlags enum

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



// class: varSymbol
class varSymbol
{
public:

	// data members
	string _name;

	bool _isMutable;

	bool _needsMemSafety;

	bool _isArray;

	bool hasBeenDropped;

	bool ownsHeapData;

	DataType::DATA_TYPE dataType;

	MemFlags memPermissions;

	// permissions for the heap data itself, only used if isBorrow = true
	MemFlags placeMemPermissions;

	bool isBorrow;

	// the name of the variable that is borrowed from (if isBorrow is set)
	string  borrowee;

	int arraySize;


	// ctors
	varSymbol() : _name(""), _isMutable(false), _needsMemSafety(false), _isArray(false), dataType(DataType::INT), 
		memPermissions(none), placeMemPermissions(none), isBorrow(false), borrowee(""), hasBeenDropped(false), arraySize(0),
		ownsHeapData(false)
	{};

	varSymbol(string name, bool mut, bool memSafety, bool isArray, DataType::DATA_TYPE data, 
		MemFlags memflags, MemFlags place, bool borrow, int size) :
		_name(name), _isMutable(mut), _needsMemSafety(memSafety), _isArray(isArray), 
		dataType(data), memPermissions(memflags), placeMemPermissions(place), isBorrow(borrow), 
		hasBeenDropped(false), arraySize(size), ownsHeapData(false)
	{};


	// member functions
	void printVarSymbol();

	// functions to change memory permissions
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


