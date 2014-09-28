#include "RPG_Debug.h"
#include "Player.h"
#include "settings.h"
#include "hgeanim.h"
#include "hgefont.h"
#include "hgeGUI.h"
#include "menuitem.h"
#include <fstream>
#include <iostream>
#include "hgeSprite.h"

#include <cstdio>
#include <stdlib.h>


#include <cassert>
#include "Box2D.h"

#include "Trigger_Portal.h"
#include "BaseManager.h"
#include "GUI.h"


#include "MapParser.h"
#include "CollisionMap.h"
#include "Atlas.h"
#include "TileMap.h"

#include "ScenePrivate.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Character.h"
#include "UserSetting.h"
#include "PlayerInput.h"

std::map<std::tstring, TileMap*> Atlas::m_atlas;


namespace RPG_Debug {

	HGE *hge = nullptr;
	GUI* gui = nullptr;
	InputComponent inputComponent;
	Character* pCharacter;
	UserSetting userSetting;
	PlayerInput playerInput(&userSetting, &inputComponent);

	Trigger_Portal* portal;
	Player*					myPlayer;
	Camera*					camera;
	HTEXTURE			hMouseTexture;
	hgeSprite			*mouseSprite;
	HTEXTURE			hPortal;
	HTEXTURE			anitex;
	hgeSprite			*portalSprite;
	hgeAnimation*		ani;
	hgeFont					*fnt;
	HEFFECT					snd;

	//experimental 


	// Some resource handles

	hgeQuad				quad;

