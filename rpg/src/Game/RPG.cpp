#include "RPG.h"
#include "Player.h"
#include "Camera.h"

#include "settings.h"
#include "hgeanim.h"
#include "hgefont.h"
#include "hgeGUI.h"
#include "menuitem.h"
#include <fstream>
#include <iostream>
#include "hgeSprite.h"

#include "Tmx.h"
#include <cstdio>
#include <stdlib.h>

#include "MapParser.h"
#include <cassert>
//#include "Box2D.h"

#include "Trigger_Portal.h"
#include "BaseManager.h"
#include "GUI.h"

namespace RPG {

	// All back ends contain objects to make Guichan work on a
	// specific target - in this case HGE - and they are a Graphics
	// object to make Guichan able to draw itself using HGE, an
	// input object to make Guichan able to get user input using HGE
	// and an ImageLoader object to make Guichan able to load images
	// using SDL.
	//gcn::HGEGraphics		*graphics;
	//gcn::HGEInput			*input;
	//gcn::HGEImageLoader		*imageLoader;
	//gcn::Gui				*gui;

	HGE *hge = 0;
	//base::BaseManager* gui = 0;
	GUI* gui = 0;

	Tmx::Map *map;
	std::map<std::tstring, MapParser*> world;
	Trigger_Portal* portal;
	//b2World *b2World = NULL;

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

	// Some resource handles

	hgeQuad				quad;

	// Pointers to the HGE objects we will use
	//hgeGUI				*gui;


	float mouseX, mouseY;
	int count;

	void boom() {
		int pan = int((myPlayer->GetXPosition() - 400) / 4);
		float pitch = (myPlayer->Get_dx_dt()*myPlayer->Get_dx_dt() + myPlayer->Get_dy_dt()*myPlayer->Get_dy_dt())*0.0005f + 0.2f;
		hge->Effect_PlayEx(snd, 100, pan, pitch);
	}

	bool FrameFunc(){
		if (hge->Input_GetKeyState(HGEK_ESCAPE)) {
			return true;
		}
		float dt = hge->Timer_GetDelta();

		// camera zone check
		camera->SetZone(myPlayer->getZone());
		if (!world[camera->GetZone()]->isLoaded()) {
			world[camera->GetZone()]->Load();
		}

		// player move
		float x = myPlayer->GetXPosition(), y = myPlayer->GetYPosition();
		float dx_dt = myPlayer->Get_dx_dt(), dy_dt = myPlayer->Get_dy_dt();
		float acceleration = myPlayer->GetAcceleration();
		float friction = myPlayer->GetFriction();

		if (hge->Input_GetKeyState(HGEK_LEFT)) {
			dx_dt = -acceleration;
		}
		if (hge->Input_GetKeyState(HGEK_RIGHT)) {
			dx_dt = acceleration;
		}
		if (hge->Input_GetKeyState(HGEK_UP)) {
			dy_dt = -acceleration;
		}
		if (hge->Input_GetKeyState(HGEK_DOWN)) {
			dy_dt = acceleration;
		}

		int map_width = world[camera->GetZone()]->Get_Width();
		int map_height = world[camera->GetZone()]->Get_Height();

		// Do some movement calculations and collision detection
		if (x > map_width - 16) { x = map_width - 16 - (x - map_width - 16); dx_dt = -dx_dt; boom(); }
		if (x<16) { x = 16 + 16 - x; dx_dt = -dx_dt; boom(); }
		if (y> map_height - 16) { y = map_width - 16 - (y - map_width - 16); dy_dt = -dy_dt; boom(); }
		if (y < 16) { y = 16 + 16 - y; dy_dt = -dy_dt; boom(); }

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
			camera->SetYPosition(map_height - cam_height_2);
		else if (camera->willCollideNorth(v_displacement))
			camera->SetYPosition(0 + cam_height_2);
		else camera->SetYPosition(cam_y + v_displacement);
		

		

		portal->Try(myPlayer);
		//myPlayer->setPosition(x + dx_dt, y + dy_dt);
		myPlayer->getAnimation()->Update(dt);

		//camera->SetXPosition(x + dx_dt);
		//camera->SetYPosition(y + dy_dt);

		// Now we let the Gui object perform its logic.
		//gui->logic();
		return false;
	}

