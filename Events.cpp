#include "Events.h"

//========================================================
Events::Events(Game * _pGame):pGame(_pGame), mousepos(0,0), sFocusIn(NULL), sClickedBegin(NULL)
{
	 
}
//========================================================
Events::~Events()
{
	
}
//========================================================
void Events::GetMousePos (hgeVector _mousepos)
{
	if (IsMouseMove(_mousepos))
	{
		pGame -> onMouseMove(_mousepos, mousepos);

		std::map<std::string, Node*>::iterator iter; 
		std::map<std::string, Node*> & tablewithbindobjects = pGame ->GetHolder() -> GetTableWithBindedObjects();
		for (iter = tablewithbindobjects.begin(); iter != tablewithbindobjects.end(); ++iter)
		{
			if (iter -> second -> IsRespondable())
			{
				bool is_intersect = iter -> second -> IsIntersect(_mousepos);
				if (is_intersect)
				{
					pGame -> OnFocusIn(iter -> second);

					if (!sFocusIn)
						sFocusIn = iter -> second;

					break;
				}
				else if (sFocusIn)
				{
					pGame -> OnFocusOut(sFocusIn);
					sFocusIn = NULL;
				}
			}
		}
	}

	mousepos = _mousepos;
}
//========================================================
void Events::GetKey(int key)
{
	switch(key)
	{
	case HGEK_LBUTTON:
		if (sFocusIn)
		{
			pGame -> OnClickBegin(sFocusIn);
			sClickedBegin = sFocusIn;
		}
		break;
	}
}
//========================================================
bool Events::IsMouseMove(hgeVector _mousepos)
{
	float dx = mousepos.x - _mousepos.x;
	float dy = mousepos.y - _mousepos.y;

	if ((dx || dy) && (mousepos.x!= 0 && mousepos.y!=0))
		return true;

	mousepos.x = _mousepos.x;
	mousepos.y = _mousepos.y;

	return false;
}
//========================================================
void Events::IsKeyUp()
{
	if (sClickedBegin && hge->Input_KeyUp(HGEK_LBUTTON))
	{
		pGame -> OnClickEnd(sClickedBegin);
		sClickedBegin = NULL;
	}
}
//========================================================
void Events::Update(float dt)
{
	pGame  -> Update(dt);
}
//========================================================
void Events::Render()
{
	pGame  -> RenderObjects();
}
//========================================================