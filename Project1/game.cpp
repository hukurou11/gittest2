#include "game.h"
#include "input2.h"
#include "manager.h"
#include "scene.h"
#include "result.h"

void CGame::Init()
{
	CBullet::Load();
	CExplosion::Load();
	CEffect::Load();


	CMap::Load();
	CWall::Load();
	CWall2::Load();

	AddGameObject<CCamera>(0);
	AddGameObject<CField>(1);
	AddGameObject<CPlayer>(1);

	/*	AddGameObject<CWall>(1);
		AddGameObject<CWall>(1)->SetPosision(D3DXVECTOR3( 1.0f, 0.0f, 0.0f));
		AddGameObject<CWall>(1)->SetPosision(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));*/

		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(-5.0f, 0.0f, 5.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(5.0f, 0.0f, 5.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(-10.0f, 0.0f, 15.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(0.0f, 0.0f, 15.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(8.0f, 0.0f, 15.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(-4.0f, 0.0f, 15.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(0.0f, 0.0f, 15.0f));
		//AddGameObject<CEnemy>(1)->SetPosision(D3DXVECTOR3(9.0f, 0.0f, 15.0f));

//		AddGameObject<CPolygon>(2);
}

void CGame::Uninit()
{
	CScene::Uninit();

	CBullet::Unload();
	CExplosion::Unload();
	CEffect::Unload();
	CWall::Unload();
	CWall2::Unload();
}

void CGame::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CResult>();
	}
}