	bool RenderFunc(){
		// Next we begin a scene.
		hge->Gfx_BeginScene();
		hge->Gfx_Clear(0);
		// Now we let the Gui object draw itself.
		//gui->draw();

		//bg->RenderStretch(0, 0, 800, 600);

		camera->RenderScene();
		portalSprite->Render(0, 0);
		float x, y;
		hge->Input_GetMousePos(&x, &y);
		mouseSprite->Render(x, y);

		//fnt->printf(5, 100, HGETEXT_LEFT, "colliding north? %d", int(camera->willCollideSouth(0.0f)));
		//fnt->printf(5, 100, HGETEXT_LEFT, "colliding north? %d", int(camera->willCollideEast(0.0f)));
		//fnt->printf(5, 100, HGETEXT_LEFT, "colliding north? %d", int(camera->willCollideWest(0.0f)));
		fnt->printf(5, 100, HGETEXT_LEFT, "colliding north? %d", int(camera->willCollideNorth(0.0f)));
		fnt->printf(5, 130, HGETEXT_LEFT, "camera xposn %d, yposn %d.", int(camera->GetXPosition()), int(camera->GetYPosition()));
		fnt->printf(5, 165, HGETEXT_LEFT, "poring xposn %d, yposn %d.", int(myPlayer->GetXPosition()), int(myPlayer->GetYPosition()));
		fnt->printf(5, 210, HGETEXT_LEFT, "speed %d.", int(myPlayer->GetAcceleration()));

		//Render GUI
		gui->HgeFrameFunc();

		// Finally we end the scene causing the screen to be updated.
		hge->Gfx_EndScene();

		return false;
	}

	void init() {

#pragma region init
		hge = hgeCreate(HGE_VERSION);
		// Load settings
		Settings::load(TEXT("config.txt"));
		bool b_windowed = true;
		hge->System_SetState(HGE_LOGFILE, "resources/game.log");
		hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
		hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
		hge->System_SetState(HGE_TITLE, "Project 3: basic animation and map loading");
		hge->System_SetState(HGE_WINDOWED, b_windowed);
		hge->System_SetState(HGE_SCREENBPP, 32);
		hge->System_SetState(HGE_FPS, 60);

		assert(hge->System_Initiate());
			//throw GCN_EXCEPTION("Unable to initialize HGE: " + std::tstring(hge->System_GetErrorMessage()));

		gui = new GUI();
		gui->registerWindow(hge->System_GetState(HGE_HWND), hge, b_windowed);
		// Load savedata
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
#pragma endregion init


		std::cout << "Loading Map \"desert\"\n";
// 		world["desert"] = new TileMap("map1.tmx");
// 		world["little"] = new TileMap("map2.tmx");
// 		world["desert"]->Load();

		myPlayer->setZone(TEXT("desert"));


		hPortal = hge->Texture_Load("resources/gems.png");
		portalSprite = new hgeSprite(hPortal, 0, 31, 32, 32);
		portal = new Trigger_Portal(0);



// 		camera = new Camera();
// 		camera->SetXPosition(myPlayer->GetXPosition());
// 		camera->SetYPosition(myPlayer->GetYPosition());
// 		camera->SetDisplayLocation(0, 0);
// 		camera->SetDisplaySize_1(800, 600);
// 		camera->SetTarget(myPlayer);
// 		camera->Enter(world["desert"]);
// 		camera->SetWorld(world);
// 		camera->SetZone("desert");

		/*
		if (tileset->GetTiles().size() > 0) {
			// Get a tile from the tileset.
			const Tmx::Tile *tile = *(tileset->GetTiles().begin());

			// Print the properties of a tile.
			std::map< std::tstring, std::tstring > list = tile->GetProperties().GetList();
			std::map< std::tstring, std::tstring >::iterator iter;
			for (iter = list.begin(); iter != list.end(); ++iter) {
				printf("%s = %s\n", iter->first.c_str(), iter->second.c_str());
			}
		}
		*/
		//hge->System_SetState(HGE_FRAMEFUNC, MenuFrameFunc);
		//hge->System_SetState(HGE_RENDERFUNC, MenuRenderFunc);

		// Set up the quad we will use for background animation
		quad.blend = BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;

		for (int i = 0; i<4; i++)
		{
			// Set up z-coordinate of vertices
			quad.v[i].z = 0.5f;
			// Set up color. The format of DWORD col is 0xAARRGGBB
			quad.v[i].col = 0xFFFFFFFF;
		}

		quad.v[0].x = 0; quad.v[0].y = 0;
		quad.v[1].x = 800; quad.v[1].y = 0;
		quad.v[2].x = 800; quad.v[2].y = 600;
		quad.v[3].x = 0; quad.v[3].y = 600;

		quad.tex = hge->Texture_Load("resources/bg.png");
		hMouseTexture = hge->Texture_Load("resources/cursor.png");
		snd = hge->Effect_Load("resources/menu.wav");
		fnt = new hgeFont("resources/font1.fnt");
		fnt->SetColor(0xFF000000);

		mouseSprite = new hgeSprite(hMouseTexture, 0, 0, 32, 32);
		
		anitex = hge->Texture_Load("resources/aninew.png");
		ani = new hgeAnimation(anitex, 6, 6, 0, 0, 38, 46);
		ani->SetHotSpot(16, 16);
		ani->Play();

		myPlayer->setAnimation(ani);
	}

