#pragma once
#include "hge.h"
#include "hgeb2draw.h"
#include "Tmx.h"
#include "hgeb2world.h"

class Camera;
class CollisionMap
{
public:
	CollisionMap(const TCHAR* file_name);
	~CollisionMap();
	void Update(float _dt);
	void Render(Camera* _camera);

	void Load();
	void Unload();

private:
	int				m_width;
	int				m_height;
	HGE*			m_pHGE;
	Tmx::Map*		m_pMap_info;
	hgeB2World*		m_pHgeB2World;
	hgeB2Draw*		m_pIhgeB2Draw;
};
