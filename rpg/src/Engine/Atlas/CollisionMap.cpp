#include "CollisionMap.h"
#include "Camera.h"
#include "BoxComponent.h"

//Flags use to manage Drawing in Box2D
uint32 drawFlags = hgeB2Draw::e_shapeBit | hgeB2Draw::e_jointBit | hgeB2Draw::e_aabbBit;
// Prepare for simulation. Typically we use a time step of 1/60 of a
// second (60Hz) and 10 iterations. This provides a high quality simulation
// in most game scenarios.
float32 timeStep = 1.0f / 60.0f;
int32 velocityIterations = 6;
int32 positionIterations = 2;

CollisionMap::CollisionMap(const TCHAR* file_name)
{
	// parse map information from .tmx file.
	m_pHGE = hgeCreate(HGE_VERSION);
	const TCHAR* resourcePath = TEXT("resources/");
	std::tstring filePath = resourcePath;
	filePath.append(file_name);
	m_pMap_info = new Tmx::Map();

	ANSICHAR tempFilePath[100];
	wcstombs(tempFilePath, filePath.c_str(), 100);
	m_pMap_info->ParseFile(tempFilePath);

	m_width = m_pMap_info->GetWidth() * m_pMap_info->GetTileWidth();
	m_height = m_pMap_info->GetHeight() * m_pMap_info->GetTileHeight();

	//Init Box2D
	b2Vec2 gravity(0.0f, 0.0f);
	m_pHgeB2World = new hgeB2World(gravity);
	m_pHgeB2World->SetMapSize(m_width, m_height);
	m_pIhgeB2Draw = new hgeB2Draw(m_pHGE);
	m_pIhgeB2Draw->SetFlags(drawFlags);
	m_pIhgeB2Draw->SetMapHeight(m_width);
	m_pHgeB2World->SetDebugDraw(m_pIhgeB2Draw);

// 	BoxComponent* tempBox = new BoxComponent();
// 	tempBox->setX(P2M(500));
// 	tempBox->setY(P2M(100));
// 	tempBox->SetBoxTextent(1, 1);
// 	tempBox->RegisterWithBox2D(m_pHgeB2World);
// 	b2Vec2 vel = tempBox->m_pB2Body->GetLinearVelocity();
// 	vel.x -= 5;
// 	tempBox->m_pB2Body->SetType(b2_dynamicBody);
// 	tempBox->m_pB2Body->SetLinearVelocity(vel);
// 
// 	BoxComponent* tempBox1 = new BoxComponent();
// 	tempBox1->setX(P2M(200));
// 	tempBox1->setY(P2M(100));
// 	tempBox1->SetBoxTextent(1, 1);
// 	tempBox1->RegisterWithBox2D(m_pHgeB2World);
}

CollisionMap::~CollisionMap()
{
	Unload();
	delete m_pMap_info;
	m_pHGE->Release();
}

void CollisionMap::Update(float _dt) {
	m_pHgeB2World->Step(_dt, velocityIterations, positionIterations);
}

void CollisionMap::Render(Camera* _camera) {
	// translate camera position to screen top left corner
	int x, y;
	x = _camera->Get_Display_Width_2() - (int)_camera->GetXPosition();
	y = _camera->Get_Display_Height_2() - (int)_camera->GetYPosition();
	// translate camera position again if map is smaller than screen
	// center the content.
	if (m_width < _camera->Get_Display_Width_2() * 2)
		x = (_camera->Get_Display_Width_2() * 2 - m_width) / 2;
	if (m_height < _camera->Get_Display_Height_2() * 2)
		y = (_camera->Get_Display_Height_2() * 2 - m_height) / 2;

	m_pIhgeB2Draw->SetDrawPosition(x, y);
	m_pHgeB2World->DrawDebugData();
}

void CollisionMap::Load() {
	const Tmx::ObjectGroup* phyxgrp;
	//Init physics
	for (int i = 0; i < m_pMap_info->GetNumObjectGroups(); i++) {
		const Tmx::ObjectGroup* objgroup = m_pMap_info->GetObjectGroup(i);
		if (objgroup->GetName() == "Physics"){
			phyxgrp = objgroup;
			break;
		}
	}

	if (phyxgrp) {
		printf("Found physics obj group.\n");

		for (int j = 0; j < phyxgrp->GetNumObjects(); j++) {
			const Tmx::Object* obj = phyxgrp->GetObjectAtIdx(j);
			printf("Found an object.\n");

			const Tmx::Polygon* polygon = obj->GetPolygon();
			if (polygon) {
				printf("I'm a polygon.\n");
				printf("I have %d points.\n", polygon->GetNumPoints());

			}
			const Tmx::Polyline* polyline = obj->GetPolyline();
			if (polyline) {
				printf("I'm a polyline.\n");
				// Define the polyline body.
				b2BodyDef bodyDef;
				bodyDef.position.Set(P2M(obj->GetX()), P2M(m_pMap_info->GetHeight() * m_pMap_info->GetTileHeight() - obj->GetY()));
				b2Body* p_body = m_pHgeB2World->CreateBody(&bodyDef);
				b2FixtureDef fixtureDef;

				// Define a chain shape.
				b2ChainShape* p_chainShape = new b2ChainShape();

				b2Vec2* chainPoints = (b2Vec2*)malloc(sizeof(b2Vec2)* polyline->GetNumPoints());
				// translate the vertices
				for (int k = 0; k < polyline->GetNumPoints(); k++) {
					chainPoints[k] = b2Vec2(P2M(polyline->GetPoint(k).x), -P2M(polyline->GetPoint(k).y));
				}
				p_chainShape->CreateChain(chainPoints, polyline->GetNumPoints());

				fixtureDef.shape = p_chainShape;

				// Add the ground fixture to the ground body.
				p_body->CreateFixture(&fixtureDef);

				delete chainPoints;
				delete p_chainShape;
			}
			const Tmx::Ellipse* ellipse = obj->GetEllipse();
			if (ellipse) {
				printf("I'm an ellipse.\n");
			}
		}
	}
}
void CollisionMap::Unload() {
	delete m_pHgeB2World;
	delete m_pIhgeB2Draw;
}