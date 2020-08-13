#pragma once

#include "game_object.h"

class CBlock : public CGameObject
{

protected:

	int m_HP;

public:
	CBlock() {}
	~CBlock() {}

	//void Init();
	//void Uninit();
	//void Update();
	//void Draw();
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;


	void BlakeWall() { m_HP -= 1; }

};