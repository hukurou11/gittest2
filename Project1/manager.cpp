
#include "main.h"
#include "manager.h"
#include "input2.h"
#include "renderer.h"
#include "scene.h"
#include "title.h"
#include "fade.h"


#include <list>

//CCamera* g_Camera;
///*CPolygon**/CGameObject g_Polygon;
///*CField**/CGameObject* g_Field;
///*CPlayer**/ CGameObject * g_Player;

//CGameObject* g_GameObject[3];

//std::list<CGameObject*> g_GameObject;	// STL‚ÌƒŠƒXƒg\‘¢
//CScene* g_Scene;

CScene* CManager::m_Scene = NULL;

void CManager::Init()
{

	CRenderer::Init();

	CInput::Init();

	CFade::Init();

	//g_Camera = new CCamera;
	//g_Camera->Init();
	//
	//g_Field = new CField;
	//g_Field->Init();
	//
	//g_Polygon = new CPolygon;
	//g_Polygon->Init();
	//
	//g_Player = new CPlayer;
	//g_Player->Init();
	//
	//g_GameObject[0] = new CField();
	//g_GameObject[0]->Init();
	//
	//g_GameObject[1] = new CPlayer();
	//g_GameObject[1]->Init();
	//
	//g_GameObject[2] = new CPolygon();
	//g_GameObject[2]->Init();
	//
	//CField* field = new CField();
	//field->Init();
	//g_GameObject.push_back( field );
	//
	//CPlayer* player = new CPlayer();
	//player->Init();
	//g_GameObject.push_back( player );
	//
	//CPolygon* polygon = new CPolygon();
	//polygon->Init();
	//g_GameObject.push_back( polygon );

	SetScene<CTitle>();
	//SetFade<CTitle>();
}

void CManager::Uninit()
{
	//for(int i = 0; i < 3; i++)
	//{
	//	g_GameObject[i]->Uninit();
	//	delete g_GameObject[i];
	//}
	//
	//for (CGameObject* object : g_GameObject)
	//{
	//	object->Uninit();
	//	delete object;
	//}
	//
	//g_GameObject.clear();
	//
	//g_Camera->Uninit();
	//delete g_Camera;

	m_Scene->Uninit();
	delete m_Scene;

	CFade::Uninit();

	CInput::Uninit();

	CRenderer::Uninit();

}

void CManager::Update()
{
	CInput::Update();

	//g_Camera->Update();
	//for (int i = 0; i < 3; i++) 
	//{
	//	g_GameObject[i]->Update();
	//}
	//
	//for(CGameObject* object : g_GameObject)
	//{
	//	object->Update();
	//}

	m_Scene->Update();

	CFade::Update();
}

void CManager::Draw()
{

	CRenderer::Begin();

	//g_Camera->Draw();

	LIGHT light;
	light.Enable = false;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetLight(light);

	//g_Field->Draw();
	//g_Player->Draw();
	//
	//light.Enable = false;
	//CRenderer::SetLight(light);
	//
	//g_Polygon->Draw();
	//
	//for(int i = 0; i < 3; i++)
	//{
	//	g_GameObject[i]->Draw();
	//}
	//
	//for (CGameObject* object : g_GameObject)
	//{
	//	object->Draw();
	//}

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