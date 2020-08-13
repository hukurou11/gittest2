#pragma once

#include "game_object.h"

class CExplosion : public CGameObject
{
private:
	static ID3D11Buffer*				m_VertexBuffer;
	static ID3D11ShaderResourceView*		m_Textuer;

	int m_Caunt;

public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


