#pragma once
#include "Pawn.h"

class BoxComponent;
class SpriteComponent;
class TileMap;
class SpellInfo;

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

	//cast spell
	void castSpell(SpellInfo* _spell);

private:
	TileMap* m_pCurrMap;
	BoxComponent* m_pBox;
	SpriteComponent* m_pSpr;
};
