#include "title.h"
#include "input2.h"
#include "manager.h"
#include "camera.h"
#include "fade.h"
#include "game.h"

void CTitle::Init()
{
	AddGameObject<CCamera>(0);
}

void CTitle::Update()
{
	CScene::Update();

	if(CInput::GetKeyTrigger(VK_RETURN))
	{
		//CManager::SetScene<CGame>();
		CFade::SetFade<CGame>();
	}
}