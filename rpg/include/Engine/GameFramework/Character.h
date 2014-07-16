#pragma once
#include "Pawn.h"

class BoxComponent;
class SpriteComponent;
class TileMap;

class Character : public Pawn
{
public:
	Character();
	~Character();
	
	virtual void RegisterAllComponents();
	void SetSprite(SpriteComponent* _pSpr);
	void RegisterWithTileMap(TileMap* _pTileMap);
	
	//movement
	void moveUp();

	void moveDown();

	void moveLeft();

	void moveRight();


private:
	TileMap* m_pCurrMap;
	BoxComponent* m_pBox;
	SpriteComponent* m_pSpr;
};
