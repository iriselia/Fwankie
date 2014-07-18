#pragma once
#include "Pawn.h"

class BoxComponent;
class SpriteComponent;
class TileMap;

class Character : public Pawn
{
public:
	Character(TileMap* _TileMapToSpawnIn);
	~Character();
	
	void SetSprite(class hgeSprite* _pSpr);
	
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
