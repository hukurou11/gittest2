#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "wall.h"
#include "input.h"
#include "input2.h"
#include "scene.h"
#include "bullet.h"

class CModel* CWall::m_Model;

void CWall::Load()
{
	m_Model = new CModel();
	m_Model->Load("asset\\model\\cube.obj");

	assert(m_Model);
}

void CWall::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void CWall::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.5f, 1.0f);

	m_HP = 1;
}

void CWall::Uninit()
{

}

void CWall::Update() 
{
	if(m_HP <= 0)
	SetDestory();
}

void CWall::Draw()
{
	//
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x , m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();

}

