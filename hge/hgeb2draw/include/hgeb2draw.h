/*
* Copyright (c) 2008 Vitaliano Palmieri Neto
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#pragma once

#include "Box2D.h"
#include <hge.h>
#include <hgevector.h>
#include <hgecolor.h>
#include <iostream>
#include <vector>

struct b2AABB;

class hgeB2Draw :
	public b2Draw
{
public:
	hgeB2Draw(){};
	hgeB2Draw(HGE* draw):hge(draw){};
	void SetHGE(HGE* draw){ hge = draw;};
	//In Pixels.
	void SetMapHeight(int _height) { m_map_height = _height; }
	void SetDrawPosition(int _x, int _y) { m_x = _x; m_y = _y; }
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	void DrawTransform(const b2Transform& xf);

private:
	HGE* hge;
	int m_map_height;
	int m_x;
	int m_y;
};

/*
void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

void DrawString(int x, int y, const char* string, ...);
void DrawAABB(b2AABB* aabb, const b2Color& color);
*/