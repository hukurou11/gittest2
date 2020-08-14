#include "result.h"
#include "manager.h"
#include "input2.h"
#include "scene.h"
#include "title.h"
#include "fade.h"
#include "result_background.h"

void CResult::Init()
{
	AddGameObject<CCamera>(0);
	AddGameObject<CResult_UI>(2);
}

void CResult::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CFade::SetFade<CTitle>();
	}
}