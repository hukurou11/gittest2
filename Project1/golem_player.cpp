#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "golem_player.h"
#include "input.h"
#include "input2.h"
#include "scene.h"

/////////////////////////////////
////�ϐ��錾////////
////////////////////////////////
//�}�g���N�X�ݒ�
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
//�v���C���[�f�[�^�ϐ�
static bool act;				//�A�N�V�����t���O
static bool punch;				//�p���`���[�V����
static int count;				//�A�N�V�����t���[�Y����
static bool g_MoveAct;			//������؂�ւ���
static float RangeOfMotion_A;	//�r�s������A
static float RangeOfMotion_B;	//�r�s������B
//////////////////////////////////
///�A�N�V�����֐�
//////////////////////////////////

//���s
void Move_Forward();		//�O�����s
void Move_Back();			//������s
void Move_Left();			//�������s
void Move_Right();			//�E�����s

//�R�}���h�A�N�V����
void Break();				//�j��A�N�V����


//���̃N���X�i��{�j
class Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX BodyMatrix, BodyScale, BodyRotation, BodyTransform;//�p���s��ۑ�
};

////////////////////
//�֐߃p�[�c�錾
///////////////////
//���N���X�i�h���j
class CHed :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX HedMatrix, HedScale, HedRotation, HedTransform;//�p���s��ۑ�
};

//�E���N���X�i�h���j
class CR_Shoulder :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX RightShoulderMatrix, RightShoulderScale, RightShoulderRotation, RightShoulderTransform;//�p���s��ۑ�
};

//�E�r�N���X�i�h���j
class CR_ARM :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX RightArmMatrix, RightArmScale, RightArmRotation, RightArmTransform;//�p���s��ۑ�
};

//�E�I�N���X
class CR_ELBOW :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX RightElbowMatrix, RightElbowScale, RightElbowRotation, RightElbowTransform;//�p���s��ۑ�
};

//�E��N���X
class CR_HAND :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX RightHandMatrix, RightHandScale, RightHandRotation, RightHandTransform;//�p���s��ۑ�
};

//�E�G�N���X
class CR_KNEE :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX RightKneeMatrix, RightKneeScale, RightKneeRotation, RightKneeTransform;//�p���s��ۑ�
};

//�����N���X�i�h���j
class CL_Shoulder :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX LeftShoulderMatrix, LeftShoulderScale, LeftShoulderRotation, LeftShoulderTransform;//�p���s��ۑ�
};

//���r�N���X�i�h���j
class CL_ARM :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX LeftArmMatrix, LeftArmScale, LeftArmRotation, LeftArmTransform;//�p���s��ۑ�
};

//���I�N���X
class CL_ELBOW :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX LeftElbowMatrix, LeftElbowScale, LeftElbowRotation, LeftElbowTransform;//�p���s��ۑ�
};

//����N���X
class CL_HAND :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX LeftHandMatrix, LeftHandScale, LeftHandRotation, LeftHandTransform;//�p���s��ۑ�
};

//���G�N���X
class CL_KNEE :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX LeftKneeMatrix, LeftKneeScale, LeftKneeRotation, LeftKneeTransform;//�p���s��ۑ�
};

//�E���N���X�i�h���j
class CR_Leg :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX RightLegMatrix, RightLegScale, RightLegRotation, RightLegTrasnform;//�p���s��ۑ�
};

//�����N���X�i�h���j
class CL_Leg :public Body
{
public:
	D3DXVECTOR3 Position;//�ʒu
	Vector3 Rotetion;//��]
	Vector3 Scale;			//�g�k
	D3DXMATRIX LeftLegMatrix, LeftLegScale, LeftLegRotation, LeftLegTransform;//�p���s��ۑ�
};


/////////////////////////
//�p�[�c�C���X�^���X
////////////////////////

