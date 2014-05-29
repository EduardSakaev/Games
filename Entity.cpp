#include "Entity.h"
//=====================================================
SpriteEntity::SpriteEntity(std::string path, std::string _name):sprite(0), texture(0), hx(0), hy(0), name(path), path(path), scalex(1), scaley(1),
	width(1), height(1), x(0), y(0), angle(0), pAttach(NULL), alpha(255), colorr(255), colorg(255), colorb(255), anglePar(0), scalexpar(0), scaleypar(0),
	ParentOrder(0), bVisible(true), bRespondable(true), bActive(true), rotationspeed(0), bVisiblePar(true), bRespondablePar(true), bActivePar(true), ParentAlpha(255)
{
	name = _name;
	texture = hge -> Texture_Load(path.c_str());
	sprite = new SpriteEntityHge(texture, 0, 0, 1, 1);
}
//=====================================================
SpriteEntity::SpriteEntity(const SpriteEntity & right):sprite(right.sprite), 
	hx(right.hx), hy(right.hy), name(right.name), path(right.path), scalex(right.scalex), scaley(right.scaley),
	width(right.width), height(right.height), x(right.x), y(right.y), angle(right.angle), pAttach(right.pAttach), alpha(right.alpha), 
	colorr(right.colorr), colorg(right.colorg), colorb(right.colorb), anglePar(right.anglePar), scalexpar(right.scalexpar), scaleypar(right.scaleypar),
    ParentOrder(right.ParentOrder), bVisible(right.bVisible), bRespondable(right.bRespondable), bActive(right.bActive), rotationspeed(right.rotationspeed),
	bVisiblePar(right.bVisiblePar), bRespondablePar(right.bRespondablePar), bActivePar(right.bActivePar), ParentAlpha(right.ParentAlpha)
{
	sprite = new SpriteEntityHge(right.texture, 0, 0, 1, 1);
}
//=====================================================
SpriteEntity::~SpriteEntity()
{
	hge->Texture_Free(texture);
	delete sprite;

	if (pAttach) 
		pAttach = 0;

	if (GetChildsEntity().size() != 0) 
		GetChildsEntity().clear();
}
//=====================================================
void SpriteEntity::DeAttach()
{
	if (!GetParentEntity()) return;

	x = x + GetParentX(GetParentEntity());
	y = y + GetParentY(GetParentEntity());

	anglePar = 0;
	scalexpar = 0;
	scaleypar = 0;
	ParentOrder = 0;
	bVisiblePar = true;
	bRespondablePar = true;
	bActivePar      = true;
	ParentOrder     = 1;
	GetParentEntity() ->GetChildsEntity().erase(GetName());
	pAttach = NULL;

	RecalculatePositionsForChilds(this, GetRotationRad(), 0, 0, GetZ(), GetColorAlpha());
}
//=====================================================
void SpriteEntity::AttachTo(Node * object)
{
	if (this == object || GetParentEntity()) return;

	pAttach = object;
	object -> GetChildsEntity().insert(std::make_pair(name, this));

	x = x - GetParentX(object);
	y = y - GetParentY(object);

	SetParentZ(object -> GetZ() > dynamic_cast<SpriteEntity *>(object) -> GetParentZ() ? dynamic_cast<SpriteEntity *>(object) -> GetParentZ() : object -> GetZ());
	SetParentActive(object -> IsActive());
	SetParentRespondable(object -> IsRespondable());
	SetParentVisibility(object -> IsVisible());
	SetParentScaleX(1 - object -> GetScaleX()  -  dynamic_cast<SpriteEntity *>(object) -> GetParentScaleX());
	SetParentScaleY(1 - object -> GetScaleY() -  dynamic_cast<SpriteEntity *>(object) -> GetParentScaleY());
	SetParentAlpha(object -> GetColorAlpha() * dynamic_cast<SpriteEntity *>(object) -> GetParentAlpha() / 255);
	SetParentRotationRad(object -> GetRotationRad() + dynamic_cast<SpriteEntity *>(object) -> GetParentRotationRad());

	//sending new info for childs
	RecalculatePositionsForChilds(this, GetParentRotationRad(), GetParentScaleX(), GetParentScaleY(), GetParentZ(), GetParentAlpha());
}
//=====================================================
void SpriteEntity::SetTextureRect(float top_x, float top_y, float _width, float _height)
{
	sprite->SetTextureRect(top_x, top_y, _width, _height);
	width = _width; 
	height = _height;
	sprite -> SetHotSpot(_width / 2, _height / 2);
}
//=====================================================
void SpriteEntity::SetX(float _x)
{
	x = _x;
}
//=====================================================
void SpriteEntity::SetY(float _y)
{
	y = _y; 
}
//=====================================================
void SpriteEntity::SetXY(float _x, float _y)
{
	x = _x;
	y = _y;
}
//=====================================================
void SpriteEntity::SetWidth(float _width)
{
	if (IsActive())
		width = _width;
}
//=====================================================
void SpriteEntity::SetHeight(float _height)
{
	if (IsActive())
		height = _height;
}
//=====================================================
void SpriteEntity::SetName(std::string _name)
{
	if (IsActive())
		name  = _name;
}
//=====================================================
void SpriteEntity::SetHotSpotX(float _hx)
{
	if (IsActive())
	{
		hx  = _hx;
	}
}
//=====================================================
void SpriteEntity::SetHotSpotY(float _hy)
{
	if (IsActive())
	{
		hy  = _hy;
	}
}
//=====================================================
void SpriteEntity::SetHotSpot(float _hx, float _hy)
{
	if (IsActive())
	{
		hx  = _hx;
		hy  = _hy;
	}
}
//=====================================================
void SpriteEntity::SetZ(int _z)
{
	if (IsActive())
	{
		int _idz = GetZ() - _z;
		RecalculatePositionsForChilds(this, 0, 0, 0, _idz);
		zOrder = _z;
	}
}
//=====================================================
void SpriteEntity::SetRotationDeg(float Deg)
{
	if (IsActive())
	{
		float angle_rad = (Deg * M_PI) / 180;
		RecalculatePositionsForChilds(this, angle_rad - angle);
		angle = angle_rad;
	}
}
//=====================================================
void SpriteEntity::SetRotationRad(float Rad)
{
	if (IsActive())
	{
		RecalculatePositionsForChilds(this, Rad - angle);
		angle = Rad;
	}
}
//=====================================================
void SpriteEntity::SetScaleX(float _scalex)
{
	if (IsActive())
	{
		float _dscalex = _scalex - GetScaleX();
		RecalculatePositionsForChilds(this, 0, _dscalex, 0, 0);
		scalex = _scalex;
	}
}
//=====================================================
void SpriteEntity::SetScaleY(float _scaley)
{
	if (IsActive())
	{
		float _dscaley = _scaley - GetScaleY();
		RecalculatePositionsForChilds(this, 0, 0, _dscaley, 0);
		scaley = _scaley;
	}
}
//=====================================================
void SpriteEntity::SetScale(float _sx , float _sy)
{
	if (IsActive())
	{
		float _dscalex = _sx - GetScaleX();
		float _dscaley = _sy - GetScaleY();
		RecalculatePositionsForChilds(this, 0, _dscalex, _dscaley, 0);
		scalex = _sx;
		scaley = _sy;
	}
}
//=====================================================
void SpriteEntity::SetVisible(bool _visible)
{
	if (IsActive())
	{
		bVisible = _visible;
		RecalculatePositionsForChilds(this);
	}
}
//=====================================================
void SpriteEntity::SetRespondable(bool _respondable)
{
	if (IsActive())
	{
		bRespondable = _respondable;
		RecalculatePositionsForChilds(this);
	}
}
//=====================================================
void SpriteEntity::SetActive(bool _active)
{
	bActive = _active;
	RecalculatePositionsForChilds(this);
}
//=====================================================
void SpriteEntity::SetColor(int _r, int _g, int _b)
{
	colorr = _r;
	colorg = _g;
	colorb = _b;
}
//=====================================================
void SpriteEntity::SetAlpha(int _alpha)
{
	RecalculatePositionsForChilds(this, 0, 0, 0, 0, _alpha - GetColorAlpha());
	alpha = _alpha;
}
//=====================================================
void SpriteEntity::SetParentScaleX(float _scalex)
{
	scalexpar = _scalex;
}
//=====================================================
void SpriteEntity::SetParentScaleY(float _scaley)
{
	scaleypar = _scaley;
}
//=====================================================
void SpriteEntity::SetParentRotationRad(float _angle)
{
	anglePar = _angle;
}
//=====================================================
void SpriteEntity::SetParentAlpha(int _alpha)
{
	ParentAlpha = _alpha;
}
//=====================================================
void SpriteEntity::SetParentZ(int _order)
{
	ParentOrder = _order;
}
//=====================================================
void SpriteEntity::SetParentVisibility(bool _visible)
{
	bVisiblePar = _visible;
}
//=====================================================
void SpriteEntity::SetParentActive(bool _active)
{
	bActivePar = _active;
}
//=====================================================
void SpriteEntity::SetParentRespondable(bool _respondable)
{
	bRespondablePar = _respondable;
}
////=====================================================
//void SpriteEntity::SetVertex(float _x, float _y, float _dangle, float _sx, float _sy)
//{
//		if (_x)
//		{
//			coordofvertex[0].x = GetParentX(this) - GetHotSpotX();
//			coordofvertex[1].x = GetParentX(this) - GetHotSpotX() + GetWidth();
//			coordofvertex[2].x = GetParentX(this) - GetHotSpotX() + GetWidth();
//			coordofvertex[3].x = GetParentX(this) - GetHotSpotX();
//		}
//		//-----------------------------------------------------------------
//		if (_y)
//		{
//			coordofvertex[0].y = GetParentY(this) - GetHotSpotY();
//			coordofvertex[1].y = GetParentY(this) - GetHotSpotY();
//			coordofvertex[2].y = GetParentY(this) - GetHotSpotY() + GetHeight();
//			coordofvertex[3].y = GetParentY(this) - GetHotSpotY() + GetHeight();
//		}
//		//-----------------------------------------------------------------
//		if (_dangle)
//		{
//			for (int i = 0; i < 4; ++i)
//			{
//				coordofvertex[i] = *coordofvertex[i].Rotate(_dangle);
//			}
//		}
//		//-----------------------------------------------------------------
//		if (_sx)
//		{
//			coordofvertex[0].x = GetParentX(this) - GetHotSpotX() + (1 - _sx) / 2;
//			coordofvertex[1].x = GetParentX(this) - GetHotSpotX() + GetWidth() - (1 - _sx) / 2;
//			coordofvertex[2].x = GetParentX(this) - GetHotSpotX() + GetWidth() - (1 - _sx) / 2;
//			coordofvertex[3].x = GetParentX(this) - GetHotSpotX() + (1 - _sx) / 2;
//		}
//		//-----------------------------------------------------------------
//		if (_sy)
//		{
//			coordofvertex[0].y = GetParentY(this) - GetHotSpotY() + (1 - _sy) / 2;
//			coordofvertex[1].y = GetParentY(this) - GetHotSpotY() + (1 - _sy) / 2;
//			coordofvertex[2].y = GetParentY(this) - GetHotSpotY() + GetHeight() - (1 - _sy) / 2;
//			coordofvertex[3].y = GetParentY(this) - GetHotSpotY() + GetHeight() - (1 - _sy) / 2;
//		}
//}
//=====================================================


