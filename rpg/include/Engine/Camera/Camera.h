#pragma once
#include "GameEntity.h"
#include "Map.h"

class Map;

class Camera : public GameEntity
{
public:
	Camera();
	Camera(float _x_position, float _y_position);
	~Camera();
	
	void Update(float _dt);
	void RenderScene();
	void Render(float _x_position, float _y_position);

	void SetDisplayLocation(int _display_x_position, int _display_y_position) { display_x = _display_x_position; display_y = _display_y_position; }
	void SetDisplaySize_1(float _display_width, float _display_height) { display_width_2 = static_cast<int>(_display_width / 2); display_height_2 = static_cast<int>(_display_height / 2); }
	void SetDisplaySize_2(float _display_width_2, float _display_height_2) { display_width_2 = static_cast<int>(_display_width_2); display_height_2 = static_cast<int>(_display_height_2); }
	void SetTarget(GameEntity* _target) { target = _target; }
	void SetZone(std::string _zone) { currentZone = _zone; }
	void Enter(Map* _map);

	int Get_Display_Width_2() { return display_width_2; }
	int Get_Display_Height_2() { return display_height_2; }

	GameEntity* GetFollowee() { return target; }
	Map* getMap();
	std::string GetZone() { return currentZone; }

	bool willCollideEast(float _x_displacement);
	bool willCollideNorth(float _y_displacement);
	bool willCollideSouth(float _x_displacement);
	bool willCollideWest(float _y_displacement);
private:
	// object of reference for camera movement
	GameEntity* target;
	Map* m_pMap;
	
	// string name of zone
	std::string currentZone;
	// size of the camera
	int display_width_2;
	int display_height_2;
	// on-screen position of the top left corner of the camera
	int display_x;
	int display_y;
};
