#pragma once
#include "Box2D.h"

class hgeB2World :
	public b2World
{
public:
	hgeB2World(const b2Vec2& gravity);
	virtual ~hgeB2World();

	void SetMapSize(int _width, int _height) { m_map_width = P2M(_width); m_map_height = P2M(_height); }
	float GetMapWidth() { return m_map_width; } // In meters
	float GetMapHeight() { return m_map_height; } // In meters

private:
	float m_map_width;
	float m_map_height;
};
