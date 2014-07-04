#pragma once
#include "GameEntity.h"
#include "hgeanim.h"
class NPC : GameEntity {
public:
	NPC();
	~NPC();

	void Update(float _dt);
	void Render(float _x_position, float _y_position);
	void SetAnimation(hgeAnimation* _m_pAnim) { m_pAnim = _m_pAnim; }

private:
	hgeAnimation* m_pAnim;
};

NPC::NPC()
{
}

NPC::~NPC()
{
}