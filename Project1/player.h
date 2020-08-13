#pragma once

#include "game_object.h"

class CPlayer : public CGameObject
{

private:
	class CModel* m_Model;
	D3DXVECTOR3 m_Vecter;
	D3DXVECTOR3 m_OldPosition;

	float m_Move;

	int MMP;//Map_Make_Point

public:
	CPlayer() {}
	~CPlayer() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();
	
};