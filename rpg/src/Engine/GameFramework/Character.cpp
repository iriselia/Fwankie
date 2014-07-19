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
	delete m_pBox;
	delete m_pSpr;
}

void Character::moveUp() {
	std::cout << "Character Move Up.\n";
	m_pRootComponent->setY(m_pRootComponent->getY() - 1);
}

void Character::moveDown() {
	std::cout << "Character move down.\n";
	m_pRootComponent->setY(m_pRootComponent->getY() + 1);
}

void Character::moveLeft() {
	std::cout << "character move left.\n";
	m_pRootComponent->setX(m_pRootComponent->getX() - 1);
}

void Character::moveRight() {
	std::cout << "character move right.\n";
	m_pRootComponent->setX(m_pRootComponent->getX() + 1);
}

void Character::SetSprite(hgeSprite* _pSpr)
{
	m_pSpr->setStaticSprite(_pSpr);
}
