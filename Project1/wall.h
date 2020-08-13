#pragma once

#include "game_object.h"
#include "block.h"

class CWall : public CBlock
{
private:
	static class CModel* m_Model;


public:
	CWall() {}
	~CWall() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();
	static void Load();
	static void Unload();

	void BlakeWall() { m_HP -= 1; }
};