Body body;					//�̃p�[�c�C���X�^���X
CHed hed;					//���p�[�c�C���X�^���X
CR_Shoulder right_shoulder;	//�E���p�[�c�C���X�^���X
CL_Shoulder left_shoulder;	//�����p�[�c�C���X�^���X
CR_ARM right_arm;			//�E�r�p�[�c�C���X�^���X
CL_ARM left_arm;			//���r�p�[�c�C���X�^���X
CR_ELBOW right_elbow;		//�E�I�p�[�c�C���X�^���X
CL_ELBOW left_elbow;		//���I�p�[�c�C���X�^���X
CR_HAND right_hand;			//�E��p�[�c�C���X�^���X
CL_HAND left_hand;			//����p�[�c�C���X�^���X
CR_KNEE right_knee;			//�E�G�p�[�c�C���X�^���X
CL_KNEE left_knee;			//���G�p�[�c�C���X�^���X
CR_Leg right_leg;			//�E���p�[�c�C���X�^���X
CL_Leg left_leg;			//�����p�[�c�C���X�^���X

void CPlayer::Init()
{
	//���f���ǂݍ��ݏ���
	m_HEAD = new CModel();			//���p�[�c
	m_BODY = new CModel();			//�̃p�[�c
	m_LEFTSHOULDER = new CModel();	//�����p�[�c
	m_RIGHTSHOULDER = new CModel();	//�E���p�[�c
	m_RIGHTARM = new CModel();		//�E�r�p�[�c
	m_LEFTARM = new CModel();		//���r�p�[�c
	m_RIGHTELBOW = new CModel();	//�E�I�p�[�c
	m_LEFTELBOW = new CModel();		//���I�p�[�c
	m_RIGHTHAND = new CModel();		//�E��p�[�c
	m_LEFTHAND = new CModel();		//����p�[�c
	m_RIGHTKNEE = new CModel();		//�E�G�p�[�c
	m_LEFTKNEE = new CModel();		//���G�p�[�c
	m_LEFTLEG = new CModel();		//�����p�[�c
	m_RIGHTLEG = new CModel();		//�E���p�[�c

	//�e���f���ǂݍ���
	m_HEAD->Load("asset\\model\\cube.obj");				//���p�[�c
	m_BODY->Load("asset\\model\\cube.obj");				//�̃p�[�c
	m_LEFTSHOULDER->Load("asset\\model\\cube.obj");		//�����p�[�c
	m_RIGHTSHOULDER->Load("asset\\model\\cube.obj");	//�E���p�[�c
	m_RIGHTARM->Load("asset\\model\\cube.obj");			//�E�r�p�[�c
	m_LEFTARM->Load("asset\\model\\cube.obj");			//���r�p�[�c
	m_RIGHTELBOW->Load("asset\\model\\cube.obj");		//�E�I�p�[�c
	m_LEFTELBOW->Load("asset\\model\\cube.obj");		//���I�p�[�c
	m_RIGHTHAND->Load("asset\\model\\cube.obj");		//�E��p�[�c
	m_LEFTHAND->Load("asset\\model\\cube.obj");			//����p�[�c
	m_RIGHTKNEE->Load("asset\\model\\cube.obj");		//�E�G�p�[�c
	m_LEFTKNEE->Load("asset\\model\\cube.obj");			//���G�p�[�c
	m_LEFTLEG->Load("asset\\model\\cube.obj");			//�����p�[�c
	m_RIGHTLEG->Load("asset\\model\\cube.obj");			//�E���p�[�c

	//���f�������l�ݒ� 
	//�����ʒu
	body.Position = Vector3(0.0f, 0.0f, 0.0f);																				//��
	hed.Position = Vector3(body.Position.x, body.Position.y + 1.2f, body.Position.z);										//��
	left_shoulder.Position = Vector3(body.Position.x, body.Position.y + 1.5f, body.Position.z - 1.2f);						//����
	right_shoulder.Position = Vector3(body.Position.x, body.Position.y + 1.5f, body.Position.z + 1.2f);							//�E��
	right_arm.Position = Vector3(right_shoulder.Position.x, right_shoulder.Position.y - 0.3f, right_shoulder.Position.z);		//�E�r
	left_arm.Position = Vector3(left_shoulder.Position.x, left_shoulder.Position.y - 0.3f, left_shoulder.Position.z);		//���r
	right_elbow.Position = Vector3(right_arm.Position.x, right_arm.Position.y - 0.5f, right_arm.Position.z);				//�E�I
	left_elbow.Position = Vector3(left_arm.Position.x, left_arm.Position.y - 0.5f, left_arm.Position.z);					//���I
	right_hand.Position = Vector3(right_elbow.Position.x, right_elbow.Position.y - 0.3f, right_elbow.Position.z);			//�E��
	left_hand.Position = Vector3(left_elbow.Position.x, left_elbow.Position.y - 0.3f, left_elbow.Position.z);				//����
	right_knee.Position = Vector3(body.Position.x, body.Position.y - 0.1f, body.Position.z + 0.3f);									//�E�G
	left_knee.Position = Vector3(body.Position.x, body.Position.y - 0.1f, body.Position.z - 0.3f);									//���G
	left_leg.Position = Vector3(left_knee.Position.x, left_knee.Position.y - 0.1f, left_knee.Position.z);								//����
	right_leg.Position = Vector3(right_knee.Position.x, right_knee.Position.y - 0.1f, right_knee.Position.z);							//�E��

	//�X�P�[���i�傫���j
	body.Scale = Vector3(1.5f, 3.5f, 1.5f);				//��
	hed.Scale = Vector3(1.0f, 0.5f, 1.0f);				//��
	left_shoulder.Scale = Vector3(1.0f, 0.2f, 1.0f);	//����
	right_shoulder.Scale = Vector3(1.0f, 0.2f, 1.0f);	//�E��
	right_arm.Scale = Vector3(0.8f, 0.5, 0.8f);			//�E�r
	left_arm.Scale = Vector3(0.8f, 0.5f, 0.8f);			//���r
	right_elbow.Scale = Vector3(0.2f, 0.2, 0.2f);		//�E�I
	left_elbow.Scale = Vector3(0.2f, 0.2f, 0.2f);		//���I
	right_hand.Scale = Vector3(0.5f, 1.0, 0.5f);		//�E��
	left_hand.Scale = Vector3(0.5f, 1.0f, 0.5f);		//����
	right_knee.Scale = Vector3(0.2f, 0.2, 0.2f);		//�E�G
	left_knee.Scale = Vector3(0.2f, 0.2f, 0.2f);		//���G
	left_leg.Scale = Vector3(0.5f, 1.5f, 0.5f);			//����
	right_leg.Scale = Vector3(0.5f, 1.0f, 0.5f);		//�E��

	//��]������
	body.Rotetion = Vector3(0.0f, 0.0f, 0.0f);				//��
	hed.Rotetion = Vector3(0.0f, 0.0f, 0.0f);				//��
	left_shoulder.Rotetion = Vector3(0.0f, 0.0f, -3.2f);	//����
	right_shoulder.Rotetion = Vector3(0.0f, 0.0f, 3.2f);	//�E��
	right_arm.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//�E�r
	left_arm.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//���r
	right_elbow.Rotetion = Vector3(0.0f, 0.0f, 3.2f);		//�E�I
	left_elbow.Rotetion = Vector3(0.0f, 0.0f, -3.2f);		//���I
	right_hand.Rotetion = Vector3(0.0f, 0.0f, 3.2f);		//�E��
	left_hand.Rotetion = Vector3(0.0f, 0.0f, -3.2f);		//����
	right_knee.Rotetion = Vector3(0.0f, 0.0f, 3.2f);		//�E�G
	left_knee.Rotetion = Vector3(0.0f, 0.0f, -3.2f);		//���G
	left_leg.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//����
	right_leg.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//�E��

	//�O���[�o���ϐ�������
	count = 0;
	act = false;
	punch = false;
	g_MoveAct = false;			//������؂�ւ���
	RangeOfMotion_A = 4.2f;	//�r�s������A
	RangeOfMotion_B = 2.0f;	//�r�s������B

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
	//�p���`���͎��s������
	if (!punch)
	{
		//�s���R�}���h����
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
		//�s���R�}���h�������Ƃ��ɕ��s�A�N�V�������Z�b�g
		if (CInput::GetKeyRelease(VK_UP))
		{
			left_leg.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//����
			right_leg.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//�E��
		}
		if (CInput::GetKeyRelease(VK_DOWN))
		{
			left_leg.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//����
			right_leg.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//�E��
		}
		if (CInput::GetKeyRelease(VK_RIGHT))
		{
			left_leg.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//����
			right_leg.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//�E��
		}
		if (CInput::GetKeyRelease(VK_LEFT))
		{
			left_leg.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//����
			right_leg.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//�E��
		}
	}
	//�U���R�}���h����
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		left_leg.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//����
		right_leg.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//�E��
		act = true;
	}
	//�R�}���h�t���O�Ăяo��
	if (act)
	{
		Break();
	}
	//�A�N�V�����R�}���h���Z�b�g
	if (right_arm.Position.x == -1.0f)
	{
		count++;
		if (count > 30)//�p���`�q�b�g���t���[�Y����
		{
			punch = false;
			act = false;
			right_arm.Rotetion = Vector3(0.0f, 0.0f, 3.2f);			//�E�r
			left_arm.Rotetion = Vector3(0.0f, 0.0f, -3.2f);			//���r
			right_elbow.Rotetion = Vector3(0.0f, 0.0f, 3.2f);		//�E�I
			left_elbow.Rotetion = Vector3(0.0f, 0.0f, -3.2f);		//���I
			right_hand.Rotetion = Vector3(0.0f, 0.0f, 3.2f);		//�E��
			left_hand.Rotetion = Vector3(0.0f, 0.0f, -3.2f);		//����
			right_arm.Position = Vector3(right_shoulder.Position.x, right_shoulder.Position.y - 0.3f, right_shoulder.Position.z);		//�E�r
			right_elbow.Position = Vector3(right_arm.Position.x, right_arm.Position.y - 0.5f, right_arm.Position.z);				//�E�I
			right_hand.Position = Vector3(right_elbow.Position.x, right_elbow.Position.y - 0.3f, right_elbow.Position.z);			//�E��
			left_hand.Position = Vector3(left_elbow.Position.x, left_elbow.Position.y - 0.3f, left_elbow.Position.z);
			count = 0;
		}
	}
	//�f�o�b�O�L�[����
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
	//Body(�e)�̎p���s���ݒ�
	D3DXMatrixScaling(&body.BodyScale, body.Scale.x, body.Scale.y, body.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&body.BodyRotation, body.Rotetion.y, body.Rotetion.x, body.Rotetion.z);
	D3DXMatrixTranslation(&body.BodyTransform, body.Position.x, body.Position.y, body.Position.z);
	//body(�e)�̎p���s��ۑ�
	body.BodyMatrix = body.BodyScale * body.BodyRotation*body.BodyTransform;

	//Hed(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&hed.HedScale, hed.Scale.x, hed.Scale.y, hed.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&hed.HedRotation, hed.Rotetion.y, hed.Rotetion.x, hed.Rotetion.z);
	D3DXMatrixTranslation(&hed.HedTransform, hed.Position.x, hed.Position.y, hed.Position.z);
	//hed(�q)�̎p���s��ۑ�
	hed.HedMatrix = hed.HedScale * hed.HedRotation*hed.HedTransform;

	//RightShoulder(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&right_shoulder.RightShoulderScale, right_shoulder.Scale.x, right_shoulder.Scale.y, right_shoulder.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&right_shoulder.RightShoulderRotation, right_shoulder.Rotetion.y, right_shoulder.Rotetion.x, right_shoulder.Rotetion.z);
	D3DXMatrixTranslation(&right_shoulder.RightShoulderTransform, right_shoulder.Position.x, right_shoulder.Position.y, right_shoulder.Position.z);
	//RightShoulder(�q)�̎p���s��ۑ�
	right_shoulder.RightShoulderMatrix = right_shoulder.RightShoulderScale * right_shoulder.RightShoulderRotation*right_shoulder.RightShoulderTransform;

	//LeftShoulder(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&left_shoulder.LeftShoulderScale, left_shoulder.Scale.x, left_shoulder.Scale.y, left_shoulder.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&left_shoulder.LeftShoulderRotation, left_shoulder.Rotetion.y, left_shoulder.Rotetion.x, left_shoulder.Rotetion.z);
	D3DXMatrixTranslation(&left_shoulder.LeftShoulderTransform, left_shoulder.Position.x, left_shoulder.Position.y, left_shoulder.Position.z);
	//LeftShoulder(�q)�̎p���s��ۑ�
	left_shoulder.LeftShoulderMatrix = left_shoulder.LeftShoulderScale * left_shoulder.LeftShoulderRotation*left_shoulder.LeftShoulderTransform;

	//RightArm(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&right_arm.RightArmScale, right_arm.Scale.x, right_arm.Scale.y, right_arm.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&right_arm.RightArmRotation, right_arm.Rotetion.y, right_arm.Rotetion.x, right_arm.Rotetion.z);
	D3DXMatrixTranslation(&right_arm.RightArmTransform, right_arm.Position.x, right_arm.Position.y, right_arm.Position.z);
	//RightArm(�q)�̎p���s��ۑ�
	right_arm.RightArmMatrix = right_arm.RightArmScale * right_arm.RightArmRotation*right_arm.RightArmTransform;

	//LeftArm(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&left_arm.LeftArmScale, left_arm.Scale.x, left_arm.Scale.y, left_arm.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&left_arm.LeftArmRotation, left_arm.Rotetion.y, left_arm.Rotetion.x, left_arm.Rotetion.z);
	D3DXMatrixTranslation(&left_arm.LeftArmTransform, left_arm.Position.x, left_arm.Position.y, left_arm.Position.z);
	//LeftArm(�q)�̎p���s��ۑ�
	left_arm.LeftArmMatrix = left_arm.LeftArmScale * left_arm.LeftArmRotation*left_arm.LeftArmTransform;

	//RightElbow(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&right_elbow.RightElbowScale, right_elbow.Scale.x, right_elbow.Scale.y, right_elbow.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&right_elbow.RightElbowRotation, right_elbow.Rotetion.y, right_elbow.Rotetion.x, right_elbow.Rotetion.z);
	D3DXMatrixTranslation(&right_elbow.RightElbowTransform, right_elbow.Position.x, right_elbow.Position.y, right_elbow.Position.z);
	//RightElbow(�q)�̎p���s��ۑ�
	right_elbow.RightElbowMatrix = right_elbow.RightElbowScale * right_elbow.RightElbowRotation*right_elbow.RightElbowTransform;

	//LeftElbow(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&left_elbow.LeftElbowScale, left_elbow.Scale.x, left_elbow.Scale.y, left_elbow.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&left_elbow.LeftElbowRotation, left_elbow.Rotetion.y, left_elbow.Rotetion.x, left_elbow.Rotetion.z);
	D3DXMatrixTranslation(&left_elbow.LeftElbowTransform, left_elbow.Position.x, left_elbow.Position.y, left_elbow.Position.z);
	//LeftElbow(�q)�̎p���s��ۑ�
	left_elbow.LeftElbowMatrix = left_elbow.LeftElbowScale * left_elbow.LeftElbowRotation*left_elbow.LeftElbowTransform;

	//RightHand(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&right_hand.RightHandScale, right_hand.Scale.x, right_hand.Scale.y, right_hand.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&right_hand.RightHandRotation, right_hand.Rotetion.y, right_hand.Rotetion.x, right_hand.Rotetion.z);
	D3DXMatrixTranslation(&right_hand.RightHandTransform, right_hand.Position.x, right_hand.Position.y, right_hand.Position.z);
	//RightHand(�q)�̎p���s��ۑ�
	right_hand.RightHandMatrix = right_hand.RightHandScale * right_hand.RightHandRotation*right_hand.RightHandTransform;

	//LeftHand(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&left_hand.LeftHandScale, left_hand.Scale.x, left_hand.Scale.y, left_hand.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&left_hand.LeftHandRotation, left_hand.Rotetion.y, left_hand.Rotetion.x, left_hand.Rotetion.z);
	D3DXMatrixTranslation(&left_hand.LeftHandTransform, left_hand.Position.x, left_hand.Position.y, left_hand.Position.z);
	//LeftHand(�q)�̎p���s��ۑ�
	left_hand.LeftHandMatrix = left_hand.LeftHandScale * left_hand.LeftHandRotation*left_hand.LeftHandTransform;

	//RightKnee(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&right_knee.RightKneeScale, right_knee.Scale.x, right_knee.Scale.y, right_knee.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&right_knee.RightKneeRotation, right_knee.Rotetion.y, right_knee.Rotetion.x, right_knee.Rotetion.z);
	D3DXMatrixTranslation(&right_knee.RightKneeTransform, right_knee.Position.x, right_knee.Position.y, right_knee.Position.z);
	//RightKnee(�q)�̎p���s��ۑ�
	right_knee.RightKneeMatrix = right_knee.RightKneeScale * right_knee.RightKneeRotation*right_knee.RightKneeTransform;

	//LeftKnee(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&left_knee.LeftKneeScale, left_knee.Scale.x, left_knee.Scale.y, left_knee.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&left_knee.LeftKneeRotation, left_knee.Rotetion.y, left_knee.Rotetion.x, left_knee.Rotetion.z);
	D3DXMatrixTranslation(&left_knee.LeftKneeTransform, left_knee.Position.x, left_knee.Position.y, left_knee.Position.z);
	//LeftKnee(�q)�̎p���s��ۑ�
	left_knee.LeftKneeMatrix = left_knee.LeftKneeScale * left_knee.LeftKneeRotation*left_knee.LeftKneeTransform;

	//RightLeg(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&right_leg.RightLegScale, right_leg.Scale.x, right_leg.Scale.y, right_leg.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&right_leg.RightLegRotation, right_leg.Rotetion.y, right_leg.Rotetion.x, right_leg.Rotetion.z);
	D3DXMatrixTranslation(&right_leg.RightLegTrasnform, right_leg.Position.x, right_leg.Position.y, right_leg.Position.z);
	//RightLeg(�q)�̎p���s��ۑ�
	right_leg.RightLegMatrix = right_leg.RightLegScale * right_leg.RightLegRotation*right_leg.RightLegTrasnform;

	//LeftLeg(�q)�̎p���s���ݒ�
	D3DXMatrixScaling(&left_leg.LeftLegScale, left_leg.Scale.x, left_leg.Scale.y, left_leg.Scale.z);
	D3DXMatrixRotationYawPitchRoll(&left_leg.LeftLegRotation, left_leg.Rotetion.y, left_leg.Rotetion.x, left_leg.Rotetion.z);
	D3DXMatrixTranslation(&left_leg.LeftLegTransform, left_leg.Position.x, left_leg.Position.y, left_leg.Position.z);
	//LeftLeg(�q)�̎p���s��ۑ�
	left_leg.LeftLegMatrix = left_leg.LeftLegScale * left_leg.LeftLegRotation*left_leg.LeftLegTransform;

	//�e�q�p���s��v�Z
	g_BODYandHED = hed.HedMatrix*body.BodyMatrix;										//���Ƒ̂̌v�Z
	g_BODYandRSHOULDER = right_shoulder.RightShoulderMatrix*body.BodyMatrix;			//�E���Ƒ̂̌v�Z
	g_BODYandLSHOULDER = left_shoulder.LeftShoulderMatrix*body.BodyMatrix;				//�����Ƒ̂̌v�Z
	g_BODYandRARM = right_arm.RightArmMatrix*body.BodyMatrix;							//�E�r�Ƒ̂̌v�Z
	g_BODYandLARM = left_arm.LeftArmMatrix*body.BodyMatrix;								//���r�Ƒ̂̌v�Z
	g_BODYandRELBOW = right_elbow.RightElbowMatrix*body.BodyMatrix;						//�E���Ƒ̂̌v�Z
	g_BODYandLELBOW = left_elbow.LeftElbowMatrix*body.BodyMatrix;						//�����Ƒ̂̌v�Z
	g_BODYandRHAND = right_hand.RightHandMatrix*body.BodyMatrix;						//�E��Ƒ̂̌v�Z
	g_BODYandLHAND = left_hand.LeftHandMatrix*body.BodyMatrix;							//����Ƒ̂̌v�Z
	g_BODYandRKNEE = right_knee.RightKneeMatrix*body.BodyMatrix;						//�E�G�Ƒ̂̌v�Z
	g_BODYandLKNEE = left_knee.LeftKneeMatrix*body.BodyMatrix;							//���G�Ƒ̂̌v�Z
	g_BODYandRLEG = right_leg.RightLegMatrix*body.BodyMatrix;							//�E���Ƒ̂̌v�Z
	g_BODYandLLEG = left_leg.LeftLegMatrix*body.BodyMatrix;								//�����Ƒ̂̌v�Z
}

