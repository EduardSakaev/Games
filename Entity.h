#pragma once
#include "Node.h"
#include "SpriteEntityhge.h"

extern HGE * hge;

class SpriteEntity: public Node
{
	SpriteEntityHge * sprite;
	HTEXTURE texture;

	Node * pAttach;

	std::map<std::string, Node*> tablewithchilds; //table with object which attached to this object

	//parents parameters
	float anglePar;
	float scalexpar, scaleypar; 
	int   ParentOrder, ParentAlpha;
	bool  bVisiblePar, bRespondablePar, bActivePar;

	std::string name; // name of object
	std::string path; // full path to the object

	float scalex, scaley, x, y, hx, hy, width, height, angle; 
	float rotationspeed; //speed to rotate sprite
	int zOrder, alpha, colorr, colorg, colorb;  
	bool bVisible, bRespondable, bActive;

public:
	SpriteEntity(std::string path, std::string name);
	SpriteEntity(const SpriteEntity &); // copy constructor

	~SpriteEntity();
	//=============================================
	virtual void Render();
	virtual void Update(int);
	inline virtual void AttachTo(Node * object);
	inline virtual void DeAttach();      
	//=============================================
	inline virtual std::string GetName();
	SpriteEntityHge * GetHgeSpriteEntity();

	inline virtual float GetX();
	inline virtual float GetY();
	inline virtual float GetScrX(); 
	inline virtual float GetScrY(); 
	inline virtual float GetWidth();
	inline virtual float GetHeight();
	inline virtual float GetHotSpotX();            
	inline virtual float GetHotSpotY(); 
	inline virtual int   GetZ();    
	inline virtual float GetRotationDeg();
	inline virtual float GetRotationRad();
	inline virtual float GetScaleX();
	inline virtual float GetScaleY();
    inline virtual bool  IsVisible();              
	inline virtual bool  IsRespondable();               
	inline virtual bool  IsActive();         
	inline virtual float GetRotationSpeed();  
	inline virtual Node* GetParentEntity();
	inline virtual  std::map<std::string, Node*> & GetChildsEntity();
	inline virtual int GetColorAlpha();           
	inline virtual int GetColorR();                 
	inline virtual int GetColorG();                
	inline virtual int GetColorB();
	virtual bool IsIntersect(hgeVector cursorpos);
public:
	//Parent parameters
	inline float GetParentX(Node *);
	inline float GetParentY(Node *);
	inline float GetParentScaleX();
	inline float GetParentScaleY();
	inline float GetParentRotationRad();
	inline int GetParentAlpha();
	inline int GetParentZ();
	inline bool GetParentVisibility();
	inline bool IsParentActive();
	inline bool IsParentRespondable();

	inline void SetParentScaleX(float);
	inline void SetParentScaleY(float);
	inline void SetParentRotationRad(float);
	inline void SetParentAlpha(int);
	inline void SetParentZ(int);
	inline void SetParentVisibility(bool);
	inline void SetParentActive(bool);
	inline void SetParentRespondable(bool);

public:
	inline virtual void SetX(float _x);
	inline virtual void SetY(float _y);
	inline virtual void SetXY(float _x, float _y);
	inline virtual void SetScrX(float _x);            
	inline virtual void SetScrY(float _y);           
	inline virtual void SetScrXY(float _x, float _y); 
	inline virtual void SetWidth(float _width);
	inline virtual void SetHeight(float _height);
	inline virtual void SetName(std::string name);
	inline virtual void SetHotSpotX(float _hx);
	inline virtual void SetHotSpotY(float _hy);
	inline virtual void SetHotSpot(float _x, float _y);
	inline virtual void SetRotationDeg(float Deg);
	inline virtual void SetRotationRad(float Rad);
	inline virtual void SetTextureRect(float top_x, float top_y, float width, float height);
	inline virtual void SetZ(int z);  
	inline virtual void SetScaleX(float _scalex);                  
	inline virtual void SetScaleY(float _scaley); 
	inline virtual void SetScale(float , float);        
	inline virtual void SetVisible(bool);             
	inline virtual void SetRespondable(bool);          
	inline virtual void SetActive(bool);   
	inline virtual void SetColor(int, int, int);
	inline virtual void SetAlpha(int);     
	

	//in has parent recalculate pos of sprite relatively parent
	virtual void RecalculatePositions(Node * pChild, float dangle, float scalex, float scale, int z, int alpha);
	virtual void RecalculatePositionsForChilds(Node * pNode,  float _dangle = 0, float _dscalex = 0, float _dscaley = 0, int _dz = 1, int _dalpha = 0);

	//operators
	//operator =, +=, -=, +, -, *, / ==
	SpriteEntity & operator = (const SpriteEntity & Right);
	bool operator == (const SpriteEntity & Right);
};


