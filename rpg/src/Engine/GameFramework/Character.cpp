#include "Character.h"
#include "BoxComponent.h"
#include "SpriteComponent.h"
#include <iostream>

Character::Character(TileMap* _TileMapToSpawnIn) : Pawn() {
	m_pCurrMap = _TileMapToSpawnIn;

	m_pBox = new BoxComponent();
	m_pSpr = new SpriteComponent();

	AddRootComponent(m_pBox);
	AddComponent(m_pSpr);
}

Character::~Character() {

}

void Character::moveUp() {
	std::cout << "Character Move Up.\n";
}

void Character::moveDown() {
	std::cout << "Character move down.\n";
}

void Character::moveLeft() {
	std::cout << "character move left.\n";
}

void Character::moveRight() {
	std::cout << "character move right.\n";
}

void Character::SetSprite(hgeSprite* _pSpr)
{
	m_pSpr->setStaticSprite(_pSpr);
}
