#pragma once

#include "game_object.h"

class CCamera : public CGameObject
{

private:

	D3DXVECTOR3 m_Target;				//�����_
	D3DXVECTOR3 PlayerPos,PlayerVec;
	D3DXMATRIX m_ViewMatrix;
	
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; };
};
