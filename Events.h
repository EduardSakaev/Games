#pragma once

#include "stdafx.h"
#include "Game.h"

class Game;

class Events
{
	Events(const Events & Right);
	Events & operator = (Events & right);
	bool IsMouseMove(hgeVector _mousepos);
	
private:
	Game * pGame;
	hgeVector mousepos;

	Node * sFocusIn;
	Node * sClickedBegin;

public:
	explicit Events(Game * pGame);
	~Events();

	void GetMousePos (hgeVector);
	void GetKey(int key);
	void IsKeyUp();
	void Update(float dt);
	void Render();
};