	void init() {
		hge = hgeCreate(HGE_VERSION);

		Settings::load(TEXT("config.txt"));
		bool b_windowed = true;

		//hge->System_SetState(HGE_SHOWSPLASH, false);
		hge->System_SetState(HGE_LOGFILE, "resources/game.log");
		hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
		hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
		hge->System_SetState(HGE_TITLE, "Project 3: basic animation and map loading");
		hge->System_SetState(HGE_WINDOWED, b_windowed);
		hge->System_SetState(HGE_SCREENBPP, 32);
		hge->System_SetState(HGE_FPS, 60);
		hge->System_SetState(HGE_USETRANSPARENTCOLOR, true);

		assert(hge->System_Initiate());

		//Testing d3d11 only
		//hge->Gfx_Test();

		gui = new GUI();
		gui->registerWindow(hge->System_GetState(HGE_HWND), hge, b_windowed);
		// Make GUI mouse & key focus visible to the game.
		diagnostic::InputFocusInfo* diag = gui->getFocusInput();
		diag->setFocusVisible(true);

		myPlayer = new Player();
		std::ifstream savedata("resources/savedata.txt");
		if (savedata.is_open()) {
			char yolo[100];
			char *yololine = yolo;
			savedata.getline(yololine, 100);
			float x, y;
			x = strtof(yololine, &yololine);
			y = strtof(yololine, &yololine);
			myPlayer->SetXPosition(x);
			myPlayer->SetYPosition(y);
			myPlayer->setFriction(0.6f);
			myPlayer->setAcceleration(200);
			savedata.close();
		}
		else {
			perror("load savedata messed up!");
		}

		anitex = hge->Texture_Load("resources/aninew.png");
		ani = new hgeAnimation(anitex, 6, 6, 0, 0, 38, 46);
		ani->SetHotSpot(19, 17);
		ani->Play();

		myPlayer->setAnimation(ani);

		std::cout << "Loading Map \"desert\"\n";

		Atlas::AddMap(TEXT("map1.tmx"));
		Atlas::LoadResource(TEXT("map1.tmx"));
		Atlas::AddMap(TEXT("map2.tmx"));

		camera = new Camera();
		camera->SetXPosition(myPlayer->GetXPosition());
		camera->SetYPosition(myPlayer->GetYPosition());
		camera->SetDisplayLocation(0, 0);
		camera->SetDisplaySize_1(800, 600);
		camera->SetTarget(myPlayer);
		camera->Enter(Atlas::queryByName(TEXT("map1.tmx")));
		camera->SetZone(TEXT("desert"));

		/*
		b2AABB worldAABB;
		worldAABB.lowerBound.Set(-100.0f, -100.0f);
		worldAABB.upperBound.Set(100.0f, 100.0f);

		// Define the gravity vector.
		b2Vec2 gravity(0.0f, -10.0f);

		// Do we want to let bodies sleep?
		bool doSleep = true;

		// Construct a world object, which will hold and simulate the rigid bodies.
		b2world = new b2World(gravity);
		b2world->SetAllowSleeping(doSleep);
		// Now set hge pointer for DebugDraw class
		IhgeB2Draw.SetHGE(hge);
		// We need to clean the current flags
		IhgeB2Draw.SetFlags(0);

		b2world->SetDebugDraw(&IhgeB2Draw);

		// Define the ground body.
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, 0.0f);

		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground box shape (also from a pool).
		// The body is also added to the world.
		b2Body* groundBody = b2world->CreateBody(&groundBodyDef);

		// Define the ground box shape.
		b2PolygonShape groundBox;

		// The extents are the half-widths of the box.
		groundBox.SetAsBox(P2M(395), P2M(100));

		// Add the ground fixture to the ground body.
		groundBody->CreateFixture(&groundBox, 0.0f);





		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(0.0f, 40.0f);
		b2Body* body = b2world->CreateBody(&bodyDef);

		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f, 1.0f);

		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 1.0f;

		// Override the default friction.
		fixtureDef.friction = 0.3f;

		// Add the shape to the body.
		//body->CreateFixture(&fixtureDef);
		*/

		hMouseTexture = hge->Texture_Load("resources/cursor.png");
		mouseSprite = new hgeSprite(hMouseTexture, 0, 0, 32, 32);

		pCharacter = new Character(Atlas::queryByName(TEXT("map1.tmx")));
		pCharacter->SetSprite(ani);
		pCharacter->RegisterWithTileMap(Atlas::queryByName(TEXT("map1.tmx")));

		//set up input component
		inputComponent.addKeyBinding(TEXT("CHAR_MOVE_UP"), BIND_MEM_CB(&Character::moveUp, pCharacter));
		inputComponent.addKeyBinding(TEXT("CHAR_MOVE_LEFT"), BIND_MEM_CB(&Character::moveLeft, pCharacter));
		inputComponent.addKeyBinding(TEXT("CHAR_MOVE_DOWN"), BIND_MEM_CB(&Character::moveDown, pCharacter));
		inputComponent.addKeyBinding(TEXT("CHAR_MOVE_RIGHT"), BIND_MEM_CB(&Character::moveRight, pCharacter));

		userSetting.setKeyBindingMap(TEXT("./config/UserKeySetting.txt"));
	}

	void run() {
		hge->System_Start();
	}

	void halt() {
		delete myPlayer;
		delete camera;
		delete ani;

		delete mouseSprite;
		delete pCharacter;

		Atlas::DestroyAll();


		//delete gui;
		//delete imageLoader;
		//delete input;
		//delete graphics;
		gui->shutdown();
		delete gui;
		gui = nullptr;
		hge->Release();
	}

