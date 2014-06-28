#pragma once

#include "Node.h"
#include "stdafx.h"

#include <map>
#include <algorithm>
#include <functional>

class Holder //here we hold a pointers to our objects
{
	std::map<std::string, Node*> tablewithallobjects;
	std::map<std::string, Node*> tablewithbindobjects;

	std::vector<std::string> tablewithallobjectnames;
	std::vector<std::string> tablewithbindobectnames;
	
	int lenghtallobject;
	int lengthbindobject;
	// hide all constructors and operators of assignment
    Holder( const Holder & );  
    Holder & operator = ( Holder & );
public:
	 Holder();
	~Holder();
	// public methods
	std::map<std::string, Node*> & GetTableWithAllObjects();
	std::map<std::string, Node*> & GetTableWithBindedObjects();

	inline bool HasEntityObject ( std::string name);
	inline bool HasBindObject   ( std::string name);

	Node * GetEntityObjectByName(std::string);
	Node * GetBindObjectByName(std::string);

    Node * GetEntityObjectById(int id);
	Node * GetBindObjectById(int id);

	int GetLengthAllObjectTable();
	int GetLengthBindObjectTable();

	void AddEntityObject(Node * obj, std::string name);
	void AddBindObject(Node * obj, std::string name);

	void Sort();
};

