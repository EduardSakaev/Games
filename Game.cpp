#include "Game.h"
#include <ctime>

//===========================================
Game::Game():iNumOfColumns(15), iNumOfRaws(8), iDX(42), iDY(42), iNumberOfUniqueChips(20), mousepos(0,0), bClicked(NULL), Score(0), focusedObject(NULL)
{
	iLeftTop.x = 350;
	iLeftTop.y = 265;

	folder_path = "textures\\";
	char * path = "fonts\\font1.fnt";

	pHolder = new Holder();
	pHelpers = new Helpers(pHolder);

	Fonts.font3   = new hgeFont(path);
	Fonts.fontScore = new hgeFont(path);
	Fonts.font1 = new hgeFont(path);

	CreatePositions();
	CreateObjectsTable();
	RandomizeObjects();
}
//===========================================

void Game::CreatePositions() 
{
	for (int i = 0; i < iNumOfRaws; ++i)
	{
		for (int j = 0; j < iNumOfColumns; ++j)
		{
			hgeVector vector(0, 0);
			vector.x = (float)(iLeftTop.x + (j - 1) * iDX);
			vector.y = (float)(iLeftTop.y + (i - 1) * iDY);
			tableofcoord.push_back(vector);
		}
	}
}
//===========================================
Node * CreateObject(std::string Path, std::string Name, hgeVector hgevector, float width = 1, float height = 1, int Z = 0)
{
	Node * pobject = new SpriteEntity(Path, Name);
	pobject -> SetTextureRect(0, 0, width, height);
	pobject -> SetXY(hgevector.x, hgevector.y);
	pobject -> SetHotSpot(width / 2, height / 2);
	pobject -> SetZ(Z);
	
	return pobject;
}
//===========================================
void Game::CreateObjectsTable()
{
	//Maybe here I should use abstract factory...

	//1.create bg
	std::string path = folder_path +  "HOMG_Bg.png";
	std::string name   = "BG";

	Node * pobject_bg = CreateObject(path, name, hgeVector(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 1160, 700, 0);
	pHolder -> AddEntityObject(pobject_bg, name);

	//===============================================================
	//create chips
	char raw_id[5];
	char column_id[5];
	char Unique_id[3];
	std::string unique_name;
	Node * pobject;
	int iCounter = 0, iCurrentChip = 1;
	int iNumberOfEqualChips = iNumOfColumns * iNumOfRaws / iNumberOfUniqueChips;
	for (int i = 0; i < iNumOfRaws; ++i)
	{
		for (int j = 0; j < iNumOfColumns; ++j)
		{
			iCounter = iCounter + 1;
			_itoa_s(i, raw_id, 10);
			_itoa_s(j, column_id, 10);
			_itoa_s(iCurrentChip, Unique_id, 10);

			path = folder_path + "HOMG_Chip_" + Unique_id + ".PNG";
			name = "chip_" + (std::string)raw_id + "_" + (std::string)column_id;
			pobject = CreateObject(path, name, GetXYFromArray(i, j), 40, 40, 1);
			pHolder -> AddEntityObject(pobject, name);
			pHolder -> AddBindObject(pobject, name);
			pobject -> AttachTo(pobject_bg);

			// create table
			TableWithChipsParameters table;
			table.icolumn = j;
			table.iraw    = i;
			table.iId     = iCurrentChip;
			table.bottom  = false;
			table.left    = false;
			table.right   = false;
			table.left    = false;

			tablewithchips.insert(std::make_pair(name, table));
			//======================================================

			if (iCounter >= iNumberOfEqualChips)
			{
				iCounter = 0;

				if (iCurrentChip < iNumberOfUniqueChips)
					iCurrentChip = iCurrentChip + 1;
			}
		}
	}

	//===============================================================
	Node * pLight;
	char light_id[2];

	for (int i = 0; i < 2; ++i)
	{
		//light
		std::string light_path = folder_path + "HOMG_Chip_Light.PNG";
		_itoa_s(i + 1, light_id, 10);
		std::string light_name = "chip_light_" + (std::string)light_id;
		pLight =  CreateObject(light_path, light_name, GetXYFromArray(0, 0), 90, 90, 3);
		pLight -> SetHotSpot(46, 43);
		pHolder ->AddEntityObject(pLight, light_name); 
		pLight -> SetVisible(false);
	}
	//===============================================================
	// cursor
	std::string cursor_path = folder_path + "cursor.png";
	std::string cursor_name = "cursor";
	Node * pobject_cursor =  CreateObject(cursor_path, cursor_name, hgeVector(0,0), 64, 54, 10);
	pobject_cursor -> SetHotSpot(0, 0);
	pHolder ->AddEntityObject(pobject_cursor, cursor_name);
}
//===========================================
Holder * Game::GetHolder()
{
	return pHolder;
}
//===========================================
hgeVector Game::GetXYFromArray(int raw, int column)
{
	int id = (((raw + 1) * iNumOfColumns) - (iNumOfColumns - (column + 1))) - 1;
	hgeVector curpos;
	curpos = tableofcoord[id];
	return curpos;
}
//=============================================
Game::~Game()
{
	//выгружаю tableofcoord
	int iSize = tableofcoord.size();
	for (int i = 0; i < iSize; ++i)
	{
		tableofcoord.pop_back();
	}
	tableofcoord.clear();

	//release int * positions
	tablewithchips.clear();

	delete Fonts.font1;
	delete Fonts.font3;
	delete Fonts.fontScore;
}

//=============================================
// EVENTS
//=============================================
void Game::onMouseMove(hgeVector _curmousepos, hgeVector _prevMousePos)
{
	Node * pcursor = pHolder ->GetEntityObjectByName("cursor");
	pcursor -> SetXY(_curmousepos.x, _curmousepos.y);
}
//=============================================
void Game::OnFocusIn  (Node * _pSprite)
{
	float x = _pSprite -> GetScrX();
	float y = _pSprite -> GetScrY();

	focusedObject = _pSprite;

	if (!bClicked)
	{
		pHelpers->GetEntityNamed("chip_light_1") -> SetVisible(true);
		pHelpers->GetEntityNamed("chip_light_1") -> SetXY(x, y);
	}
	else 
	{
		pHelpers->GetEntityNamed("chip_light_2") -> SetVisible(true);
		pHelpers->GetEntityNamed("chip_light_2") -> SetXY(x, y);
	}

}
//=============================================
void Game::OnFocusOut (Node * _pSprite)
{
	if (!bClicked)
		pHelpers->GetEntityNamed("chip_light_1") -> SetVisible(false);
	else
		pHelpers->GetEntityNamed("chip_light_2") -> SetVisible(false);

	focusedObject = NULL;
}
//=============================================
void Game::OnClickBegin(Node * _pSprite)
{
	if (!bClicked)
	{
		bClicked = _pSprite;
		return;
	}

	if ((bClicked != _pSprite) && (tablewithchips[bClicked -> GetName()].iId == tablewithchips[_pSprite-> GetName()].iId) && CheckOnConnect(bClicked, _pSprite) ) 
	{
		pHelpers->EntityHide(bClicked-> GetName());
		pHelpers->EntityHide(_pSprite -> GetName());

		SetScore(GetScore() + 20);
	}
	
	pHelpers->GetEntityNamed("chip_light_1") -> SetVisible(false);
	pHelpers->GetEntityNamed("chip_light_2") -> SetVisible(false);
	bClicked = NULL;
	iwaytoconnect.clear();
}
//=============================================
void Game::OnClickEnd  (Node * _pSprite)
{

}
//===========================================
void Game::Update(float dt)
{

}
//=============================================

//===========================================
void Game::RenderObjects()
{
	int iSize = pHolder -> GetLengthAllObjectTable();
	for (int i = 0; i < iSize; ++i)
	{
		pHolder ->GetEntityObjectById(i)->Render();
	}

	if (bClicked)
		Fonts.font3 -> printf(5, 150, HGETEXT_LEFT, "Clicked Object: %s", bClicked -> GetName().c_str());
	
	Fonts.fontScore -> printf(512, 5, HGETEXT_LEFT, "Score is: %d", GetScore());

	if (focusedObject)
	{
		Fonts.font1 -> printf(5, 100, HGETEXT_LEFT, "Focus: %s", focusedObject -> GetName().c_str());
		Fonts.font1 -> printf(5, 130, HGETEXT_LEFT, "Object id is: %d", tablewithchips[focusedObject -> GetName().c_str()].iId);
		Fonts.font1 -> printf(5, 160, HGETEXT_LEFT, "Chip raw is: %d", tablewithchips[focusedObject -> GetName().c_str()].iraw);
		Fonts.font1 -> printf(5, 190, HGETEXT_LEFT, "Chip column is: %d", tablewithchips[focusedObject -> GetName().c_str()].icolumn);
	}

}
//===========================================
void Game::RandomizeObjects()
{
	srand(unsigned(time(NULL)));
	int iSize = tablewithchips.size();
	std::string name_1, name_2;


	int itemppos;
	for (int i = 1; i < iSize; ++i)
	{
		
		itemppos = rand() % i; // позици€, с которой € буду переставл€ть i-й объект

		name_1 = GetNameById(itemppos);
		name_2 = GetNameById(i);

		Node * pObject_1, * pObject_2;
		pObject_1 = pHolder -> GetBindObjectByName(name_1);
		pObject_2 = pHolder -> GetBindObjectByName(name_2);

		Swap(name_1, name_2, pObject_1, pObject_2);
	}
}
//===========================================
void Game::Swap(std::string name_1, std::string name_2, Node * pObject_1, Node * pObject_2)
{
	TableWithChipsParameters temp(tablewithchips[name_1]);

	tablewithchips[name_1].iId     = tablewithchips[name_2].iId;
	tablewithchips[name_2].iId     = temp.iId;
	
	//мен€ю дл€ Holder
	pHolder -> GetTableWithAllObjects().erase(name_1);
	pHolder -> GetTableWithAllObjects().erase(name_2);
	pHolder -> GetTableWithBindedObjects().erase(name_1);
	pHolder -> GetTableWithBindedObjects().erase(name_2);

	float x = pObject_1 -> GetX();
	float y = pObject_1 -> GetY();
	std::string name = pObject_1 -> GetName();

	pObject_1 -> SetX(pObject_2 -> GetX());
	pObject_1 -> SetY(pObject_2 -> GetY());
	pObject_1 -> SetName(pObject_2 -> GetName());

	pObject_2 -> SetXY(x, y);
	pObject_2 -> SetName(name); 

	//
	pHolder -> GetTableWithAllObjects().insert(std::make_pair(pObject_1 -> GetName(), pObject_1));
	pHolder -> GetTableWithAllObjects().insert(std::make_pair(pObject_2 -> GetName(), pObject_2));
	pHolder -> GetTableWithBindedObjects().insert(std::make_pair(pObject_1 -> GetName(), pObject_1));
	pHolder -> GetTableWithBindedObjects().insert(std::make_pair(pObject_2 -> GetName(), pObject_2));
}
//===========================================
void Game::GetRawAndColumnById(int * raw, int * column, int id)
{
	int iCount = 0;
	for (int i = 0; i < iNumOfRaws; ++i)
		for (int j = 0; j < iNumOfColumns; ++j)
		{
			if (iCount == id)
			{
				*raw = i;
				*column = j;
				return;
			}
			++iCount;
		}
}
//===========================================
int Game::GetIdByRawAndColumn(int raw, int column)
{
	return (iNumOfColumns *  (raw - 1) + column - 1);
}
//===========================================
std::string Game::GetNameById(int id)
{
	int raw = 0, column = 0;
	GetRawAndColumnById(&raw, &column, id);

	return GetNameByRawAndColumn(raw, column);
}
//===========================================
std::string Game::GetNameByRawAndColumn(int raw, int column)
{
	char sName_Buf_raw[3], sName_Buf_column[3];

	_itoa_s(raw, sName_Buf_raw, 10);
	_itoa_s(column, sName_Buf_column, 10);

	std::string name_1 = "chip_" + (std::string)sName_Buf_raw + "_" + sName_Buf_column;
	return name_1;
}
//===========================================
Node * Game::GetActiveChip()
{
	return bClicked;
}
//===========================================
int Game::GetScore()
{
	return Score;
}
//===========================================
void Game::SetScore(int _score)
{
	Score = _score;
}
//===========================================
bool Game::LimitingOnTopRightBottomLeft(int raw_tar, int col_tar, int raw_cur, int col_cur)
{
	if ((raw_cur < 0 || raw_cur >= iNumOfRaws) || (col_cur < 0 || col_cur >= iNumOfColumns))
		return true;

	int raw_from       = tablewithchips[bClicked-> GetName()].iraw;
	int col_from       = tablewithchips[bClicked-> GetName()].icolumn;
    int delta_raw      = raw_from - raw_tar;
    int delta_column   = col_from - col_tar;
    bool blimiting     = false;
    //--------------------------------------------------

    if ((delta_raw >= 0) && (delta_column <= 0))
	{
        blimiting =  ((raw_cur < raw_tar  && col_cur < col_from) || 
                      (raw_cur > raw_from  && col_cur < col_from) ||
                      (raw_cur < raw_tar   && col_cur > col_tar)  ||
                      (raw_cur > raw_from  && col_cur > col_tar));
	}
    else if (delta_raw >= 0 && delta_column >= 0)
	{
        blimiting =  ((raw_cur < raw_tar  && col_cur < col_tar)  ||
                      (raw_cur > raw_from  && col_cur < col_tar)  ||
                      (raw_cur < raw_tar   && col_cur > col_from) ||
                      (raw_cur > raw_from  && col_cur > col_from));
	}
    else if (delta_raw <= 0 && delta_column <= 0)
	{
        blimiting =  ((raw_cur < raw_from  && col_cur < col_from) || 
                      (raw_cur > raw_tar    && col_cur < col_from) || 
                      (raw_cur < raw_from   && col_cur > col_tar)  || 
                      (raw_cur > raw_tar    && col_cur > col_tar));
	}
    else if (delta_raw <= 0 && delta_column >= 0)
	{
        blimiting =  ((raw_cur < raw_from  && col_cur < col_tar) || 
                      (raw_cur > raw_tar    && col_cur < col_tar) ||
                      (raw_cur < raw_from   && col_cur > col_from)||
                      (raw_cur > raw_tar    && col_cur > col_from));
	}
    //--------------------------------------------------
	return blimiting;
}
//===========================================
bool Game::CheckOnConnect(Node * _sprite1, Node * _sprite2)
{
	int iraw_1 = tablewithchips[_sprite1 -> GetName()].iraw;
	int icol_1 = tablewithchips[_sprite1 -> GetName()].icolumn;

	int iraw_2 = tablewithchips[_sprite2 -> GetName()].iraw;
	int icol_2 = tablewithchips[_sprite2 -> GetName()].icolumn;
	
	//запускаю рекурсивную функцию, котора€ будет определ€ть, можно ли сконнектить 2 спрайта? 
	int id = GetIdByRawAndColumn(iraw_1, icol_1);
	iwaytoconnect.push_back(id);

	bool is_connect = IsConnect(iraw_1, icol_1, iraw_2, icol_2, 0);

	if (is_connect)
	{
		tablewithchips[_sprite1 -> GetName()].iId = 0;
		tablewithchips[_sprite2 -> GetName()].iId = 0;
	}

	ClearTableFromRecursiveWay();
	return is_connect;
}
//===========================================
bool Game::IsConnect(int raw_cur, int column_cur, int raw_tar, int col_tar, int iNumberOfTurns)
{
	//static bool bconnected = false;
	//провер€ю все направлени€, по нахождению пути...
	//int raw_next = raw_cur, column_next = column_cur;
	bool is_connect = false;
	std::string name_cur = GetNameByRawAndColumn(raw_cur, column_cur);
	//1. определение направлений
	//====================================================
	//top
	bool is_limit = LimitingOnTopRightBottomLeft(raw_tar, col_tar, raw_cur - 1, column_cur);
	std::string name_next = GetNameByRawAndColumn(raw_cur - 1, column_cur);
	bool is_free = (tablewithchips[name_next].iId == 0);

	if (raw_cur - 1 == raw_tar && column_cur == col_tar) 
			return true;

	if (CheckOnTurn(raw_cur - 1, column_cur, &iNumberOfTurns) && !is_limit && !tablewithchips[name_cur].top && is_free)
	{
		tablewithchips[name_cur].top = true;
		tablewithchips[name_next].bottom = true;
		is_connect = IsConnect(raw_cur - 1, column_cur, raw_tar, col_tar, iNumberOfTurns);
		if (is_connect)
			return true;
	}
	//====================================================
	//right
	is_limit = LimitingOnTopRightBottomLeft(raw_tar, col_tar, raw_cur, column_cur + 1);
	name_next = GetNameByRawAndColumn(raw_cur, column_cur + 1);
    is_free = (tablewithchips[name_next].iId == 0);

	if (raw_cur == raw_tar && column_cur + 1 == col_tar) 
			return true;

	if (CheckOnTurn(raw_cur, column_cur + 1, &iNumberOfTurns) && !is_limit  && !tablewithchips[name_cur].right && is_free)
	{
	    tablewithchips[name_cur].right = true;
		tablewithchips[name_next].left = true;
		is_connect = IsConnect(raw_cur, column_cur + 1, raw_tar, col_tar, iNumberOfTurns);
		if (is_connect)
			return true;
	}
	//====================================================
	//bottom
	is_limit = LimitingOnTopRightBottomLeft(raw_tar, col_tar, raw_cur + 1, column_cur);
	name_next = GetNameByRawAndColumn(raw_cur + 1, column_cur);
    is_free = (tablewithchips[name_next].iId == 0);

	if (raw_cur + 1 == raw_tar && column_cur == col_tar) 
			return true;

	if (CheckOnTurn(raw_cur + 1, column_cur, &iNumberOfTurns) && !is_limit  && !tablewithchips[name_cur].bottom && is_free)
	{
		tablewithchips[name_cur].bottom = true;
		tablewithchips[name_next].top = true;
		is_connect = IsConnect(raw_cur + 1, column_cur, raw_tar, col_tar, iNumberOfTurns);
		if (is_connect)
			return true;
	}
	//left
	//====================================================
	is_limit = LimitingOnTopRightBottomLeft(raw_tar, col_tar, raw_cur, column_cur - 1);
	name_next = GetNameByRawAndColumn(raw_cur, column_cur - 1);
    is_free = (tablewithchips[name_next].iId == 0);

	if (raw_cur == raw_tar && column_cur - 1 == col_tar) 
			return true;

	if (CheckOnTurn(raw_cur, column_cur - 1, &iNumberOfTurns) && !is_limit  && !tablewithchips[name_cur].left && is_free)
	{
		tablewithchips[name_cur].left = true;
		tablewithchips[name_next].right = true;
		is_connect = IsConnect(raw_cur, column_cur - 1, raw_tar, col_tar, iNumberOfTurns);
		if (is_connect)
			return true;
	}
	
	return false;
}
//===========================================
void Game::ClearTableFromRecursiveWay()
{
	int size = tablewithchips.size();

	for (int i = 0; i < size; ++i)
	{
		std::string name = GetNameById(i);
		tablewithchips[name].top = false;
		tablewithchips[name].right = false;
		tablewithchips[name].bottom = false;
		tablewithchips[name].left = false;
	}
}
//===========================================
bool Game::CheckOnTurn(int raw_next, int column_next, int * number_of_turns)
{
	int size =  iwaytoconnect.size(); 
    if (size > 1) 
	{
		int raw_cur, col_cur;
		GetRawAndColumnById(&raw_cur, &col_cur, iwaytoconnect[size]);

		int raw_prev, col_prev;
		GetRawAndColumnById(&raw_prev, &col_prev, iwaytoconnect[size - 1]);

        float determinant = (col_cur - col_prev) * (raw_next - raw_prev) - (raw_cur - raw_prev) * (column_next - col_prev);

        if(determinant != 0) 
            *number_of_turns = *number_of_turns + 1;

		return true;
	}

	if (*number_of_turns < 2)
		return true;
	return true;
}