	bool FrameFunc() {
		if (hge->Input_GetKeyState(HGEK_ESCAPE)) {
			return true;
		}

		float dt = hge->Timer_GetDelta();
		float mouseX, mouseY;
		hge->Input_GetMousePos(&mouseX, &mouseY);

		// check mouse hover
		bool isMouseOnGUI = gui->getFocusInput()->doesMouseHaveFocus();

		//Update Map
		Atlas::queryByName(TEXT("map1.tmx"))->Update(dt);

		// Do mouse hover logic
		if (isMouseOnGUI) {
			printf("Mouse is on GUI, abort collision check on actors.\n");
		}
		else {
			// x/y difference between mouse and sprite
			float a = mouseX - myPlayer->GetXPosition();
			float b = mouseY - myPlayer->GetYPosition();
			if (ani->isHoveringXY((float)a, (float)b)) {
				printf("is hovering player!! x: %f, y: %f, frame: %d\n", mouseX, mouseY, ani->GetFrame());
			}
		}

		playerInput.translateInput();
		playerInput.dispatchMessage();
		inputComponent.executeAction();
		// player move
		float x = myPlayer->GetXPosition(), y = myPlayer->GetYPosition();
		float dx_dt = myPlayer->Get_dx_dt(), dy_dt = myPlayer->Get_dy_dt();
		float acceleration = myPlayer->GetAcceleration();
		float friction = myPlayer->GetFriction();

		if (hge->Input_GetKeyState(HGEK_LEFT) ||
			hge->Input_GetKeyState(HGEK_A)) {
			dx_dt = -acceleration;
		}
		if (hge->Input_GetKeyState(HGEK_RIGHT) ||
			hge->Input_GetKeyState(HGEK_D)) {
			dx_dt = acceleration;
		}
		if (hge->Input_GetKeyState(HGEK_UP) ||
			hge->Input_GetKeyState(HGEK_W)) {
			dy_dt = -acceleration;
		}
		if (hge->Input_GetKeyState(HGEK_DOWN) ||
			hge->Input_GetKeyState(HGEK_S)) {
			dy_dt = acceleration;
		}

		int map_width = camera->getMap()->Get_Width();
		int map_height = camera->getMap()->Get_Height();

		// Do some movement calculations and collision detection
		if (x > map_width - 16) { x = map_width - 16 - (x - map_width - 16); dx_dt = -dx_dt; }
		if (x<16) { x = 16 + 16 - x; dx_dt = -dx_dt; }
		if (y> map_height - 16) { y = map_width - 16 - (y - map_width - 16); dy_dt = -dy_dt; }
		if (y < 16) { y = 16 + 16 - y; dy_dt = -dy_dt;  }

		myPlayer->setVelocity(dx_dt * friction, dy_dt * friction);
		myPlayer->SetXPosition(x + dx_dt * dt);
		myPlayer->SetYPosition(y + dy_dt * dt);

		// camera move
		// check if camera reaches edge in this movement




		float cam_x = camera->GetXPosition();
		float cam_y = camera->GetYPosition();

		int cam_width_2 = camera->Get_Display_Width_2();
		int cam_height_2 = camera->Get_Display_Height_2();

		float h_displacement = dx_dt * dt;
		float v_displacement = dy_dt * dt;

		// resolve camera movement on x axis
		if (camera->willCollideEast(h_displacement))
			camera->SetXPosition(map_width - cam_width_2);
		else if (camera->willCollideWest(h_displacement))
			camera->SetXPosition(0 + cam_width_2);
		else camera->SetXPosition(cam_x + h_displacement);


		// resolve camera movement on y axis
		if (camera->willCollideSouth(v_displacement))
			camera->SetYPosition((float)(map_height - cam_height_2));
		else if (camera->willCollideNorth((float)(v_displacement)))
			camera->SetYPosition((float)(0 + cam_height_2));
		else camera->SetYPosition((float)(cam_y + v_displacement));

		//myPlayer->setPosition(x + dx_dt, y + dy_dt);
		//myPlayer->getAnimation()->Update(dt);

		//camera->GetMap()->StepB2World();

		return false;
	}

	bool RenderFunc() {
		hge->Gfx_BeginScene();
		hge->Gfx_Clear(0);
		//hge->Gfx_SetClipping(0, 0, 300, 300);
		camera->RenderScene();

		Atlas::queryByName(TEXT("map1.tmx"))->Render();
		//Render Mouse
		float x, y;
		hge->Input_GetMousePos(&x, &y);
		mouseSprite->Render(x, y);
		mouseSprite->Render(0, 0);
		//Render GUI
		gui->HgeFrameFunc();

		hge->Gfx_EndScene();

		return false;
	}

}