#pragma once
#include "stdafx.h"

#include <list>
#include <math.h>
#include <map>
#include <vector>

class Node //abstract base class
{
public:
	virtual ~Node(){}
	//====================================== methods
	virtual void Render()                      = 0;
	virtual void Update(int)                   = 0;
	virtual void AttachTo(Node * object)       = 0;
	virtual void DeAttach()                    = 0;

	virtual float GetX()                       = 0;
	virtual float GetY()                       = 0;
	virtual float GetScrX()                    = 0;
	virtual float GetScrY()                    = 0;
	virtual float GetHotSpotX()                = 0;
	virtual float GetHotSpotY()                = 0;
	virtual float GetWidth()                   = 0;
	virtual float GetHeight()                  = 0;
	virtual std::string GetName()              = 0;
	virtual int GetZ()                         = 0;
	virtual float GetScaleX()                  = 0;
	virtual float GetScaleY()                  = 0;
	virtual bool IsVisible()                   = 0;
	virtual bool IsRespondable()               = 0;
	virtual bool IsActive()                    = 0;
	virtual float GetRotationSpeed()           = 0;
	virtual Node* GetParentEntity()            = 0;
	virtual float GetRotationDeg()             = 0;
	virtual float GetRotationRad()             = 0;
	virtual std::map<std::string, Node*> & GetChildsEntity() = 0;
	virtual int GetColorAlpha ()             = 0;
	virtual int GetColorR()                  = 0;
	virtual int GetColorG ()                 = 0;
	virtual int GetColorB ()                 = 0;
	virtual bool IsIntersect(hgeVector)      = 0;


	virtual void SetX(float _x)                = 0;  //coord relatives parent coord
	virtual void SetY(float _y)                = 0;
	virtual void SetXY(float _x, float _y)     = 0;
	virtual void SetScrX(float _x)             = 0; //coord relatives screen coord
	virtual void SetScrY(float _y)             = 0;
	virtual void SetScrXY(float _x, float _y)  = 0;
	virtual void SetWidth(float _width)        = 0;
	virtual void SetHeight(float _height)      = 0;
	virtual void SetHotSpotX(float _hx)        = 0;
	virtual void SetHotSpotY(float _hy)        = 0;
	virtual void SetName(std::string name)     = 0;
	virtual void SetTextureRect(float top_x, float top_y, 
		float width, float height)              = 0;
	virtual void SetZ(int z)                    = 0; 

	virtual void SetHotSpot(float _x, float _y) = 0;
	
	virtual void SetRotationDeg(float Deg)      = 0;
	virtual void SetRotationRad(float Rad)      = 0;
	virtual void SetScaleX(float _scalex)       = 0;
	virtual void SetScaleY(float _scaley)       = 0;
	virtual void SetScale(float, float)         = 0;
	virtual void SetVisible(bool)               = 0;
	virtual void SetRespondable(bool)           = 0;
	virtual void SetActive(bool)                = 0;
	virtual void SetColor(int, int, int)        = 0;
	virtual void SetAlpha(int)                  = 0;

	virtual void RecalculatePositions(Node * pChild, float dangle, float scalex, float scale, int z, int alpha)   = 0;
	virtual void RecalculatePositionsForChilds(Node * pChild, float dangle, float scalex, float scale, int z, int alpha) = 0;
};