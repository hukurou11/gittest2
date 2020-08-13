#pragma once

#include "game_object.h"

class CUI : public CGameObject
{
protected:
	D3DXVECTOR2 m_UIPosition;
	D3DXVECTOR2 m_UISize;
	D3DXVECTOR2 m_UItexStartPosition;
	D3DXVECTOR2 m_UItexSize;
	bool m_Mapflg = false;		// true�̏ꍇMap����

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*		m_Textuer = NULL;

public:
	CUI() {}
	virtual ~CUI() {}

	// �q�N���XInit()�I�[�o�[���C�h�֐��擪��CUI::Init()�Ăяo��
	virtual void Init(const char* file, D3DXVECTOR2 Position = D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2 Size = D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2 texstart = D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2 texsize = D3DXVECTOR2(0.0f, 0.0f));

	// �q�N���XUninit()�I�[�o�[���C�h�֐�������CUI::Unitit()�Ăяo��
	virtual void Uninit();

	virtual void Update() = 0;
	virtual void Draw();

	D3DXVECTOR2 GetPosision() { return m_UIPosition; }
	D3DXVECTOR2 GetSize() { return m_UISize; }
	D3DXVECTOR2 GettexStartPosition() { return m_UItexStartPosition; }
	D3DXVECTOR2 GettexSize() { return m_UItexSize; };

	void SetPosision(D3DXVECTOR2 Position) { m_UIPosition = Position; }
	void SetSize(D3DXVECTOR2 Size) { m_UISize = Size; }
	void SettexStartPosision(D3DXVECTOR2 Position) { m_UItexStartPosition = Position; }
	void SettexSize(D3DXVECTOR2 Size) { m_UItexSize = Size; }

	void SetMapflg(bool flg) { m_Mapflg = flg; }
};