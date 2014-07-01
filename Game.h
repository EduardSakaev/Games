#pragma once
#include "stdafx.h"

#include "Entity.h"
#include "Node.h"
#include "Holder.h"
#include <vector>
#include <map>
#include "Helpers.h"
#include "Events.h"
#include <assert.h>


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//here I describe main game logic
class Game
{
	std::vector <hgeVector> tableofcoord; 
	Holder * pHolder;                  
	hgeVector mousepos; //store mousepos from last update frame
	Node * bClicked;    //Clicked Object
	Node * focusedObject;//object in ficus
	hgeVector iLeftTop; //left top position on the screen

	struct Fonts{
		hgeFont * font1;    //Write Score on the Screen
		hgeFont * font3;        //Write Active Object, which clicked
		hgeFont * fontScore;    //Write Score on the Screen
	}Fonts;
	
	Helpers * pHelpers;

	std::vector<int> iwaytoconnect;

	struct TableWithChipsParameters //write here chips positions 
	{
		int iraw;    //raw position
		int icolumn; //column position
		int iId;     //group id

		bool top;
		bool bottom;
		bool right;
		bool left;

		TableWithChipsParameters(const TableWithChipsParameters & Right ):iraw(Right.iraw), icolumn(Right.icolumn), iId(Right.iId)
		{
			top = Right.top;
			bottom = Right.bottom;
			left = Right.left;
			right = Right.right;
		}

		TableWithChipsParameters():left(false), right(false), bottom(false), top(false)
		{}
	};

	std::map<std::string, TableWithChipsParameters> tablewithchips; // store current chip position and its group

	//game parameters
	int iNumOfColumns;  // number of columns for net
	int iNumOfRaws;     // number of raws
	int iDX;            // difference between x nodes positions
	int iDY;            // difference between y nodes positions
	int iNumberOfUniqueChips; // number of chips group

	std::string folder_path;      //path to the sprite

	//Global score
	int Score;
	
	friend class Events;
public:
	Game();
	~Game();
	void RenderObjects();   //show sprites on the screen
	Node * GetActiveChip();
private:
	void RandomizeObjects(); 
	void Swap(std::string name_1, std::string name_2, Node*, Node*); 
	//======================================================= mechanics of game
	bool CheckOnConnect(Node * _sprite1, Node * _sprite2); // Check if 2 sprite might be connected
	bool LimitingOnTopRightBottomLeft(int raw_tar, int col_tar, int raw_cur, int col_cur);
	int CheckOnTurn(int raw_next, int column_next, int  number_of_turns);
	bool IsConnect(int raw_cur, int column_cur, int raw_tar, int col_tar, int iNumberOfTurns);
	void ClearTableFromRecursiveWay();
	void SetZ(int z, Node *);
	bool CheckOnPerform();

	//=======================================================
	//game fiches
	int GetScore();
	void SetScore(int);

	//game properties
	void CreatePositions();    // create positions for working sprites
	void CreateObjectsTable(); //download sprites on the screen
	Holder  * GetHolder();

	hgeVector GetXYFromArray(int raw, int column);
	void GetRawAndColumnById(int *, int *, int);
	int GetIdByRawAndColumn(int raw, int column);
	std::string GetNameById(int id);
	std::string GetNameByRawAndColumn(int raw, int column);

private:
	//events
	void Update(float dt);
	void onMouseMove(hgeVector , hgeVector);
	void OnFocusIn  (Node *);
	void OnFocusOut (Node *);
	void OnClickBegin(Node *);
	void OnClickEnd  (Node *);
};
