#include "Holder.h"

//===============================================================
Holder::Holder():lenghtallobject(0), lengthbindobject(0)
{
	
}
//===============================================================
bool Holder::HasEntityObject ( std::string name)
{
	if (tablewithallobjects[name])
		return true;
	return false;
}
//===============================================================
bool Holder::HasBindObject   ( std::string name)
{
	if (tablewithbindobjects[name])
		return true;
	return false;
}
//===============================================================
std::map<std::string, Node*> & Holder::GetTableWithAllObjects()
{
	std::map<std::string, Node*> & pobjects = tablewithallobjects;
	return pobjects;
}
//===============================================================
std::map<std::string, Node*> & Holder::GetTableWithBindedObjects()
{
	std::map<std::string, Node*> & pbindobjects = tablewithbindobjects;
	return pbindobjects;
}
//===============================================================
void Holder::AddEntityObject(Node * obj, std::string name)
{
	tablewithallobjects.insert(std::make_pair(name, obj));
	tablewithallobjectnames.push_back(name);
	lenghtallobject = lenghtallobject + 1;
}
//===============================================================
void Holder::AddBindObject(Node * obj, std::string name)
{
	tablewithbindobjects.insert(std::make_pair(name, obj));
	tablewithbindobectnames.push_back(name);
	lengthbindobject = lengthbindobject + 1;
}
//===============================================================
Node * Holder::GetEntityObjectByName(std::string _key)
{
	return tablewithallobjects[_key];
}
//===============================================================
Node * Holder::GetBindObjectByName(std::string _key)
{
	return tablewithbindobjects[_key];
}
//===============================================================
Node * Holder::GetEntityObjectById(int id)
{
	std::string _key = tablewithallobjectnames[id];
	return tablewithallobjects[_key];
}
//===============================================================
Node * Holder::GetBindObjectById(int id)
{
	std::string _key = tablewithbindobectnames[id];
	return tablewithallobjects[_key];
}
//===============================================================
int Holder::GetLengthAllObjectTable()
{
	return lenghtallobject;
}
//===============================================================
int Holder::GetLengthBindObjectTable()
{
	return lengthbindobject;
}
//===============================================================
Holder::~Holder()
{
	//delete all objects
	for (int i = 0; i < lenghtallobject; ++i)
	{
		delete GetEntityObjectById(i);
	}

	for (int i = 0; i < lenghtallobject; ++i)
		tablewithallobjectnames.pop_back();

	for (int i = 0; i < lengthbindobject; ++i)
		tablewithbindobectnames.pop_back();
	
	tablewithallobjectnames.clear();
	tablewithbindobectnames.clear();
	tablewithallobjects.clear();
	tablewithbindobjects.clear();
}
//===============================================================
void Holder::Sort()
{
	int iSize = tablewithallobjectnames.size();
	if (iSize > 2)
	 {
        std::size_t jump = iSize;
        bool swapped = true;
        while (jump > 1 || swapped) 
		{
            if (jump > 1)
                jump /= 1.24733;

            swapped = false;

            for (std::size_t i = 0; i + jump < iSize; ++i)
			{
				std::string name_i    = tablewithallobjectnames[i];
				std::string name_jump = tablewithallobjectnames[i + jump];
                if (tablewithallobjects[name_i]->GetZ() > tablewithallobjects[name_jump]->GetZ()) 
				{
                    std::swap(tablewithallobjectnames[i], tablewithallobjectnames[i + jump]);
                    swapped = true;
                }
			}
        }
    }
}
 
