#pragma once
#include "Box2D.h"

class hgeB2World :
	public b2World
{
public:
	hgeB2World(const b2Vec2& gravity);
	~hgeB2World();

	void SetMapSize(int _width, int _height) { m_map_width = P2M(_width); m_map_height = P2M(_height); }
	int GetMapWidth() { return m_map_width; } // In meters
	int GetMapHeight() { return m_map_height; } // In meters

private:
	int m_map_width;
	int m_map_height;
};
