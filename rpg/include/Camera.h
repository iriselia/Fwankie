#include "GameEntity.h"
#include "Map.h"

class Camera : public GameEntity {
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
	void SetFollowee(GameEntity* _followee) { followee = _followee; }
	void SetZone(std::string _zone) { currentZone = _zone; }
	void SetWorld(std::map<std::string, Map*> _world) { world = _world; }
	void SetMap(Map* _map) { map = _map; }

	int Get_Display_Width_2() { return display_width_2; }
	int Get_Display_Height_2() { return display_height_2; }

	GameEntity* GetFollowee() { return followee; }
	Map* GetMap() { return map; }
	std::string GetZone() { return currentZone; }

	bool willCollideEast(float _x_displacement) { return (followee->GetXPosition() + display_width_2 + _x_displacement) >= map->Get_Width(); }
	bool willCollideNorth(float _y_displacement) { return (followee->GetYPosition() - display_height_2 + _y_displacement) <= 0; }
	bool willCollideSouth(float _x_displacement) { return (followee->GetYPosition() + display_height_2 + _x_displacement) >= map->Get_Height(); }
	bool willCollideWest(float _y_displacement) { return (followee->GetXPosition() - display_width_2 + _y_displacement) <= 0; }
private:
	// object of reference for camera movement
	GameEntity* followee;
	// the Map of the current world to render
	Map* map;
	std::map<std::string, Map*> world;
	// string name of zone
	std::string currentZone;
	// size of the camera
	int display_width_2;
	int display_height_2;
	// on-screen position of the top left corner of the camera
	int display_x;
	int display_y;
};