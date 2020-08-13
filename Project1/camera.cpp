#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input2.h"
#include "scene.h"
#include "player.h"

void CCamera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -3.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void CCamera::Uninit()
{

}

void CCamera::Update()
{
	CScene* scene = CManager::GetScene();
	CPlayer* player = scene->GetGameObject<CPlayer>(1);

	PlayerPos = player->GetPosision();


	m_Target = PlayerPos;
	m_Target.y = PlayerPos.y + 2;

//	m_Position.z = PlayerPos.z - 1;
	m_Position.z = PlayerPos.z - 3;
	m_Position.x = PlayerPos.x;
}

void CCamera::Draw()
{
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	CRenderer::SetViewMatrix(&m_ViewMatrix);

	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);


	CRenderer::SetProjectionMatrix(&projectionMatrix);
}

