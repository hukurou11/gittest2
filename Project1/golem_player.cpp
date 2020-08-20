#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "golem_player.h"
#include "input.h"
#include "input2.h"
#include "scene.h"

/////////////////////////////////
////変数宣言////////
////////////////////////////////
//マトリクス設定
D3DXMATRIX g_BODYandHED,
g_BODYandRSHOULDER,
g_BODYandLSHOULDER,
g_BODYandRLEG,
g_BODYandLLEG,
g_BODYandRARM,
g_BODYandLARM,
g_BODYandRELBOW,
g_BODYandLELBOW,
g_BODYandLHAND,
g_BODYandRHAND,
g_BODYandLKNEE,
g_BODYandRKNEE;
//プレイヤーデータ変数
static bool act;				//アクションフラグ
static bool punch;				//パンチモーション
static int count;				//アクションフリーズ制御
static bool g_MoveAct;			//動きを切り替える
static float RangeOfMotion_A;	//腕行動可動域A
static float RangeOfMotion_B;	//腕行動可動域B
//////////////////////////////////
///アクション関数
//////////////////////////////////

//歩行
void Move_Forward();		//前方歩行
void Move_Back();			//後方歩行
void Move_Left();			//左方歩行
void Move_Right();			//右方歩行

//コマンドアクション
void Break();				//破壊アクション


//胴体クラス（基本）
class Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX BodyMatrix, BodyScale, BodyRotation, BodyTransform;//姿勢行列保存
};

////////////////////
//関節パーツ宣言
///////////////////
//頭クラス（派生）
class CHed :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX HedMatrix, HedScale, HedRotation, HedTransform;//姿勢行列保存
};

//右肩クラス（派生）
class CR_Shoulder :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX RightShoulderMatrix, RightShoulderScale, RightShoulderRotation, RightShoulderTransform;//姿勢行列保存
};

//右腕クラス（派生）
class CR_ARM :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX RightArmMatrix, RightArmScale, RightArmRotation, RightArmTransform;//姿勢行列保存
};

//右肘クラス
class CR_ELBOW :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX RightElbowMatrix, RightElbowScale, RightElbowRotation, RightElbowTransform;//姿勢行列保存
};

//右手クラス
class CR_HAND :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX RightHandMatrix, RightHandScale, RightHandRotation, RightHandTransform;//姿勢行列保存
};

//右膝クラス
class CR_KNEE :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX RightKneeMatrix, RightKneeScale, RightKneeRotation, RightKneeTransform;//姿勢行列保存
};

//左肩クラス（派生）
class CL_Shoulder :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX LeftShoulderMatrix, LeftShoulderScale, LeftShoulderRotation, LeftShoulderTransform;//姿勢行列保存
};

//左腕クラス（派生）
class CL_ARM :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX LeftArmMatrix, LeftArmScale, LeftArmRotation, LeftArmTransform;//姿勢行列保存
};

//左肘クラス
class CL_ELBOW :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX LeftElbowMatrix, LeftElbowScale, LeftElbowRotation, LeftElbowTransform;//姿勢行列保存
};

//左手クラス
class CL_HAND :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX LeftHandMatrix, LeftHandScale, LeftHandRotation, LeftHandTransform;//姿勢行列保存
};

//左膝クラス
class CL_KNEE :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX LeftKneeMatrix, LeftKneeScale, LeftKneeRotation, LeftKneeTransform;//姿勢行列保存
};

//右足クラス（派生）
class CR_Leg :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX RightLegMatrix, RightLegScale, RightLegRotation, RightLegTrasnform;//姿勢行列保存
};

//左足クラス（派生）
class CL_Leg :public Body
{
public:
	D3DXVECTOR3 Position;//位置
	Vector3 Rotetion;//回転
	Vector3 Scale;			//拡縮
	D3DXMATRIX LeftLegMatrix, LeftLegScale, LeftLegRotation, LeftLegTransform;//姿勢行列保存
};


/////////////////////////
//パーツインスタンス
////////////////////////

