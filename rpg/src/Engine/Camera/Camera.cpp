#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(float _x_position, float _y_position) : GameEntity(_x_position, _y_position) {

}

Camera::~Camera() {

}

void Camera::Update(float _dt) {

}

void Camera::Enter(TileMap* _map) { m_pMap = _map; }

TileMap* Camera::getMap() { return m_pMap; }

void Camera::RenderScene() {
	// translate camera position to screen top left corner
	float x, y;
	x = this->Get_Display_Width_2() - this->GetXPosition();
	y = this->Get_Display_Height_2() - this->GetYPosition();

	// translate camera position again if map is smaller than screen
	// center the content.
	TileMap* temp = m_pMap;
	if (temp->Get_Width() < display_width_2 * 2)
		x = (float)(display_width_2 * 2 - temp->Get_Width()) / 2;
	if (temp->Get_Height() < display_height_2 * 2)
		y = (float)(display_height_2 * 2 - temp->Get_Height()) / 2;

	m_pMap->Render(this);// (0, 0, (int)x, (int)y);
	

	float x1 = target->GetXPosition(), y1 = target->GetYPosition();
	target->Render(x1 + x, y1 + y);

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

bool Camera::willCollideEast(float _x_displacement)
{
	return (target->GetXPosition() + display_width_2 + _x_displacement) >= m_pMap->Get_Width();
}

bool Camera::willCollideNorth(float _y_displacement)
{
	return (target->GetYPosition() - display_height_2 + _y_displacement) <= 0;
}

bool Camera::willCollideSouth(float _x_displacement)
{
	return (target->GetYPosition() + display_height_2 + _x_displacement) >= m_pMap->Get_Height();
}

bool Camera::willCollideWest(float _y_displacement)
{
	return (target->GetXPosition() - display_width_2 + _y_displacement) <= 0;
}
