#pragma once

#include "game_object.h"

class CPolygon : public CGameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*		m_Textuer = NULL;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};


