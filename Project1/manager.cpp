
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "input2.h"
#include "scene.h"

//CScene* g_Scene;

CScene* CManager::m_Scene = NULL;

void CManager::Init()
{

	CRenderer::Init();
	CInput::Init();

	m_Scene = new CScene();
	m_Scene->Init();

}

void CManager::Uninit()
{

	Keyboard_Finalize();
	
	GamePad_Finalize();

	m_Scene->Uninit();
	delete m_Scene;
	
	CInput::Uninit();
	CRenderer::Uninit();
	
}

void CManager::Update()
{
	CInput::Update();

	m_Scene->Update();
	

	Keyboard_Update();
	
	GamePad_Update();

}

void CManager::Draw()
{

	CRenderer::Begin();

	
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f,-1.0f,1.0f,0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetLight(light);


	m_Scene->Draw();
	

	CRenderer::End();

}
