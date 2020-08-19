#pragma once

#include "game_object.h"

class CPlayer :public CGameObject//�p��(�C���w���^���X)
{
private:

	//�O���錾(�|�C���^�ϐ��̗L��)
	//�e�p�[�c���f���̓ǂݍ���
	class CModel* m_HEAD;			//���p�[�c
	class CModel* m_BODY;			//�̃p�[�c
	class CModel* m_LEFTSHOULDER;	//�����p�[�c		
	class CModel* m_RIGHTSHOULDER;	//�E���p�[�c
	class CModel* m_RIGHTARM;		//�E�r�p�[�c
	class CModel* m_LEFTARM;		//���r�p�[�c
	class CModel*m_RIGHTELBOW;		//�E�I�p�[�c
	class CModel*m_LEFTELBOW;		//���I�p�[�c
	class CModel*m_RIGHTHAND;		//�E��p�[�c
	class CModel*m_LEFTHAND;		//����p�[�c
	class CModel*m_RIGHTKNEE;		//�E�G�p�[�c
	class CModel*m_LEFTKNEE;		//���G�p�[�c
	class CModel* m_LEFTLEG;		//�����p�[�c
	class CModel* m_RIGHTLEG;		//�E���p�[�c
public:
	CPlayer() {}
	~CPlayer() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();

	friend class CScene;
};