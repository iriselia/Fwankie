#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(float _x_position, float _y_position) : GameEntity(_x_position, _y_position) {

}

Camera::~Camera() {

}

void Camera::Update(float _dt) {

}

void Camera::RenderScene() {
	// translate camera position to screen top left corner
	float x, y;
	x = this->Get_Display_Width_2() - this->GetXPosition();
	y = this->Get_Display_Height_2() - this->GetYPosition();

	// translate camera position again if map is smaller than screen
	// center the content.
	Map* temp = world[currentZone];
	if (temp->Get_Width() < display_width_2 * 2)
		x = static_cast<float>((display_width_2 * 2 - temp->Get_Width()) / 2);
	if (temp->Get_Height() < display_height_2 * 2)
		y = static_cast<float>((display_height_2 * 2 - temp->Get_Height()) / 2);

	world[currentZone]->Render(0, 0, static_cast<int>(x), static_cast<int>(y));
	

	float x1 = followee->GetXPosition(), y1 = followee->GetYPosition();
	followee->Render(x1 + x, y1 + y);

	/*
	// If camera is colliding horizontally
	if (willCollideEast(0.0f) || willCollideWest(0.0f))
		x1 = this->Get_Display_Width_2() + followee->GetXPosition() - this->GetXPosition();
	else
		x1 = this->Get_Display_Width_2();

	// If camera is colliding vertically
	if (willCollideSouth(0.0f) || willCollideNorth(0.0f))
		y1 = this->Get_Display_Height_2() + followee->GetYPosition() - this->GetYPosition();
	else
		y1 = this->Get_Display_Height_2();
		*/
	

}

// Usually will do nothing because camera usually doesn't have a sprite
void Camera::Render(float _x_position, float _y_position) {
}