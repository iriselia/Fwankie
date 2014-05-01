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

#include "Box2D.h"
#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"
#include "hgeparticle.h"
#include "HGEDebugDraw.h"

HGEDebugDraw DebugDraw;

//Flags use to manage Drawing in Box2D
uint32 flagsDraw = HGEDebugDraw::e_shapeBit|HGEDebugDraw::e_jointBit|HGEDebugDraw::e_aabbBit;

b2World *world = NULL;
b2Body *body = NULL;
b2Body *groundBody = NULL;

// Prepare for simulation. Typically we use a time step of 1/60 of a
// second (60Hz) and 10 iterations. This provides a high quality simulation
// in most game scenarios.
float32 timeStep = 1.0f / 60.0f;
int32 iterations = 10;

// Pointer to the HGE interface.
// Helper classes require this to work.
HGE *hge=0;

bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();

	// Process keys
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	
	// Moves the world
	world->Step(timeStep, iterations);

	return false;
}

bool RenderFunc()
{
	// Set the flags needed for Drawing
	DebugDraw.SetFlags(flagsDraw);
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);

	// Draw the stopped world
	world->Step(0,0);

	hge->Gfx_EndScene();

	// Clean the flags to don't Draw
	DebugDraw.SetFlags(0);
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "TestBedHGE.log");
	hge->System_SetState(HGE_HIDEMOUSE, false);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "TestBedHGE");
	hge->System_SetState(HGE_FPS, 100);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);

	b2AABB worldAABB;
	worldAABB.lowerBound.Set(-100.0f, -100.0f);
	worldAABB.upperBound.Set(100.0f, 100.0f);

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Do we want to let bodies sleep?
	bool doSleep = true;

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(worldAABB, gravity, doSleep);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -90.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonDef groundShapeDef;//b2PolygonDef groundShapeDef;

	// The extents are the half-widths of the box.
	groundShapeDef.SetAsBox(50.0f, 10.0f);

	// Add the ground shape to the ground body.
	groundBody->CreateShape(&groundShapeDef);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.position.Set(0.0f, 90.0f);
	body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2CircleDef shapeDef;//b2PolygonDef shapeDef;
	shapeDef.radius = 4.0f;

	// Set the box density to be non-zero, so it will be dynamic.
	shapeDef.density = 1.0f;

	// Override the default friction.
	shapeDef.friction = 0.3f;

	shapeDef.restitution = 0.2f;

	// Add the shape to the body.
	body->CreateShape(&shapeDef);

	// Now tell the dynamic body to compute it's mass properties base
	// on its shape.
	body->SetMassFromShapes();

	// Now set hge pointer for DebugDraw class
	DebugDraw.SetHGE(hge);
	// We need to clean the current flags
	DebugDraw.SetFlags(0);

	world->SetDebugDraw(&DebugDraw);

	if(hge->System_Initiate()) {
		
		// Let's rock now!
		hge->System_Start();
	}

	delete world;

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;
}