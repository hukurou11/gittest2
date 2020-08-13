#pragma once



class CGameObject
{
protected:
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;
	bool m_Destory = false;

public:
	CGameObject() {}
	virtual ~CGameObject() {}

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	D3DXVECTOR3 GetPosision() { return m_Position; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale() { return m_Scale; }

	void SetPosision(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; }


	void SetDestory() { m_Destory = true; }

	bool Destory()
	{
		if (m_Destory)
		{
			Uninit();
			delete this;
			return true;
		}

		else
		{
			return false;
		}
	}
};
