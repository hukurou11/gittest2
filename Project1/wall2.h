#pragma once

#include "game_object.h"
#include "block.h"

class CWall2 : public CBlock
{

private:
	static class CModel* m_Model;

	/*static class CModel* m_Model;

	int m_HP = 2;*/


public:
	CWall2() {}
	~CWall2() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();
	static void Load();
	static void Unload();

	void BlakeWall() { m_HP -= 1; }
};