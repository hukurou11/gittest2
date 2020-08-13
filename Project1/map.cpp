
#include <stdlib.h>
#include "main.h"
#include "wall.h"
#include "wall2.h"
#include "scene.h"
#include "map.h"
#include "manager.h"
#include "block.h"

int Map[Map_WIDTH][Map_HEIGHT];

void Make_Map(int x, int y);

struct 
{
	int x;
	int y;
} dir[] = 
{
	{0, -1}, /** UP */
	{0, 1},  /** DOWN */
	{-1, 0}, /** LEFT */
	{1, 0}   /** RIGHT */
};

void Map_Init()
{//マップ初期化
	int x, y;
	for (y = 0; y < Map_HEIGHT; y++)
		for (x = 0; x < Map_WIDTH; x++)
			Map[x][y] = 1;
}

int rand_odd(int mod)
{//奇数のみのランダム関数
	srand((int)time(NULL));
	int r = 1 + (rand() % mod);
	if (r % 2 == 0)
		r++;
	if (r > mod)
		r -= 2;
	return r;
}

void MAP()
{
	//開始位置の決定
	int x = rand_odd(Map_WIDTH - 2);
	int y = rand_odd(Map_HEIGHT - 2);
	
	//道の制作
	Make_Map(x, y);
}

void Make_Map(int x, int y)
{
	int d = rand() % 4;
	int dd = d;

	while (true)
	{
		int px = x + dir[d].x * 2;
		int py = y + dir[d].y * 2;

		if (px < 0 || px >= Map_WIDTH || py < 0 || py >= Map_HEIGHT || Map[px][py] != 1)
		{
			d++;
			if (d == 4)
				d = 0;
			if (d == dd)
				return;
			continue;
		}

		Map[x + dir[d].x][y + dir[d].y] = 0;
		Map[px][py] = 0;
		Make_Map(px, py);
		d = dd = rand() % 4;
	}
}

void Put_Wall(int Z)
{
	CScene* scene = CManager::GetScene();

	for (int z = 0; z < Map_HEIGHT; z++)
	{
		for (int x = 0; x < Map_WIDTH; x++)
		{
			if (Map[x][z] == 1)
				scene->AddGameObject <CWall>(1)->SetPosision(D3DXVECTOR3(x - Map_WIDTH / 2, 0, z + Z));
			if (Map[x][z] == 2)
				scene->AddGameObject <CWall2>(1)->SetPosision(D3DXVECTOR3(x, 0, z + Z));
		}
	}
}

void CMap::Load()
{
	Map_Init();
	MAP();
	Put_Wall(0);

	Map_Init();
	MAP();
	Put_Wall(Map_HEIGHT - 1);
}

void CMap::SetMap(int Z)
{
	Map_Init();
	MAP();
	Put_Wall(Z);
}


//
//int Map[10][10] =
//{
//	{1,1,1,1,1,1,1,1,1,1},
//	{1,0,0,0,0,0,0,0,0,1},
//	{1,1,1,2,0,1,1,1,0,1},
//	{1,2,1,2,0,1,2,1,0,1},
//	{1,1,2,2,0,1,1,2,0,1},
//	{1,1,1,2,0,1,2,1,0,1},
//	{1,2,2,2,0,1,2,2,0,1},
//	{1,0,0,0,0,0,0,0,0,1},
//	{1,1,1,1,1,1,1,1,1,1},
//};
//int Map[1][1] = { 1 };
/*
void CMap::Load()
{
	CScene* scene = CManager::GetScene();

	for (int i = 0;i < 10;i++)
	{
		for (int j = 0;j < 10;j++)
		{
			if (Map[i][j] == 1)
				scene->AddGameObject <CWall>(1)->SetPosision(D3DXVECTOR3(j, 0, i));
			if (Map[i][j] == 2)
				scene->AddGameObject <CWall2>(1)->SetPosision(D3DXVECTOR3(j, 0, i));
		}
	}
}
*/