
#include "input.h"

#define	NUM_KEY_MAX			(256)

// game pad�p�ݒ�l
#define DEADZONE		2500			// �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX		1000			// �L���͈͂̍ő�l
#define RANGE_MIN		-1000			// �L���͈͂̍ŏ��l

static bool initialize(HINSTANCE hInstance);
static void finalize(void);

LPDIRECTINPUT8			g_pInput = NULL;

//�L�[�{�[�h
static LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;
static BYTE					g_aKeyState[NUM_KEY_MAX];
static BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];
static BYTE					g_aKeyStateRelease[NUM_KEY_MAX];

//�Q�[���p�b�h
static LPDIRECTINPUTDEVICE8	g_pGamePad[GAMEPADMAX] = { NULL, NULL, NULL, NULL };// �p�b�h�f�o�C�X
static DWORD				g_padState[GAMEPADMAX];	// �p�b�h���i�����Ή��j
static DWORD				g_padTrigger[GAMEPADMAX];
static int					g_padCount = 0;			// ���o�����p�b�h�̐�


bool initialize(HINSTANCE hInstance)
{
	if(g_pInput == NULL) {

		if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL))) {

			return false;
		}
	}

	return true;
}

void finalize(void)
{
	if(g_pInput != NULL) {
		g_pInput->Release();
		g_pInput = NULL;
	}
}

bool Keyboard_Initialize(HINSTANCE hInstance, HWND hWnd)
{
	if( !initialize(hInstance) ) {

		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}

	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}

	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return false;
	}
	//													 DISCL_BACKGROUND | DISCL_EXCLUSIVE	
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return false;
	}

	g_pDevKeyboard->Acquire();

	return true;
}

void Keyboard_Finalize(void)
{
	if(g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();

		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	finalize();
}

void Keyboard_Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	if(SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for(int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & g_aKeyState[nCnKey];

			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}

bool Keyboard_IsPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

bool Keyboard_IsTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true: false;
}

bool Keyboard_IsRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true: false;
}

//---------------------------------------- �R�[���o�b�N�֐�
BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
{
	HRESULT result;

	result = g_pInput->CreateDevice(lpddi->guidInstance, &g_pGamePad[g_padCount++], NULL);
	return DIENUM_CONTINUE;	// ���̃f�o�C�X���
}

bool GamePad_Initialize(HINSTANCE hInstance, HWND hWnd)
{
	if (!initialize(hInstance)) {

		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}

	HRESULT		result;
	int			i;

	g_padCount = 0;
	// �W���C�p�b�h��T��
	g_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
	// �Z�b�g�����R�[���o�b�N�֐����A�p�b�h�𔭌������������Ă΂��B

	for (i = 0; i<g_padCount; i++) 
	{
		// �W���C�X�e�B�b�N�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
		result = g_pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(result))
			return false; // �f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s

		// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		//		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		//		if ( FAILED(result) )
		//			return false; // ���[�h�̐ݒ�Ɏ��s

		// ���̒l�͈̔͂�ݒ�
		// X���AY���̂��ꂼ��ɂ��āA�I�u�W�F�N�g���񍐉\�Ȓl�͈̔͂��Z�b�g����B
		// (max-min)�́A�ő�10,000(?)�B(max-min)/2�������l�ɂȂ�B
		// ����傫������΁A�A�i���O�l�ׂ̍��ȓ�����߂炦����B(�p�b�h�̐��\�ɂ��)
		DIPROPRANGE				diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = RANGE_MIN;
		diprg.lMax = RANGE_MAX;
		// X���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_X;
		g_pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_Y;
		g_pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �e�����ƂɁA�����̃]�[���l��ݒ肷��B
		// �����]�[���Ƃ́A��������̔����ȃW���C�X�e�B�b�N�̓����𖳎�����͈͂̂��ƁB
		// �w�肷��l�́A10000�ɑ΂��鑊�Βl(2000�Ȃ�20�p�[�Z���g)�B
		DIPROPDWORD				dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = DEADZONE;
		//X���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_X;
		g_pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_Y;
		g_pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		//�W���C�X�e�B�b�N���͐���J�n
		g_pGamePad[i]->Acquire();
	}

	return true;
}

void GamePad_Finalize(void)
{
	for (int i = 0; i<GAMEPADMAX; i++) {
		if (g_pGamePad[i])
		{
			g_pGamePad[i]->Unacquire();
			g_pGamePad[i]->Release();
		}
	}

	finalize();
}

void GamePad_Update(void)
{
	HRESULT			result;
	DIJOYSTATE2		dijs;
	int				i;

	for (i = 0; i<g_padCount; i++)
	{
		DWORD lastPadState;
		lastPadState = g_padState[i];
		g_padState[i] = 0x00000000l;	// ������

		result = g_pGamePad[i]->Poll();	// �W���C�X�e�B�b�N�Ƀ|�[����������
		if (FAILED(result)) {
			result = g_pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = g_pGamePad[i]->Acquire();
		}

		result = g_pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// �f�o�C�X��Ԃ�ǂݎ��
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
			result = g_pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = g_pGamePad[i]->Acquire();
		}

		// �R�Q�̊e�r�b�g�ɈӖ����������A�{�^�������ɉ����ăr�b�g���I���ɂ���
		//* y-axis (forward)
		if (dijs.lY < 0)					g_padState[i] |= BUTTON_UP;
		//* y-axis (backward)
		if (dijs.lY > 0)					g_padState[i] |= BUTTON_DOWN;
		//* x-axis (left)
		if (dijs.lX < 0)					g_padState[i] |= BUTTON_LEFT;
		//* x-axis (right)
		if (dijs.lX > 0)					g_padState[i] |= BUTTON_RIGHT;
		//* �`�{�^��
		if (dijs.rgbButtons[0] & 0x80)	g_padState[i] |= BUTTON_A;
		//* �a�{�^��
		if (dijs.rgbButtons[1] & 0x80)	g_padState[i] |= BUTTON_B;
		//* �b�{�^��
		if (dijs.rgbButtons[2] & 0x80)	g_padState[i] |= BUTTON_C;
		//* �w�{�^��
		if (dijs.rgbButtons[3] & 0x80)	g_padState[i] |= BUTTON_X;
		//* �x�{�^��
		if (dijs.rgbButtons[4] & 0x80)	g_padState[i] |= BUTTON_Y;
		//* �y�{�^��
		if (dijs.rgbButtons[5] & 0x80)	g_padState[i] |= BUTTON_Z;
		//* �k�{�^��
		if (dijs.rgbButtons[6] & 0x80)	g_padState[i] |= BUTTON_L;
		//* �q�{�^��
		if (dijs.rgbButtons[7] & 0x80)	g_padState[i] |= BUTTON_R;
		//* �r�s�`�q�s�{�^��
		if (dijs.rgbButtons[8] & 0x80)	g_padState[i] |= BUTTON_START;
		//* �l�{�^��
		if (dijs.rgbButtons[9] & 0x80)	g_padState[i] |= BUTTON_M;

		// Trigger�ݒ�
		g_padTrigger[i] = ((lastPadState ^ g_padState[i])	// �O��ƈ���Ă���
			& g_padState[i]);					// ��������ON�̂��

	}
}

BOOL GamePad_IsPress(int padNo, DWORD button)
{
	return (button & g_padState[padNo]);
}

BOOL GamePad_IsTrigger(int padNo, DWORD button)
{
	return (button & g_padTrigger[padNo]);
}
