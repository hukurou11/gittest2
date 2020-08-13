#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "wall2.h"
#include "input.h"
#include "input2.h"
#include "scene.h"
#include "bullet.h"

class CModel* CWall2::m_Model;

void CWall2::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\cube.obj");

	assert(m_Model);
}

void CWall2::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CWall2::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 2.0f, 1.0f);
	m_HP = 2;
}

void CWall2::Uninit()
{

}

void CWall2::Update()
{
	if (m_HP == 1)
		m_Scale.y = 1;

	if (m_HP <= 0)
		SetDestory();
}

void CWall2::Draw()
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