//=====================================================
void SpriteEntity::RecalculatePositionsForChilds(Node * pNode, float _dangle, float _dscalex, float _dscaley, int _dz, int _dalpha)
{
	if (!pNode -> GetChildsEntity().empty())
	{
		std::map<std::string, Node*>::iterator iter;
		for (iter = pNode -> GetChildsEntity().begin(); iter != pNode -> GetChildsEntity().end(); ++iter)
		{
				iter -> second -> RecalculatePositions(iter -> second, _dangle, _dscalex, _dscaley, _dz, _dalpha);

				dynamic_cast<SpriteEntity *>(iter -> second) ->SetParentVisibility(iter -> second -> GetParentEntity() -> IsVisible());

				dynamic_cast<SpriteEntity *>(iter -> second) ->SetParentRespondable(iter -> second -> GetParentEntity() -> IsRespondable());

				dynamic_cast<SpriteEntity *>(iter -> second) ->SetParentActive(iter -> second -> GetParentEntity() -> IsActive());

				dynamic_cast<SpriteEntity *>(iter -> second) ->SetParentRotationRad(dynamic_cast<SpriteEntity *>(iter -> second) -> GetParentRotationRad() + _dangle);

				iter -> second -> RecalculatePositionsForChilds(iter -> second, _dangle, _dscalex, _dscaley, _dz, _dalpha); 
		}
	}
}
//=====================================================
float SpriteEntity::GetX()
{
	return x;
}
//=====================================================
float SpriteEntity::GetY()
{
	return y;
}
//=====================================================
float SpriteEntity::GetScrX()
{
	return x + GetParentX(pAttach);
}
//=====================================================
float SpriteEntity::GetScrY()
{
	return y + GetParentY(pAttach);
}
//=====================================================
float SpriteEntity::GetWidth()
{
	return sprite -> GetWidth();
}
//=====================================================
float SpriteEntity::GetHeight()
{
	return sprite -> GetHeight();
}
//=====================================================
std::string SpriteEntity::GetName()
{
	return name;
}
//=====================================================
SpriteEntityHge * SpriteEntity::GetHgeSpriteEntity()
{
	return sprite;
}
//=====================================================
float SpriteEntity::GetHotSpotX()
{
	return hx;
}
//=====================================================
float SpriteEntity::GetHotSpotY()
{
	return  hy;
}
//=====================================================
int SpriteEntity::GetZ()
{
	return  zOrder;
}
//===================================================== 
float SpriteEntity::GetRotationDeg()
{
	return (180 * angle) / M_PI;
}
//=====================================================
float SpriteEntity::GetRotationRad()
{
	return angle;
}
//=====================================================
float SpriteEntity::GetScaleX()
{
	return scalex;
}
//=====================================================
float SpriteEntity::GetScaleY()
{
	return scaley;
}
//=====================================================
bool SpriteEntity::IsVisible()
{
	return bVisible && GetParentVisibility();
}
//=====================================================
bool SpriteEntity::IsRespondable()
{
	return bRespondable && IsParentRespondable();
}
//=====================================================
bool SpriteEntity::IsActive()
{
	return bActive && IsParentActive();
}
//=====================================================
float SpriteEntity::GetRotationSpeed()
{
	return rotationspeed;
}
//=====================================================
float SpriteEntity::GetParentX(Node * Parent)
{
	float _x = 0.0;
	if (!Parent) return _x;

	_x = Parent -> GetX();
	_x = _x + GetParentX(Parent -> GetParentEntity());
	return _x;
}
//=====================================================
float SpriteEntity::GetParentY(Node * Parent)
{
	float _y = 0.0;
	if (!Parent) return _y;

	_y = Parent -> GetY();
	_y = _y + GetParentY(Parent -> GetParentEntity());
	return _y;
}
//=====================================================
float SpriteEntity::GetParentScaleX()
{
	return scalexpar;
}
//=====================================================
float SpriteEntity::GetParentScaleY()
{
	return scaleypar;
}
//=====================================================
float SpriteEntity::GetParentRotationRad()
{
	return anglePar;
}
//=====================================================
int SpriteEntity::GetParentZ()
{
	return ParentOrder;
}
//=====================================================
bool SpriteEntity::GetParentVisibility()
{
	return bVisiblePar;
}
//=====================================================
bool SpriteEntity::IsParentActive()
{
	return bActivePar;
}
//=====================================================
bool SpriteEntity::IsParentRespondable()
{
	return bRespondablePar;
}
//=====================================================
Node* SpriteEntity::GetParentEntity()
{
	return pAttach; 
}
//=====================================================
int SpriteEntity::GetParentAlpha()
{
	return ParentAlpha;
}
//=====================================================
std::map<std::string, Node*> & SpriteEntity::GetChildsEntity()
{
	return tablewithchilds;
}
//=====================================================
int SpriteEntity::GetColorAlpha()
{
	return alpha;
}
//=====================================================
int SpriteEntity::GetColorR()
{
	return colorr;
}
//=====================================================
int SpriteEntity::GetColorG()
{
	return colorg;
}
//=====================================================
int SpriteEntity::GetColorB()
{
	return colorb;
}
// ѕоложение точки относительно пр€мой 
float CheckPoint(float x1, float y1, float x2, float y2, float x3, float y3) 
{
      return (x2-x1)*(y2-y3)-(y2-y1)*(x2-x3); 
} 
//=====================================================
bool SpriteEntity::IsIntersect(hgeVector cursorpos) // cursor position
{
	hgeQuad Quad = GetHgeSpriteEntity() -> GetQuad();
	
	float a = CheckPoint(Quad.v[0].x, Quad.v[0].y, cursorpos.x, cursorpos.y, Quad.v[1].x, Quad.v[1].y);
	float b = CheckPoint(Quad.v[1].x, Quad.v[1].y, cursorpos.x, cursorpos.y, Quad.v[2].x, Quad.v[2].y);
	float c = CheckPoint(Quad.v[2].x, Quad.v[2].y, cursorpos.x, cursorpos.y, Quad.v[3].x, Quad.v[3].y);
	float d = CheckPoint(Quad.v[3].x, Quad.v[3].y, cursorpos.x, cursorpos.y, Quad.v[0].x, Quad.v[0].y);
	
	return !(a < 0 || b < 0 || c < 0 || d < 0);
}
//=====================================================