void CPlayer::Draw()
{
	CRenderer::SetWorldMatrix(&body.BodyMatrix);			//��
	m_BODY->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandHED);				//��
	m_HEAD->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandRSHOULDER);			//�E��
	m_RIGHTSHOULDER->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandLSHOULDER);			//����
	m_LEFTSHOULDER->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandRARM);				//�E�r
	m_RIGHTARM->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandLARM);				//���r
	m_LEFTARM->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandRELBOW);			//�E�I
	m_RIGHTELBOW->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandLELBOW);			//���I
	m_LEFTELBOW->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandRHAND);				//�E��
	m_RIGHTHAND->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandLHAND);				//����
	m_LEFTHAND->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandRKNEE);				//�E�G
	m_RIGHTKNEE->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandLKNEE);				//���G
	m_LEFTKNEE->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandRLEG);				//�E��
	m_RIGHTLEG->Draw();
	CRenderer::SetWorldMatrix(&g_BODYandLLEG);				//����
	m_LEFTLEG->Draw();

}

////////////////////////////////////////////////////
/////�v���C���[�A�N�V�����֐�
//////////////////////////////////////////////////
//�O�����s�ړ�
void Move_Forward()
{
	float Move_Speed;
	Move_Speed = 0.1f;
	body.Position.x -= Move_Speed;
	//�����]��
	body.Rotetion.y += 0.1f;
	if (body.Rotetion.y > 0.0f)
	{
		body.Rotetion.y = 0.0f;
	}
	//���s���A�N�V����
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
//������s�ړ�
void Move_Back()
{
	float Move_Speed;
	Move_Speed = 0.1f;
	body.Position.x += Move_Speed;
	//�����]��
	body.Rotetion.y += 0.1f;

	if (body.Rotetion.y > 3.0f)
	{
		body.Rotetion.y = 3.0f;
	}
	//���s���A�N�V����
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
//�������s�ړ�
void Move_Left()
{
	float Move_Speed;
	Move_Speed = 0.1f;
	body.Position.z -= Move_Speed;
	//�����]��
	body.Rotetion.y -= 0.1f;
	if (body.Rotetion.y < -1.7f)
	{
		body.Rotetion.y = -1.7f;
	}
	//���s���A�N�V����
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
//�E�����s�ړ�
void Move_Right()
{
	float Move_Speed;
	Move_Speed = 0.1f;
	body.Position.z += Move_Speed;
	//�����]��
	body.Rotetion.y += 0.1f;
	if (body.Rotetion.y > 1.7f)
	{
		body.Rotetion.y = 1.7f;
	}
	//���s���A�N�V����
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

//�R�}���h�A�N�V����
void Break()
{
	float move;
	move = 0.06f;
	//move�̐��l�ݒ�
	//0.03.....�d�ʃp���`
	//0.06.....�ʏ�p���`
	//0.09.....�y�ʃp���`
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

