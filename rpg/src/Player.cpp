#include "player.h"

Player::Player() {
	dx_dt = 0;
	dy_dt = 0;
}

Player::~Player() {

}

float Player::Get_dx_dt() { return this->dx_dt; }
float Player::Get_dy_dt() { return this->dy_dt; }
float Player::GetAcceleration() { return this->acceleration; }
float Player::GetFriction() { return this->friction; }

hgeAnimation* Player::getAnimation() { return this->anim; }

void Player::setVelocity(float newDx, float newDy) {
	this->dx_dt = newDx;
	this->dy_dt = newDy;
}

void Player::setAcceleration(float newAcceleration) {
	this->acceleration = newAcceleration;
}
void Player::setFriction(float newFriction) {
	this->friction = newFriction;
}
void Player::setAnimation(hgeAnimation *newAnim) {
	this->anim = newAnim;
}

void Player::Update(float _dt) {

}

void Player::Render(float _x_position, float _y_position) {
	anim->Render(_x_position, _y_position);
}