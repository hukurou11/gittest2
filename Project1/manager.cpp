
#include "main.h"
#include "manager.h"
#include "input2.h"
#include "renderer.h"
#include "scene.h"
#include "title.h"
#include "fade.h"


#include <list>

CScene* CManager::m_Scene = NULL;

void CManager::Init()
{
	CRenderer::Init();

	CInput::Init();

	CFade::Init();

	CManager::SetScene<CTitle>();
}

void CManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	CFade::Uninit();

	CInput::Uninit();

	CRenderer::Uninit();
}

void CManager::Update()
{
	CInput::Update();

	m_Scene->Update();

	CFade::Update();
}

void CManager::Draw()
{
	CRenderer::Begin();

	LIGHT light;
	light.Enable = false;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetLight(light);

	m_Scene->Draw();

	CFade::Draw();

	CRenderer::End();

}

void CManager::SetScene(CScene* scene)
{
	if (m_Scene != NULL)
	{
		m_Scene->Uninit();
		delete m_Scene;
		//CResource::UnloadAll();
	}
	m_Scene = scene;
	scene->Init();
}