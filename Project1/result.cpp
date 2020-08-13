#include "result.h"
#include "manager.h"
#include "input2.h"
#include "scene.h"
#include "title.h"

void CResult::Init()
{
	AddGameObject<CCamera>(0);
}

void CResult::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CTitle>();
	}
}