Body body;					//体パーツインスタンス
CHed hed;					//頭パーツインスタンス
CR_Shoulder right_shoulder;	//右肩パーツインスタンス
CL_Shoulder left_shoulder;	//左肩パーツインスタンス
CR_ARM right_arm;			//右腕パーツインスタンス
CL_ARM left_arm;			//左腕パーツインスタンス
CR_ELBOW right_elbow;		//右肘パーツインスタンス
CL_ELBOW left_elbow;		//左肘パーツインスタンス
CR_HAND right_hand;			//右手パーツインスタンス
CL_HAND left_hand;			//左手パーツインスタンス
CR_KNEE right_knee;			//右膝パーツインスタンス
CL_KNEE left_knee;			//左膝パーツインスタンス
CR_Leg right_leg;			//右足パーツインスタンス
CL_Leg left_leg;			//左足パーツインスタンス

void CPlayer::Init()
{
	//モデル読み込み準備
	m_HEAD = new CModel();			//頭パーツ
	m_BODY = new CModel();			//体パーツ
	m_LEFTSHOULDER = new CModel();	//左肩パーツ
	m_RIGHTSHOULDER = new CModel();	//右肩パーツ
	m_RIGHTARM = new CModel();		//右腕パーツ
	m_LEFTARM = new CModel();		//左腕パーツ
	m_RIGHTELBOW = new CModel();	//右肘パーツ
	m_LEFTELBOW = new CModel();		//左肘パーツ
	m_RIGHTHAND = new CModel();		//右手パーツ
	m_LEFTHAND = new CModel();		//左手パーツ
	m_RIGHTKNEE = new CModel();		//右膝パーツ
	m_LEFTKNEE = new CModel();		//左膝パーツ
	m_LEFTLEG = new CModel();		//左足パーツ
	m_RIGHTLEG = new CModel();		//右足パーツ

	//各モデル読み込み
	m_HEAD->Load("asset\\model\\cube.obj");				//頭パーツ
	m_BODY->Load("asset\\model\\cube.obj");				//体パーツ
	m_LEFTSHOULDER->Load("asset\\model\\cube.obj");		//左肩パーツ
	m_RIGHTSHOULDER->Load("asset\\model\\cube.obj");	//右肩パーツ
	m_RIGHTARM->Load("asset\\model\\cube.obj");			//右腕パーツ
	m_LEFTARM->Load("asset\\model\\cube.obj");			//左腕パーツ
	m_RIGHTELBOW->Load("asset\\model\\cube.obj");		//右肘パーツ
	m_LEFTELBOW->Load("asset\\model\\cube.obj");		//左肘パーツ
	m_RIGHTHAND->Load("asset\\model\\cube.obj");		//右手パーツ
	m_LEFTHAND->Load("asset\\model\\cube.obj");			//左手パーツ
	m_RIGHTKNEE->Load("asset\\model\\cube.obj");		//右膝パーツ
	m_LEFTKNEE->Load("asset\\model\\cube.obj");			//左膝パーツ
	m_LEFTLEG->Load("asset\\model\\cube.obj");			//左足パーツ
	m_RIGHTLEG->Load("asset\\model\\cube.obj");			//右足パーツ

	//モデル初期値設定 
	//初期位置
	body.Position = Vector3(0.0f, 0.0f, 0.0f);																				//頭
	hed.Position = Vector3(body.Position.x, body.Position.y + 1.2f, body.Position.z);										//体
	left_shoulder.Position = Vector3(body.Position.x, body.Position.y + 1.5f, body.Position.z - 1.2f);						//左肩
	right_shoulder.Position = Vector3(body.Position.x, body.Position.y + 1.5f, body.Position.z + 1.2f);							//右肩
	right_arm.Position = Vector3(right_shoulder.Position.x, right_shoulder.Position.y - 0.3f, right_shoulder.Position.z);		//右腕
	left_arm.Position = Vector3(left_shoulder.Position.x, left_shoulder.Position.y - 0.3f, left_shoulder.Position.z);		//左腕
	right_elbow.Position = Vector3(right_arm.Position.x, right_arm.Position.y - 0.5f, right_arm.Position.z);				//右肘
	left_elbow.Position = Vector3(left_arm.Position.x, left_arm.Position.y - 0.5f, left_arm.Position.z);					//左肘
	right_hand.Position = Vector3(right_elbow.Position.x, right_elbow.Position.y - 0.3f, right_elbow.Position.z);			//右手
	left_hand.Position = Vector3(left_elbow.Position.x, left_elbow.Position.y - 0.3f, left_elbow.Position.z);				//左手
	right_knee.Position = Vector3(body.Position.x, body.Position.y - 0.1f, body.Position.z + 0.3f);									//右膝
	left_knee.Position = Vector3(body.Position.x, body.Position.y - 0.1f, body.Position.z - 0.3f);									//左膝
	left_leg.Position = Vector3(left_knee.Position.x, left_knee.Position.y - 0.1f, left_knee.Position.z);								//左足
	right_leg.Position = Vector3(right_knee.Position.x, right_knee.Position.y - 0.1f, right_knee.Position.z);							//右足

	//スケール（大きさ）
	body.Scale = Vector3(1.5f, 3.5f, 1.5f);				//体
	hed.Scale = Vector3(1.0f, 0.5f, 1.0f);				//頭
	left_shoulder.Scale = Vector3(1.0f, 0.2f, 1.0f);	//左肩
	right_shoulder.Scale = Vector3(1.0f, 0.2f, 1.0f);	//右肩
	right_arm.Scale = Vector3(0.8f, 0.5, 0.8f);			//右腕
	left_arm.Scale = Vector3(0.8f, 0.5f, 0.8f);			//左腕
	right_elbow.Scale = Vector3(0.2f, 0.2, 0.2f);		//右肘
	left_elbow.Scale = Vector3(0.2f, 0.2f, 0.2f);		//左肘
	right_hand.Scale = Vector3(0.5f, 1.0, 0.5f);		//右手
	left_hand.Scale = Vector3(0.5f, 1.0f, 0.5f);		//左手
	right_knee.Scale = Vector3(0.2f, 0.2, 0.2f);		//右膝
	left_knee.Scale = Vector3(0.2f, 0.2f, 0.2f);		//左膝
	left_leg.Scale = Vector3(0.5f, 1.5f, 0.5f);			//左足
	right_leg.Scale = Vector3(0.5f, 1.0f, 0.5f);		//右足

	//回転初期化
	body.Rotetion = Vector3(0.0f, 0.0f, 0.0f);				//体
	hed.Rotetion = Vector3(0.0f, 0.0f, 0.0f);				//頭
	left_shoulder.Rotetion = Vector3(0.0f, 0.0f, -3.2f);	//左肩
	right_shoulder.Rotetion = Vector3(0.0f, 0.0f, 3.2f);	//右肩
	right_arm.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//右腕
	left_arm.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//左腕
	right_elbow.Rotetion = Vector3(0.0f, 0.0f, 3.2f);		//右肘
	left_elbow.Rotetion = Vector3(0.0f, 0.0f, -3.2f);		//左肘
	right_hand.Rotetion = Vector3(0.0f, 0.0f, 3.2f);		//右手
	left_hand.Rotetion = Vector3(0.0f, 0.0f, -3.2f);		//左手
	right_knee.Rotetion = Vector3(0.0f, 0.0f, 3.2f);		//右膝
	left_knee.Rotetion = Vector3(0.0f, 0.0f, -3.2f);		//左膝
	left_leg.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//左足
	right_leg.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//右足

	//グローバル変数初期化
	count = 0;
	act = false;
	punch = false;
	g_MoveAct = false;			//動きを切り替える
	RangeOfMotion_A = 4.2f;	//腕行動可動域A
	RangeOfMotion_B = 2.0f;	//腕行動可動域B

}

