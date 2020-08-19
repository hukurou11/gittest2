#pragma once

#include "game_object.h"

class CPlayer :public CGameObject//継承(インヘリタンス)
{
private:

	//前方宣言(ポインタ変数の有効)
	//各パーツモデルの読み込み
	class CModel* m_HEAD;			//頭パーツ
	class CModel* m_BODY;			//体パーツ
	class CModel* m_LEFTSHOULDER;	//左肩パーツ		
	class CModel* m_RIGHTSHOULDER;	//右肩パーツ
	class CModel* m_RIGHTARM;		//右腕パーツ
	class CModel* m_LEFTARM;		//左腕パーツ
	class CModel*m_RIGHTELBOW;		//右肘パーツ
	class CModel*m_LEFTELBOW;		//左肘パーツ
	class CModel*m_RIGHTHAND;		//右手パーツ
	class CModel*m_LEFTHAND;		//左手パーツ
	class CModel*m_RIGHTKNEE;		//右膝パーツ
	class CModel*m_LEFTKNEE;		//左膝パーツ
	class CModel* m_LEFTLEG;		//左足パーツ
	class CModel* m_RIGHTLEG;		//右足パーツ
public:
	CPlayer() {}
	~CPlayer() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();

	friend class CScene;
};