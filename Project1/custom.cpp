#include "custom.h"
#include "input2.h"
#include "manager.h"
#include "camera.h"
#include "fade.h"
#include "game.h"
#include "UI.h"
#include "custom_background.h"

void CCustom::Init()
{
	AddGameObject<CCamera>(0);
	AddGameObject<CCustom_UI>(2);
}

void CCustom::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		//CManager::SetScene<CGame>();
		CFade::SetFade<CGame>();
	}
}