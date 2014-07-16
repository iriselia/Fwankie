#include "Character.h"
#include "BoxComponent.h"
#include "SpriteComponent.h"
#include <iostream>

Character::Character() : Pawn() {
	m_pBox = new BoxComponent();
	m_pRootComponent = m_pBox;
	m_pRootComponent->SetOwner(this);
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

void Character::SetSprite(SpriteComponent* _pSpr)
{
	addComponent(_pSpr);
}

void Character::RegisterWithTileMap(TileMap* _pTileMap)
{
	m_pCurrMap = _pTileMap;
	RegisterAllComponents();
}

void Character::RegisterAllComponents()
{
	for (auto& component : m_OwnedComponents)
	{
		component->OnRegister();
		component->RegisterTickFuncWithTileMap(m_pCurrMap);
	}
}