void CPlayer::Uninit()
{
	m_HEAD->Unload();
	m_BODY->Unload();
	m_LEFTSHOULDER->Unload();
	m_RIGHTSHOULDER->Unload();
	m_RIGHTARM->Unload();
	m_LEFTARM->Unload();
	m_RIGHTELBOW->Unload();
	m_LEFTELBOW->Unload();
	m_RIGHTHAND->Unload();
	m_LEFTHAND->Unload();
	m_RIGHTKNEE->Unload();
	m_LEFTKNEE->Unload();
	m_LEFTLEG->Unload();
	m_RIGHTLEG->Unload();

	delete m_HEAD;
	delete m_BODY;
	delete m_LEFTSHOULDER;
	delete m_RIGHTSHOULDER;
	delete m_RIGHTARM;
	delete m_LEFTARM;
	delete m_RIGHTELBOW;
	delete m_LEFTELBOW;
	delete m_RIGHTHAND;
	delete m_LEFTHAND;
	delete m_RIGHTKNEE;
	delete m_LEFTKNEE;
	delete m_LEFTLEG;
	delete m_RIGHTLEG;
}


void CPlayer::Update()
{
	//パンチ入力時行動制限
	if (!punch)
	{
		//行動コマンド入力
		if (CInput::GetKeyPress(VK_UP))
		{
			Move_Forward();
		}
		if (CInput::GetKeyPress(VK_DOWN))
		{
			Move_Back();
		}
		if (CInput::GetKeyPress(VK_RIGHT))
		{
			Move_Right();
		}
		if (CInput::GetKeyPress(VK_LEFT))
		{
			Move_Left();
		}
		//行動コマンド離したときに歩行アクションリセット
		if (CInput::GetKeyRelease(VK_UP))
		{
			left_leg.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//左足
			right_leg.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//右足
		}
		if (CInput::GetKeyRelease(VK_DOWN))
		{
			left_leg.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//左足
			right_leg.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//右足
		}
		if (CInput::GetKeyRelease(VK_RIGHT))
		{
			left_leg.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//左足
			right_leg.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//右足
		}
		if (CInput::GetKeyRelease(VK_LEFT))
		{
			left_leg.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//左足
			right_leg.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//右足
		}
	}
	//攻撃コマンド入力
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		left_leg.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//左足
		right_leg.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//右足
		act = true;
	}
	//コマンドフラグ呼び出し
	if (act)
	{
		Break();
	}
	//アクションコマンドリセット
	if (right_arm.Position.x == -1.0f)
	{
		count++;
		if (count > 30)//パンチヒット時フリーズ時間
		{
			punch = false;
			act = false;
			right_arm.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//右腕
			left_arm.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//左腕
			right_elbow.Rotetion = Vector3(0.0f, 0.0f, 3.2f);		//右肘
			left_elbow.Rotetion = Vector3(0.0f, 0.0f, -3.2f);		//左肘
			right_hand.Rotetion = Vector3(0.0f, 0.0f, 3.2f);		//右手
			left_hand.Rotetion = Vector3(0.0f, 0.0f, -3.2f);		//左手
			right_arm.Position = Vector3(right_shoulder.Position.x, right_shoulder.Position.y - 0.3f, right_shoulder.Position.z);		//右腕
			right_elbow.Position = Vector3(right_arm.Position.x, right_arm.Position.y - 0.5f, right_arm.Position.z);				//右肘
			right_hand.Position = Vector3(right_elbow.Position.x, right_elbow.Position.y - 0.3f, right_elbow.Position.z);			//右手
			left_hand.Position = Vector3(left_elbow.Position.x, left_elbow.Position.y - 0.3f, left_elbow.Position.z);
			count = 0;
		}
	}
	//デバッグキー入力
	if (CInput::GetKeyPress(VK_BACK))
	{
		right_shoulder.Rotetion.z = 0.1f;
		right_arm.Position.x += 0.03f;
		right_elbow.Rotetion.z = 5.0f;
		right_elbow.Position.x += 0.03f;
		right_hand.Rotetion.z = 5.0f;
		right_hand.Position.y = right_elbow.Position.y - 0.4f;
		right_hand.Position.x += 0.03f;
	}
	//Body(親)の姿勢行列を設定
	D3DXMatrixScaling(&body.BodyScale, body.Scale.x, body.Scale.y, body.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&body.BodyRotation, body.Rotetion.y, body.Rotetion.x, body.Rotetion.z);
	D3DXMatrixTranslation(&body.BodyTransform, body.Position.x, body.Position.y, body.Position.z);
	//body(親)の姿勢行列保存
	body.BodyMatrix = body.BodyScale * body.BodyRotation*body.BodyTransform;

	//Hed(子)の姿勢行列を設定
	D3DXMatrixScaling(&hed.HedScale, hed.Scale.x, hed.Scale.y, hed.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&hed.HedRotation, hed.Rotetion.y, hed.Rotetion.x, hed.Rotetion.z);
	D3DXMatrixTranslation(&hed.HedTransform, hed.Position.x, hed.Position.y, hed.Position.z);
	//hed(子)の姿勢行列保存
	hed.HedMatrix = hed.HedScale * hed.HedRotation*hed.HedTransform;

	//RightShoulder(子)の姿勢行列を設定
	D3DXMatrixScaling(&right_shoulder.RightShoulderScale, right_shoulder.Scale.x, right_shoulder.Scale.y, right_shoulder.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&right_shoulder.RightShoulderRotation, right_shoulder.Rotetion.y, right_shoulder.Rotetion.x, right_shoulder.Rotetion.z);
	D3DXMatrixTranslation(&right_shoulder.RightShoulderTransform, right_shoulder.Position.x, right_shoulder.Position.y, right_shoulder.Position.z);
	//RightShoulder(子)の姿勢行列保存
	right_shoulder.RightShoulderMatrix = right_shoulder.RightShoulderScale * right_shoulder.RightShoulderRotation*right_shoulder.RightShoulderTransform;

	//LeftShoulder(子)の姿勢行列を設定
	D3DXMatrixScaling(&left_shoulder.LeftShoulderScale, left_shoulder.Scale.x, left_shoulder.Scale.y, left_shoulder.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&left_shoulder.LeftShoulderRotation, left_shoulder.Rotetion.y, left_shoulder.Rotetion.x, left_shoulder.Rotetion.z);
	D3DXMatrixTranslation(&left_shoulder.LeftShoulderTransform, left_shoulder.Position.x, left_shoulder.Position.y, left_shoulder.Position.z);
	//LeftShoulder(子)の姿勢行列保存
	left_shoulder.LeftShoulderMatrix = left_shoulder.LeftShoulderScale * left_shoulder.LeftShoulderRotation*left_shoulder.LeftShoulderTransform;

	//RightArm(子)の姿勢行列を設定
	D3DXMatrixScaling(&right_arm.RightArmScale, right_arm.Scale.x, right_arm.Scale.y, right_arm.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&right_arm.RightArmRotation, right_arm.Rotetion.y, right_arm.Rotetion.x, right_arm.Rotetion.z);
	D3DXMatrixTranslation(&right_arm.RightArmTransform, right_arm.Position.x, right_arm.Position.y, right_arm.Position.z);
	//RightArm(子)の姿勢行列保存
	right_arm.RightArmMatrix = right_arm.RightArmScale * right_arm.RightArmRotation*right_arm.RightArmTransform;

	//LeftArm(子)の姿勢行列を設定
	D3DXMatrixScaling(&left_arm.LeftArmScale, left_arm.Scale.x, left_arm.Scale.y, left_arm.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&left_arm.LeftArmRotation, left_arm.Rotetion.y, left_arm.Rotetion.x, left_arm.Rotetion.z);
	D3DXMatrixTranslation(&left_arm.LeftArmTransform, left_arm.Position.x, left_arm.Position.y, left_arm.Position.z);
	//LeftArm(子)の姿勢行列保存
	left_arm.LeftArmMatrix = left_arm.LeftArmScale * left_arm.LeftArmRotation*left_arm.LeftArmTransform;

	//RightElbow(子)の姿勢行列を設定
	D3DXMatrixScaling(&right_elbow.RightElbowScale, right_elbow.Scale.x, right_elbow.Scale.y, right_elbow.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&right_elbow.RightElbowRotation, right_elbow.Rotetion.y, right_elbow.Rotetion.x, right_elbow.Rotetion.z);
	D3DXMatrixTranslation(&right_elbow.RightElbowTransform, right_elbow.Position.x, right_elbow.Position.y, right_elbow.Position.z);
	//RightElbow(子)の姿勢行列保存
	right_elbow.RightElbowMatrix = right_elbow.RightElbowScale * right_elbow.RightElbowRotation*right_elbow.RightElbowTransform;

	//LeftElbow(子)の姿勢行列を設定
	D3DXMatrixScaling(&left_elbow.LeftElbowScale, left_elbow.Scale.x, left_elbow.Scale.y, left_elbow.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&left_elbow.LeftElbowRotation, left_elbow.Rotetion.y, left_elbow.Rotetion.x, left_elbow.Rotetion.z);
	D3DXMatrixTranslation(&left_elbow.LeftElbowTransform, left_elbow.Position.x, left_elbow.Position.y, left_elbow.Position.z);
	//LeftElbow(子)の姿勢行列保存
	left_elbow.LeftElbowMatrix = left_elbow.LeftElbowScale * left_elbow.LeftElbowRotation*left_elbow.LeftElbowTransform;

	//RightHand(子)の姿勢行列を設定
	D3DXMatrixScaling(&right_hand.RightHandScale, right_hand.Scale.x, right_hand.Scale.y, right_hand.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&right_hand.RightHandRotation, right_hand.Rotetion.y, right_hand.Rotetion.x, right_hand.Rotetion.z);
	D3DXMatrixTranslation(&right_hand.RightHandTransform, right_hand.Position.x, right_hand.Position.y, right_hand.Position.z);
	//RightHand(子)の姿勢行列保存
	right_hand.RightHandMatrix = right_hand.RightHandScale * right_hand.RightHandRotation*right_hand.RightHandTransform;

	//LeftHand(子)の姿勢行列を設定
	D3DXMatrixScaling(&left_hand.LeftHandScale, left_hand.Scale.x, left_hand.Scale.y, left_hand.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&left_hand.LeftHandRotation, left_hand.Rotetion.y, left_hand.Rotetion.x, left_hand.Rotetion.z);
	D3DXMatrixTranslation(&left_hand.LeftHandTransform, left_hand.Position.x, left_hand.Position.y, left_hand.Position.z);
	//LeftHand(子)の姿勢行列保存
	left_hand.LeftHandMatrix = left_hand.LeftHandScale * left_hand.LeftHandRotation*left_hand.LeftHandTransform;

	//RightKnee(子)の姿勢行列を設定
	D3DXMatrixScaling(&right_knee.RightKneeScale, right_knee.Scale.x, right_knee.Scale.y, right_knee.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&right_knee.RightKneeRotation, right_knee.Rotetion.y, right_knee.Rotetion.x, right_knee.Rotetion.z);
	D3DXMatrixTranslation(&right_knee.RightKneeTransform, right_knee.Position.x, right_knee.Position.y, right_knee.Position.z);
	//RightKnee(子)の姿勢行列保存
	right_knee.RightKneeMatrix = right_knee.RightKneeScale * right_knee.RightKneeRotation*right_knee.RightKneeTransform;

	//LeftKnee(子)の姿勢行列を設定
	D3DXMatrixScaling(&left_knee.LeftKneeScale, left_knee.Scale.x, left_knee.Scale.y, left_knee.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&left_knee.LeftKneeRotation, left_knee.Rotetion.y, left_knee.Rotetion.x, left_knee.Rotetion.z);
	D3DXMatrixTranslation(&left_knee.LeftKneeTransform, left_knee.Position.x, left_knee.Position.y, left_knee.Position.z);
	//LeftKnee(子)の姿勢行列保存
	left_knee.LeftKneeMatrix = left_knee.LeftKneeScale * left_knee.LeftKneeRotation*left_knee.LeftKneeTransform;

	//RightLeg(子)の姿勢行列を設定
	D3DXMatrixScaling(&right_leg.RightLegScale, right_leg.Scale.x, right_leg.Scale.y, right_leg.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&right_leg.RightLegRotation, right_leg.Rotetion.y, right_leg.Rotetion.x, right_leg.Rotetion.z);
	D3DXMatrixTranslation(&right_leg.RightLegTrasnform, right_leg.Position.x, right_leg.Position.y, right_leg.Position.z);
	//RightLeg(子)の姿勢行列保存
	right_leg.RightLegMatrix = right_leg.RightLegScale * right_leg.RightLegRotation*right_leg.RightLegTrasnform;

	//LeftLeg(子)の姿勢行列を設定
	D3DXMatrixScaling(&left_leg.LeftLegScale, left_leg.Scale.x, left_leg.Scale.y, left_leg.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&left_leg.LeftLegRotation, left_leg.Rotetion.y, left_leg.Rotetion.x, left_leg.Rotetion.z);
	D3DXMatrixTranslation(&left_leg.LeftLegTransform, left_leg.Position.x, left_leg.Position.y, left_leg.Position.z);
	//LeftLeg(子)の姿勢行列保存
	left_leg.LeftLegMatrix = left_leg.LeftLegScale * left_leg.LeftLegRotation*left_leg.LeftLegTransform;

	//親子姿勢行列計算
	g_BODYandHED = hed.HedMatrix*body.BodyMatrix;										//頭と体の計算
	g_BODYandRSHOULDER = right_shoulder.RightShoulderMatrix*body.BodyMatrix;			//右肩と体の計算
	g_BODYandLSHOULDER = left_shoulder.LeftShoulderMatrix*body.BodyMatrix;				//左肩と体の計算
	g_BODYandRARM = right_arm.RightArmMatrix*body.BodyMatrix;							//右腕と体の計算
	g_BODYandLARM = left_arm.LeftArmMatrix*body.BodyMatrix;								//左腕と体の計算
	g_BODYandRELBOW = right_elbow.RightElbowMatrix*body.BodyMatrix;						//右肩と体の計算
	g_BODYandLELBOW = left_elbow.LeftElbowMatrix*body.BodyMatrix;						//左肩と体の計算
	g_BODYandRHAND = right_hand.RightHandMatrix*body.BodyMatrix;						//右手と体の計算
	g_BODYandLHAND = left_hand.LeftHandMatrix*body.BodyMatrix;							//左手と体の計算
	g_BODYandRKNEE = right_knee.RightKneeMatrix*body.BodyMatrix;						//右膝と体の計算
	g_BODYandLKNEE = left_knee.LeftKneeMatrix*body.BodyMatrix;							//左膝と体の計算
	g_BODYandRLEG = right_leg.RightLegMatrix*body.BodyMatrix;							//右足と体の計算
	g_BODYandLLEG = left_leg.LeftLegMatrix*body.BodyMatrix;								//左足と体の計算
}

