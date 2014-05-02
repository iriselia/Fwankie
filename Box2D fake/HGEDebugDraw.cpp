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

#include "HGEDebugDraw.h"

void HGEDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	if(!hge) return;
	
	float adjustW = hge->System_GetState(HGE_SCREENWIDTH)/2.0f;
	float adjustH = hge->System_GetState(HGE_SCREENHEIGHT)/2.0f;

	//hge->Gfx_BeginScene();
	for (int32 i = 0, j = 1; i < vertexCount; ++i, j++)
	{
		//glVertex2f(vertices[i].x, vertices[i].y);
		j = (j>=vertexCount)?0:j;
		hge->Gfx_RenderLine(adjustW + vertices[i].x, adjustH - vertices[i].y, adjustW + vertices[j].x, adjustH - vertices[j].y, ARGB(255,color.r*255,color.g*255,color.b*255));
	}
	//hge->Gfx_EndScene();
}

void HGEDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	if(!hge) return;
	
	float adjustW = hge->System_GetState(HGE_SCREENWIDTH)/2.0f;
	float adjustH = hge->System_GetState(HGE_SCREENHEIGHT)/2.0f;

	//hge->Gfx_BeginScene();
	for (int32 i = 0, j = 1; i < vertexCount; ++i, j++)
	{
		//glVertex2f(vertices[i].x, vertices[i].y);
		j = (j>=vertexCount)?0:j;
		hge->Gfx_RenderLine(adjustW + vertices[i].x, adjustH - vertices[i].y, adjustW + vertices[j].x, adjustH - vertices[j].y, ARGB(200,color.r*128,color.g*128,color.b*128));
	}
	//hge->Gfx_EndScene();
}

void HGEDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	if(!hge) return;

	float adjustW = hge->System_GetState(HGE_SCREENWIDTH)/2.0f;
	float adjustH = hge->System_GetState(HGE_SCREENHEIGHT)/2.0f;

	int NUMPOINTS = 24+(int)radius/20;//24;
    const float PI = 3.14159f;

	std::vector<b2Vec2> vertices;
	//hgeVector Circle[NUMPOINTS + 1];
	int i;//,j;
	float X;
	float Y;
	float Theta;
	float WedgeAngle;	//Size of angle between two points on the circle (single wedge)

	//Precompute WedgeAngle
	WedgeAngle = (float)((2*PI) / NUMPOINTS);

	//Set up vertices for a circle
	//Used <= in the for statement to ensure last point meets first point (closed circle)
	for(i=0; i<=NUMPOINTS; i++)
	{
		//Calculate theta for this vertex
		Theta = i * WedgeAngle;
		
		//Compute X and Y locations
		X = (float)(center.x + radius * cos(Theta));
		Y = (float)(center.y - radius * sin(Theta));

		vertices.push_back(b2Vec2(X, Y));//Circle[i] = hgeVector(X, Y);
	}

	//hge->Gfx_BeginScene();
	for (int32 k = 0, j = 1; k < (signed)vertices.size(); ++k, ++j)
	{
		//glVertex2f(vertices[i].x, vertices[i].y);
		j = (j>=(signed)vertices.size())?0:j;
		hge->Gfx_RenderLine(adjustW + vertices[k].x, adjustH - vertices[k].y, adjustW + vertices[j].x, adjustH - vertices[j].y, ARGB(255,color.r*255,color.g*255,color.b*255));
	}
	//hge->Gfx_EndScene();
}

void HGEDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	if(!hge) return;

	float adjustW = hge->System_GetState(HGE_SCREENWIDTH)/2.0f;
	float adjustH = hge->System_GetState(HGE_SCREENHEIGHT)/2.0f;

	int NUMPOINTS = 24+(int)radius/20;//24;
    const float PI = 3.14159f;

	std::vector<b2Vec2> vertices;
	//hgeVector Circle[NUMPOINTS + 1];
	int i;//,j;
	float X;
	float Y;
	float Theta;
	float WedgeAngle;	//Size of angle between two points on the circle (single wedge)

	//Precompute WedgeAngle
	WedgeAngle = (float)((2*PI) / NUMPOINTS);

	//Set up vertices for a circle
	//Used <= in the for statement to ensure last point meets first point (closed circle)
	for(i=0; i<=NUMPOINTS; i++)
	{
		//Calculate theta for this vertex
		Theta = i * WedgeAngle;
		
		//Compute X and Y locations
		X = (float)(center.x + radius * cos(Theta));
		Y = (float)(center.y - radius * sin(Theta));

		vertices.push_back(b2Vec2(X, Y));//Circle[i] = hgeVector(X, Y);
	}

	//hge->Gfx_BeginScene();
	
	for (int32 k = 0, j = 1; k < (signed)vertices.size(); ++k, ++j)
	{
		//glVertex2f(vertices[i].x, vertices[i].y);
		j = (j>=(signed)vertices.size())?0:j;
		hge->Gfx_RenderLine(adjustW + vertices[k].x, adjustH - vertices[k].y, adjustW + vertices[j].x, adjustH - vertices[j].y, ARGB(200,color.r*128,color.g*128,color.b*128));
	}
	//hge->Gfx_EndScene();
}

void HGEDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	if(!hge) return;

	float adjustW = hge->System_GetState(HGE_SCREENWIDTH)/2.0f;
	float adjustH = hge->System_GetState(HGE_SCREENHEIGHT)/2.0f;

	//hge->Gfx_BeginScene();
	hge->Gfx_RenderLine(adjustW + p1.x, adjustH - p1.y, adjustW + p2.x, adjustH - p2.y, ARGB(255,color.r*255,color.g*255,color.b*255));
	//hge->Gfx_EndScene();
}

void HGEDebugDraw::DrawXForm(const b2XForm& xf)
{
	if(!hge) return;
	
	float adjustW = hge->System_GetState(HGE_SCREENWIDTH)/2.0f;
	float adjustH = hge->System_GetState(HGE_SCREENHEIGHT)/2.0f;

	b2Vec2 p1 = xf.position, p2;
	const float32 k_axisScale = 0.4f;
	//hge->Gfx_BeginScene();
	
	p2 = p1 + k_axisScale * xf.R.col1;
	hge->Gfx_RenderLine(adjustW + p1.x, adjustH - p1.y, adjustW + p2.x, adjustH - p2.y, ARGB(255,255,0,0));

	p2 = p1 + k_axisScale * xf.R.col2;
	hge->Gfx_RenderLine(adjustW + p1.x, adjustH - p1.y, adjustW + p2.x, adjustH - p2.y, ARGB(255,0,255,0));

	//hge->Gfx_EndScene();
}