	void run() {
		hge->System_Start();
	}

	void halt() {
		std::fstream savedata("resources\\savedata.txt", std::ofstream::out, std::ofstream::trunc);
		if (savedata.is_open()) {
			float x, y;
			x = myPlayer->GetXPosition();
			y = myPlayer->GetYPosition();
			savedata << x;
			savedata << " ";
			savedata << y;
			savedata.close();
		}

		delete fnt;
		delete mouseSprite;
		delete ani;
		delete camera;
		delete portal;
		delete portalSprite;
		delete myPlayer;
		hge->Texture_Free(hPortal);
		hge->Texture_Free(hMouseTexture);
		hge->Texture_Free(anitex);
		hge->Texture_Free(quad.tex);
		hge->Effect_Free(snd);

		delete world[TEXT("desert")];
		delete world[TEXT("little")];
		


		//delete gui;
		//delete imageLoader;
		//delete input;
		//delete graphics;
		gui->shutdown();
		delete gui;
		gui = nullptr;
		//hge->System_Shutdown();
		hge->Release();
	}
	
	bool MenuFrameFunc() {
		float dt = hge->Timer_GetDelta();
		static float t = 0.0f;
		float tx, ty;
		hge->Input_GetMousePos(&mouseX, &mouseY);
		//int id;
		static int lastid;

		// Here we update our background animation
		t += dt;
		tx = 50 * cosf(t / 60);
		ty = 50 * sinf(t / 60);

		quad.v[0].tx = tx;        quad.v[0].ty = ty;
		quad.v[1].tx = tx + 800 / 64; quad.v[1].ty = ty;
		quad.v[2].tx = tx + 800 / 64; quad.v[2].ty = ty + 600 / 64;
		quad.v[3].tx = tx;        quad.v[3].ty = ty + 600 / 64;

		return false;
	}

	bool MenuRenderFunc() {
		// Render graphics
		hge->Gfx_BeginScene();
		hge->Gfx_RenderQuad(&quad);
		fnt->SetColor(0xFFFFFFFF);
		fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d", hge->Timer_GetDelta(), hge->Timer_GetFPS());
		//fnt->printf(5, 60, HGETEXT_LEFT, "Focus = %d, id = %d, count = %d, keystate= %d", gui->GetFocus(), gui->Update(0), count, hge->Input_GetKeyState(HGEK_ESCAPE));
		hge->Gfx_EndScene();

		return false;
	}
}
