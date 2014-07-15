#include "Character.h"
#include <iostream>

Character::Character() : Pawn() {

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