void CPlayer::Draw()
{
	CRenderer::SetWorldMatrix(&body.BodyMatrix);			//体
	m_BODY->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandHED);				//頭
	m_HEAD->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandRSHOULDER);			//右肩
	m_RIGHTSHOULDER->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandLSHOULDER);			//左肩
	m_LEFTSHOULDER->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandRARM);				//右腕
	m_RIGHTARM->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandLARM);				//左腕
	m_LEFTARM->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandRELBOW);			//右肘
	m_RIGHTELBOW->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandLELBOW);			//左肘
	m_LEFTELBOW->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandRHAND);				//右手
	m_RIGHTHAND->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandLHAND);				//左手
	m_LEFTHAND->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandRKNEE);				//右膝
	m_RIGHTKNEE->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandLKNEE);				//左膝
	m_LEFTKNEE->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandRLEG);				//右足
	m_RIGHTLEG->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandLLEG);				//左足
	m_LEFTLEG->Draw();

}

////////////////////////////////////////////////////
/////プレイヤーアクション関数
//////////////////////////////////////////////////
//前方歩行移動
void Move_Forward()
{
	float Move_Speed;
	Move_Speed = 0.1f;
	body.Position.x -= Move_Speed;
	//方向転換
	body.Rotetion.y += 0.1f;
	if (body.Rotetion.y > 0.0f)
	{
		body.Rotetion.y = 0.0f;
	}
	//歩行時アクション
	if (!g_MoveAct)
	{
		left_leg.Rotetion.z -= 0.1f;

		right_leg.Rotetion.z += 0.1f;
	}

	if (right_leg.Rotetion.z > RangeOfMotion_A)
	{
		g_MoveAct = true;
	}

	if (g_MoveAct)
	{
		left_leg.Rotetion.z += 0.1f;

		right_leg.Rotetion.z -= 0.1f;
	}
	if (right_leg.Rotetion.z < RangeOfMotion_B)
	{
		g_MoveAct = false;
	}

}
//後方歩行移動
void Move_Back()
{
	float Move_Speed;
	Move_Speed = 0.1f;
	body.Position.x += Move_Speed;
	//方向転換
	body.Rotetion.y += 0.1f;

	if (body.Rotetion.y > 3.0f)
	{
		body.Rotetion.y = 3.0f;
	}
	//歩行時アクション
	if (!g_MoveAct)
	{
		left_leg.Rotetion.z -= 0.1f;

		right_leg.Rotetion.z += 0.1f;
	}

	if (right_leg.Rotetion.z > RangeOfMotion_A)
	{
		g_MoveAct = true;
	}

	if (g_MoveAct)
	{
		left_leg.Rotetion.z += 0.1f;

		right_leg.Rotetion.z -= 0.1f;
	}
	if (right_leg.Rotetion.z < RangeOfMotion_B)
	{
		g_MoveAct = false;
	}
}
//左方歩行移動
void Move_Left()
{
	float Move_Speed;
	Move_Speed = 0.1f;
	body.Position.z -= Move_Speed;
	//方向転換
	body.Rotetion.y -= 0.1f;
	if (body.Rotetion.y < -1.7f)
	{
		body.Rotetion.y = -1.7f;
	}
	//歩行時アクション
	if (!g_MoveAct)
	{
		left_leg.Rotetion.z -= 0.1f;

		right_leg.Rotetion.z += 0.1f;
	}

	if (right_leg.Rotetion.z > RangeOfMotion_A)
	{
		g_MoveAct = true;
	}

	if (g_MoveAct)
	{
		left_leg.Rotetion.z += 0.1f;

		right_leg.Rotetion.z -= 0.1f;
	}
	if (right_leg.Rotetion.z < RangeOfMotion_B)
	{
		g_MoveAct = false;
	}
}
//右方歩行移動
void Move_Right()
{
	float Move_Speed;
	Move_Speed = 0.1f;
	body.Position.z += Move_Speed;
	//方向転換
	body.Rotetion.y += 0.1f;
	if (body.Rotetion.y > 1.7f)
	{
		body.Rotetion.y = 1.7f;
	}
	//歩行時アクション
	if (!g_MoveAct)
	{
		left_leg.Rotetion.z -= 0.1f;

		right_leg.Rotetion.z += 0.1f;
	}

	if (right_leg.Rotetion.z > RangeOfMotion_A)
	{
		g_MoveAct = true;
	}

	if (g_MoveAct)
	{
		left_leg.Rotetion.z += 0.1f;

		right_leg.Rotetion.z -= 0.1f;
	}
	if (right_leg.Rotetion.z < RangeOfMotion_B)
	{
		g_MoveAct = false;
	}
}

//コマンドアクション
void Break()
{
	float move;
	move = 0.06f;
	//moveの数値設定
	//0.03.....重量パンチ
	//0.06.....通常パンチ
	//0.09.....軽量パンチ
	if (!punch)
	{
		right_shoulder.Rotetion.z = 0.1f;
		right_arm.Position.x += move;
		right_elbow.Rotetion.z = 5.0f;
		right_elbow.Position.x += move;
		right_hand.Rotetion.z = 5.0f;
		right_hand.Position.y = right_elbow.Position.y - 0.4f;
		right_hand.Position.x += move;
	}
	if (right_hand.Position.x > 0.5)
	{
		punch = true;
		if (punch)
		{
			right_shoulder.Rotetion.z = 3.2f;
			right_arm.Position.x = -1.0f;
			right_elbow.Rotetion.z = 5.0f;
			right_elbow.Position.x = -1.0f;
			right_hand.Rotetion.z = 5.0f;
			right_hand.Position.y = right_elbow.Position.y - 0.4f;
			right_hand.Position.x = -2.0f;
		}
	}
}

