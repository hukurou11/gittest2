#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "UI.h"
#include "title_background.h"

void CTitle_UI::Init()
{
	CUI::Init("asset/texture/title.png", D3DXVECTOR2(0.5 * SCREEN_WIDTH, 0.5f * SCREEN_HEIGHT), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
}

void CTitle_UI::Uninit()
{
	CUI::Uninit();
}

void CTitle_UI::Update()
{}