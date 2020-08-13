#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "bullet.h"
#include "enemy.h"
#include "scene.h"
#include "explosion.h"
#include "wall.h"
#include "wall2.h"

class CModel* CBullet::m_Model;

void CBullet::Init()
{
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);

	CScene* scene = CManager::GetScene();
	CPlayer* player = scene->GetGameObject<CPlayer>(1);

	InitPos = player->GetPosision();
}

void CBullet::Uninit()
{

}

void CBullet::Update()
{

	CScene* scene = CManager::GetScene();
	std::vector<CWall*> wallList = scene->GetGameObjects<CWall>(1);
	std::vector<CWall2*> wall2List = scene->GetGameObjects<CWall2>(1);


	m_Position.z += 0.1f;
	if (m_Position.z > InitPos.z + 10)
	{
		SetDestory();
		scene->AddGameObject<CExplosion>(1)->SetPosision(m_Position);

		return;
	}

	for (CWall* wall : wallList)
	{
		D3DXVECTOR3 enemyaPosition = wall->GetPosision();

		D3DXVECTOR3 direction = m_Position - wall->GetPosision();
		float length = D3DXVec3Length(&direction);

		if (length < 0.5f)
		{
			scene->AddGameObject<CExplosion>(1)->SetPosision(m_Position);

			wall->BlakeWall();
			SetDestory();
			return;
		}
	}
	
	for (CWall2* wall : wall2List)
	{
		D3DXVECTOR3 wall2Position = wall->GetPosision();

		D3DXVECTOR3 direction = m_Position - wall->GetPosision();
		float length = D3DXVec3Length(&direction);

		if (length < 0.5f)
		{
			scene->AddGameObject<CExplosion>(1)->SetPosision(m_Position);

			wall->BlakeWall();
			SetDestory();
			return;
		}
	}
}


void CBullet::Draw()
{
	//
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();

}

void CBullet::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\torus.obj");
	assert(m_Model);
}

void CBullet::Unload()
{
	m_Model->Unload();
	delete m_Model;
}