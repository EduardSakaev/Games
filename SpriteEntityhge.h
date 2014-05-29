#pragma once
#include "stdafx.h"

class SpriteEntityHge: public hgeSprite
{
public:
	SpriteEntityHge(HTEXTURE tex, float _x, float _y, float _w, float _h);

	hgeQuad GetQuad();
};
