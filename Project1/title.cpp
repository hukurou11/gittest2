#include "title.h"
#include "input2.h"
#include "manager.h"
#include "camera.h"
#include "custom.h"
#include "fade.h"
#include "UI.h"
#include "title_background.h"

void CTitle::Init()
{
	AddGameObject<CCamera>(0);
	AddGameObject<CTitle_UI>(2);
}

void CTitle::Update()
{
	CScene::Update();

	if(CInput::GetKeyTrigger(VK_RETURN))
	{
		//CManager::SetScene<CGame>();
		CFade::SetFade<CCustom>();
	}
}