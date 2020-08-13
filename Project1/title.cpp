#include "title.h"
#include "input2.h"
#include "manager.h"
#include "game.h"
#include "camera.h"
#include "game_object.h"

void CTitle::Init()
{
	AddGameObject<CCamera>(0);
}

void CTitle::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CGame>();
	}
}