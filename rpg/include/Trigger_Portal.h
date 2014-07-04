#pragma once
#include "Trigger.h"
#include "Player.h"


class Trigger_Portal : public Trigger<Player> {
private:

protected:
	//bool isTouchingTrigger(float _x, float _y, float _entityRadius)const;

public:

	Trigger_Portal(unsigned int _ui) : Trigger<Player>(_ui) {
		this->AddCircularTriggerRegion(0, 0, 40);
		SetActive();
	}
	~Trigger_Portal() {}

	void Try(Player*);
	void Update();
	void Render();
	void Update(float _dt);
	void Render(float _x_position, float _y_position);
}; 