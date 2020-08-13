#pragma once

#include "game_object.h"
#include <time.h>

#define Map_WIDTH			25
#define Map_HEIGHT			21

class CMap : public CGameObject
{
private:
	
public:
	CMap() {}
	~CMap() {}

	static void Load();
	static void SetMap(int Z);
	//void Unload();
};



