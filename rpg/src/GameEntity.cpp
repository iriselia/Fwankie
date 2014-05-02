#include "GameEntity.h"

GameEntity::GameEntity() {

}

GameEntity::GameEntity(float _x_position, float _y_position) {
	this->x_position = _x_position;
	this->y_position = _y_position;
	this->x_rotation = 1;
	this->y_rotation = 1;
	this->x_scale = 1;
	this->y_scale = 1;
}

GameEntity::~GameEntity() {

}
