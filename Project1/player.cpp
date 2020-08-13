#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "player.h"
#include "input.h"
#include "input2.h"
#include "scene.h"
#include "bullet.h"
#include "effect.h"
#include "map.h"

void CPlayer::Init()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\cube.obj");

	assert(m_Model);

	m_Position = D3DXVECTOR3(0.0f, 0.0f, -10.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.6f, 1.0f, 0.6f);
	m_Vecter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CPlayer::m_Move = false;
	MMP = (Map_HEIGHT - 1);
}

void CPlayer::Uninit()
{
	m_Model->Unload();
	delete m_Model;
}

void CPlayer::Update()
{
	if (m_Position.z >= MMP)
	{
		MMP += (Map_HEIGHT - 1);
		CMap::SetMap(MMP);
	}


	m_OldPosition = m_Position;

	if (CInput::GetKeyPress('W'))
	{

		m_Position.z += cosf(m_Rotation.y) * 0.1;
		m_Position.x -= sinf(m_Rotation.y) * 0.1;
	}
	
	if (CInput::GetKeyPress('S'))
	{

		m_Position.z -= cosf(m_Rotation.y) * 0.1;
		m_Position.x += sinf(m_Rotation.y) * 0.1;
	}

	if (CInput::GetKeyPress('A'))
	{
		CPlayer::m_Move = true;

		m_Position.x -= 0.1f;
		//			m_Rotation.y += 0.01f;

		if (m_Vecter.z < 0.5f)
		{
			m_Vecter.z += 0.05f;
		}

		if (m_Vecter.y > -0.3f)
		{
			m_Vecter.y -= 0.05f;
		}
	}

	else if (CInput::GetKeyPress('D'))
	{
		CPlayer::m_Move = true;
		m_Position.x += 0.1f;
		//			m_Rotation.y -= 0.01f;

		if (m_Vecter.z > -0.5f)
		{
			m_Vecter.z -= 0.05f;
		}

		if (m_Vecter.y < 0.3f)
		{
			m_Vecter.y += 0.05f;
		}
	}

	else
	{
		CPlayer::m_Move = false;
	}


	if (CInput::GetKeyPress(VK_RETURN))
	{
		m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Vecter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		CScene* scene = CManager::GetScene();
		scene->AddGameObject<CBullet>(1)->SetPosision(m_Position);
	}

	if (!CPlayer::m_Move)
	{
		m_Vecter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}


	if (CInput::GetKeyTrigger('G'))
	{
		CScene* scene = CManager::GetScene();
		scene->AddGameObject<CEffect>(1)->SetPosision(m_Position);
	}

	if (CInput::GetKeyRelease('G'))
	{
		CScene* scene = CManager::GetScene();
		CEffect* effect = scene->GetGameObject<CEffect>(1);
		effect->SetDestory();
	}

	//“–‚½‚è”»’è
	CScene* scene = CManager::GetScene();
	std::vector<CWall*> wallList = scene->GetGameObjects<CWall>(1);
	std::vector<CWall2*> wall2List = scene->GetGameObjects<CWall2>(1);
/*
	for (CWall* wall : wallList)
	{
		D3DXVECTOR3 WallPosition = wall->GetPosision();

		D3DXVECTOR3 direction = m_Position - WallPosition;
		
		//X
		if (m_Position.x < m_OldPosition.x &&
			direction.x < 1.0f &&
			direction.z < 1.0f &&
			direction.z > -1.0f)
		{
			m_Position.x = m_OldPosition.x;
		}

		if (m_Position.x > m_OldPosition.x &&
			direction.x > -1.0f &&
			direction.z < 1.0f &&
			direction.z > -1.0f)
		{
			m_Position.x = m_OldPosition.x;
		}


		//Z

		if (m_Position.z < m_OldPosition.z &&
			direction.z < 1.0f &&
			direction.x < 1.0f &&
			direction.x > -1.0f)
		{
			m_Position.z = m_OldPosition.z;
		}

		if (m_Position.z > m_OldPosition.z &&
			direction.z > -1.0f &&
			direction.x < 1.0f &&
			direction.x > -1.0f)
		{
			m_Position.z = m_OldPosition.z;
		}



	/*	if (direction.x < 1.0f && direction.x > -1.0f)
		{
			if (direction.z < 1.0f && direction.z > -1.0f)
			{
				m_Position.x = m_OldPosition.x;
				m_Position.z = m_OldPosition.z;
			}
		}*/
		/*if (direction.x < 1.0f && direction.x > -1.0f)
		{
			if (direction.z < 1.0f && direction.z > -1.0f)
			{
				m_Position.x = m_OldPosition.x;
			}
		}
		
		if (direction.z < 1.0f && direction.z > -1.0f)
		{

			if (direction.x < 1.0f && direction.x > -1.0f)
			{
				m_Position.z = m_OldPosition.z;
			}
		}/
		//float length = D3DXVec3Length(&direction);
		/*if (length < 2.0f)
		{
			scene->AddGameObject<CExplosion>(1)->SetPosision(m_Position);

			wall->BlakeWall();
			SetDestory();
			return;
		}\/
	}*/
}

void CPlayer::Draw()
{
	//
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y + m_Vecter.y, m_Rotation.x + m_Vecter.x, m_Rotation.z + m_Vecter.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();

}

