#include <math.h>

/* INCLUDE HGE LIBRARY */

#include "stdafx.h"
#include <iostream>
#include <thread>

#include "Game.h"
#include "Events.h"


// Pointer to the HGE interface (helper classes require this to work)
hgeGUI    * gui;

HGE * hge = 0;
hgeFont *	fnttime;
hgeFont *	fnt;
HANDLE hThread;
Events * events;
Game * game;

//cursor
float fcursor_x = 0, fcursor_y = 0;

//chips parameters
const int iNUM            = 20;           //counts of sprites
const int iSIZEX          = 40;
const int iSIZEY		  = 40;           
const int iHOTSPOTX       = 20;
const int iHOTSPOTY       = 20;

//bg parameters 
const int iBGWIDTH        = 1160;
const int iBGHEIGHT       = 700;

//screen parameters
const int SCREEN_WIDTH    = 1200;
const int SCREEN_HEIGHT   = 768;

//folder path to textures
const std::string folder_path ("textures\\");

void freeMemory();

bool FrameFunc()
{
	if (hge -> Input_IsMouseOver())
	{
		hge -> Input_GetMousePos(&fcursor_x, &fcursor_y);

		events -> GetMousePos(hgeVector(fcursor_x, fcursor_y));
		events -> GetKey(hge->Input_GetKey());
		events -> IsKeyUp();
		events -> Update(hge->Timer_GetDelta());
	}

	return false;
}

bool RenderFunc()
{
	// Render graphics
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	events ->Render();

	fnt->printf(5, 250, HGETEXT_LEFT, "dt:%.3f\nFPS:%d\n%.1f  %.1f", hge->Timer_GetDelta(), hge->Timer_GetFPS(), fcursor_x, fcursor_y);

	hge->Gfx_EndScene();

	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	// Set desired system states and initialize HGE
	hge->System_SetState(HGE_LOGFILE, "hge_my_first_project.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "HGEMy firs little project");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, SCREEN_WIDTH);
	hge->System_SetState(HGE_SCREENHEIGHT, SCREEN_HEIGHT);
	hge->System_SetState(HGE_SCREENBPP, 32);

	std::string icon_path = folder_path + "icon.png";
	hge->System_SetState(HGE_ICON, icon_path.c_str());
	if (!hge->System_Initiate())
	{
		hge->System_Shutdown();
		hge->Release();
		return 0;
	}

	fnt = new hgeFont("fonts\\font1.fnt");
	game = new Game();  
	events = new Events(game);

	hge->System_Start();

	// Delete created objects and free loaded resources
	freeMemory();

	if(_CrtDumpMemoryLeaks())
		hge->System_Log("Memory leaks yes");

	hge->System_Shutdown();
	hge->Release();

	return 0;
}

void freeMemory()
{
	delete events;
	delete game;
}


