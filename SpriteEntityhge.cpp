#include "SpriteEntityhge.h"

SpriteEntityHge::SpriteEntityHge(HTEXTURE tex, float _x, float _y, float _w, float _h):hgeSprite(tex, _x, _y, _w, _h)
{

}
//==================================
hgeQuad SpriteEntityHge::GetQuad()
{
	return quad;
}