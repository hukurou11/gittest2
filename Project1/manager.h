#pragma once


class CManager
{
private:
	static class CScene*		m_Scene;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static class 	CScene* GetScene() { return m_Scene; }


};