//=====================================================
void SpriteEntity::Render()
{
	if (IsVisible())
	{
		sprite -> RenderEx (GetParentX(this), GetParentY(this), anglePar + GetRotationRad(), GetScaleX() + scalexpar, 
											GetScaleY() + scaleypar);
		sprite -> SetZ((float)GetZ() / 10000); // 10000 - max z
		sprite -> SetColor(ARGB(GetColorAlpha() * GetParentAlpha() / 255, GetColorR(), GetColorG(), GetColorB()));
		sprite -> SetHotSpot(GetHotSpotX(), GetHotSpotY());
	}
}
//=====================================================
void SpriteEntity::Update(int _key)
{
	
}
//======================================================
void SpriteEntity::RecalculatePositions(Node * pNode,  float _dangle, float _dscalex, float _dscaley, int _dz, int _dalpha)
{
	if (!pNode) return;

	if (_dangle)
	{
		float Angle       = _dangle;
		//angle... recalculate xy
		float Radius = sqrt(GetX() * GetX() + GetY()  * GetY());
		float  alpha;

		if (GetX() <= 0 && GetY() <= 0)
		{
			alpha = - asin(y / Radius);
			SetXY(- Radius  * cos(alpha + Angle), - Radius  * sin(alpha + Angle)); //must be SETX ...
		}
		else if (GetX() >= 0 && GetY() >= 0)
		{
			alpha = asin(y / Radius);
			SetXY(Radius  * cos(alpha + Angle), Radius  * sin(alpha + Angle));
		}
		else if ( GetX() >= 0 && GetY() <= 0)
		{
			alpha =  asin(x / Radius);
			SetXY(Radius  * sin(alpha + Angle), - Radius  * cos(alpha + Angle));
		}
		else if ( GetX() <= 0 && GetY() >= 0)
		{
			alpha = - asin(x / Radius);
			SetXY(- Radius  * sin(alpha + Angle), Radius  * cos(alpha + Angle));
		}
	}

	//scale..
	if (_dscalex || _dscaley)
	{
		SetParentScaleX(GetParentScaleX() + _dscalex);
		SetParentScaleY(GetParentScaleY() + _dscaley);

		//// change xy derived by scale x, scale y ...
		//float x_par     = dynamic_cast<SpriteEntity *>(pParentNode) -> GetParentX(pParentNode);
		//float y_par     = dynamic_cast<SpriteEntity *>(pParentNode) -> GetParentY(pParentNode);
		//float angle_par_rad  = pParentNode -> GetRotationRad() + dynamic_cast<SpriteEntity *>(pParentNode) -> GetParentRotationRad();
		//float scalexpar      = pParentNode -> GetScaleX();
		//float scaleypar      = pParentNode -> GetScaleY();

		//float x_cur = dynamic_cast<SpriteEntity *>(pNode) -> GetParentX(pNode);
		//float y_cur = dynamic_cast<SpriteEntity *>(pNode) -> GetParentY(pNode);

		//float x_temp;
		//float y_temp;

		//float angle_par_deg = (180 * angle_par_rad) / M_PI;
		//while ((angle_par_deg < 0) ? (angle_par_deg += 360) : angle_par_deg);
		//while ((angle_par_deg > 360) ? (angle_par_deg -= 360) : angle_par_deg);

		//x_cur = x_cur - x_par;
		//y_cur = y_cur - y_par;

		//if (((x_cur <= 0) && (y_cur >= 0) && (angle_par_deg >= 0 && angle_par_deg <= 90))    ||
		//	((x_cur <= 0) && (y_cur <= 0) && (angle_par_deg >= 90 && angle_par_deg <= 180))  ||
		//	((x_cur  >= 0) && (y_cur <= 0) && (angle_par_deg >= 180 && angle_par_deg <= 270))||
		//	((x_cur  >= 0) && (y_cur >= 0) && (angle_par_deg >= 270 && angle_par_deg <= 360)))
		//{
		//	x_temp = sin(angle_par_deg) * (y_cur * cos(angle_par_deg) - x_cur * sin(angle_par_deg)) * (scaleypar + _dscaley)/ cos(2 * angle_par_deg)  +
		//		cos(angle_par_deg) *(x_cur * cos(angle_par_deg) - y_cur * sin(angle_par_deg)) * (scalexpar + _dscalex) / cos(2 * angle_par_deg);
		//	y_temp = cos(angle_par_deg) * (y_cur * cos(angle_par_deg) - x_cur * sin(angle_par_deg)) * (scaleypar + _dscaley)/ cos(2 * angle_par_deg) + 
		//		sin(angle_par_deg) * (x_cur * cos(angle_par_deg) - y_cur * sin(angle_par_deg)) * (scalexpar + _dscalex)/ cos(2 * angle_par_deg);
		//}
		//else if 
		//	(((x_cur - x_par >= 0) && (y_cur - y_par <= 0) && (angle_par_deg >= 0 && angle_par_deg <= 90))   ||
		//	((x_cur - x_par >= 0) && (y_cur - y_par >= 0) && (angle_par_deg >= 90 && angle_par_deg <= 180))  ||
		//	((x_cur - x_par <= 0) && (y_cur - y_par >= 0) && (angle_par_deg >= 180 && angle_par_deg <= 270)) ||
		//	((x_cur - x_par <= 0) && (y_cur - y_par <= 0) && (angle_par_deg >= 270 && angle_par_deg <= 360)))
		//{
		//	x_temp = (x_cur + cos(angle_par_deg) * (y_cur + sin(angle_par_deg) - x_cur * cos(angle_par_deg))) * (1 - _dscaley) - 
		//			cos(angle_par_deg) * (1 - _dscalex) * (y_cur * sin(angle_par_deg) - x_cur * cos(angle_par_deg));
		//	y_temp = cos(angle_par_deg) * (x_cur + cos(angle_par_deg) * (y_cur * sin(angle_par_deg) - x_cur * cos(angle_par_deg))) * (1 - _dscaley) / sin(angle_par_deg) + 
		//			sin(angle_par_deg) * (1 -  _dscalex) * (y_cur * sin(angle_par_deg) - x_cur * cos(angle_par_deg));
		//}
		//else if 
		//	(((x_cur - x_par <= 0) && (y_cur - y_par <= 0) && (angle_par_deg >= 0 && angle_par_deg <= 90))   ||
		//	((x_cur - x_par >= 0) && (y_cur - y_par <= 0) && (angle_par_deg >= 90 && angle_par_deg <= 180))  ||
		//	((x_cur - x_par >= 0) && (y_cur - y_par >= 0) && (angle_par_deg >= 180 && angle_par_deg <= 270)) ||
		//	((x_cur - x_par <= 0) && (y_cur - y_par >= 0) && (angle_par_deg >= 270 && angle_par_deg <= 360)))
		//{
		//	x_temp = cos(angle_par_deg) * (1 - _dscalex) * (x_cur * cos(angle_par_deg) + y_cur * sin(angle_par_deg)) / cos(2 * angle_par_deg) - 
		//		(1 - _dscaley) * sin(angle_par_deg) * (x_cur + y_cur * cos(angle_par_deg)) / cos(2 * angle_par_deg);
		//	y_temp = (1 - _dscaley) * cos(angle_par_deg) * (x_cur + y_cur * cos(angle_par_deg)) / cos(2 * angle_par_deg) - 
		//		(1 - _dscalex) * sin(angle_par_deg) * (x_cur * cos(angle_par_deg) + y_cur * sin(angle_par_deg)) / cos(2 * angle_par_deg);
		//}
		//else if 
		//	(((x_cur - x_par >= 0) && (y_cur - y_par >= 0) && (angle_par_deg >= 0 && angle_par_deg <= 90))   ||
		//	((x_cur - x_par <= 0) && (y_cur - y_par >= 0) && (angle_par_deg >= 90 && angle_par_deg <= 180))  ||
		//	((x_cur - x_par <= 0) && (y_cur - y_par <= 0) && (angle_par_deg >= 180 && angle_par_deg <= 270)) ||
		//	((x_cur - x_par >= 0) && (y_cur - y_par <= 0) && (angle_par_deg >= 270 && angle_par_deg <= 360)))
		//{
		//	x_temp = (1 - _dscaley) * cos(angle_par_deg) * (x_cur * cos(angle_par_deg) + y_cur * sin(angle_par_deg)) / cos(2 * angle_par_deg) - 
		//		(1 - _dscalex) * sin(angle_par_deg) * (x_cur * sin(angle_par_deg) - y_cur * cos(angle_par_deg)) / cos(2 * angle_par_deg);
		//	y_temp = (1 - _dscaley) * sin(angle_par_deg) * (x_cur * cos(angle_par_deg) + y_cur * sin(angle_par_deg)) / cos(2 * angle_par_deg) - 
		//		(1 - _dscalex) * cos(angle_par_deg) * (x_cur * sin(angle_par_deg) - y_cur * cos(angle_par_deg)) / cos(2 * angle_par_deg);
		//}
		//x_temp = x_temp + x_par;
		//y_temp = y_temp + y_par;

		//float x_ = x_temp - dynamic_cast<SpriteEntity *>(pNode) -> GetParentX(pNode -> GetParentEntity());
		//float y_ = y_temp - dynamic_cast<SpriteEntity *>(pNode) -> GetParentY(pNode -> GetParentEntity());
		//SetXY (x_, 
		//	   y_);

		//float x_dif = x_temp - x_cur;
		//float y_dif = y_temp - y_cur;
		//if (!pNode -> GetChildsEntity().empty())
		//{
		//	std::map<std::string, Node*>::iterator iter;
		//	for (iter = pNode -> GetChildsEntity().begin(); iter != pNode -> GetChildsEntity().end(); ++iter)
		//	{
		//		iter -> second -> SetXY(iter -> second ->GetX() + x_dif, iter -> second ->GetY() + y_dif);
		//	}
		//}
	}
	 
	//z
	if (_dz)
		SetParentZ(_dz);

	if (_dalpha)
		SetParentAlpha(GetParentAlpha() + _dalpha);
}
//======================================================


//====================================================== operators
SpriteEntity & SpriteEntity::operator = (const SpriteEntity & Right)
{
	if (this == &Right) return *this;

	SpriteEntity Temp(Right);
	char * pBuff = new char [sizeof(SpriteEntity)];

	memcpy(pBuff, this, sizeof(SpriteEntity));
	memcpy(this, &Temp, sizeof(SpriteEntity));
	memcpy(&Temp, pBuff, sizeof(SpriteEntity));
	delete [] pBuff;
	return *this;
}

//========================================================
bool SpriteEntity::operator == (const SpriteEntity & Right)
{
	if (this->name == Right.name)
		return true;
	return false;
}