#include "Trigger_Portal.h"
#include "iostream"

void Trigger_Portal::Try(Player* _pPlayer) {
	if (isActive() && isTouchingTrigger(_pPlayer->GetXPosition(), _pPlayer->GetYPosition(), 5.0)) {
		std::cout << "Touching Portal\n";
		_pPlayer->setZone("little");
	}

	//else std::cout << "Not Touching Portal\n";
}

void Trigger_Portal::Update() {}
void Trigger_Portal::Update(float _dt) {}
void Trigger_Portal::Render(float _x_position, float _y_position) {}