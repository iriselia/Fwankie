#pragma once
#include "Core.h"
#include "hge.h"
#include "hgeanim.h"
#include "GameEntity.h"
#include <string>

class Player : public GameEntity{
public:
	Player();
	~Player();
	float Get_dx_dt();
	float Get_dy_dt();
	float GetAcceleration();
	float GetFriction();

	hgeAnimation* getAnimation();

	void setZone(std::tstring str) { currentZone = str; }
	std::tstring getZone() { return currentZone; }

	void setVelocity(float, float);
	void setAcceleration(float);
	void setFriction(float);
	void setAnimation(hgeAnimation *);
	void Update(float _dt);
	void Render(float _x_position, float _y_position);

private:
	std::tstring currentZone;
	float dx_dt;
	float dy_dt;
	float acceleration;
	float friction;

	hgeAnimation *anim;
};
