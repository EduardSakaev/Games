#include "stdafx.h"
#include "Holder.h"

class Helpers
{
public:
	Helpers(Holder * _pHolder)
	{
		pHolder = _pHolder;
	}
	Holder * pHolder;
	void EntityHide(std::string name)
	{
		Node * pSprite = pHolder -> GetEntityObjectByName(name);
		pSprite -> SetVisible(false);
		pSprite -> SetRespondable(false);
	}

	void EntityShow(std::string name)
	{
		Node * pSprite = pHolder -> GetEntityObjectByName(name);
		pSprite -> SetVisible(false);
		pSprite -> SetRespondable(false);
	}

	Node * GetEntityNamed(std::string name)
	{
		return pHolder -> GetEntityObjectByName(name);
	}

};
