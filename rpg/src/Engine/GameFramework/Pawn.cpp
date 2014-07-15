#include "Pawn.h"

Pawn::Pawn() : AActor() {

}

void Pawn::disableControl(Controller* _controller) {

}

void Pawn::enableControl(class Controller* _controller) {

}

bool Pawn::isMouseTouchingMe() {
	return false;
}

Pawn* Pawn::Collide() {
	return nullptr;
}

bool Pawn::CollideWith(Pawn* _otherPawn) {
	return false;
}

