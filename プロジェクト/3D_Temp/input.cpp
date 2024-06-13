//=============================================
//
//3DTemplate[input.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "input.h"

//�ÓI�����o������
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CInput::CInput()
{
	m_pDevice = nullptr;
}

//=============================================
//�f�X�g���N�^
//=============================================
CInput::~CInput()
{
}

//=============================================
//������
//=============================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CInput::Uninit()
{
	//���̓f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice = nullptr;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//������L�[�{�[�h

//=============================================
//�R���X�g���N�^
//=============================================
CInputKeyboard::CInputKeyboard()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CInputKeyboard::~CInputKeyboard()
{
}


//=============================================
//������
//=============================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance,hWnd);
	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�̃A�N�Z�X�����l��
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

//=============================================
//�X�V
//=============================================
void CInputKeyboard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX]; //���͏��
	int nCntKey;
	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire(); //�L�[�{�[�h�̃A�N�Z�X�����l��
	}
}

//=============================================
//�L�[�{�[�h�̏����擾
//=============================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) != 0;
}
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) != 0;
}

//������}�E�X

//=============================================
//�R���X�g���N�^
//=============================================
CInputMouse::CInputMouse()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CInputMouse::~CInputMouse()
{
}

//=============================================
//������
//=============================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	m_MousePos = { 0.0f,0.0f,0.0f };
	m_MouseMove = { 0.0f,0.0f,0.0f };
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;


	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return E_FAIL;
	}

	//�}�E�X�̃A�N�Z�X�����l��
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CInputMouse::Uninit()
{
	CInput::Uninit();
}

//=============================================
//�X�V
//=============================================
void CInputMouse::Update()
{
BYTE aMouseState[NUM_MOUSE_MAX]; //���͏��
	DIMOUSESTATE zdiMouseState;
	int nCntMouse;
	for (nCntMouse = 0; nCntMouse < NUM_MOUSE_MAX; nCntMouse++)
	{
		//���̓f�o�C�X����f�[�^���擾
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(zdiMouseState), &zdiMouseState)))
		{

			m_KeyStateTrigger.rgbButtons[nCntMouse] = (m_KeyState.rgbButtons[nCntMouse] ^ zdiMouseState.rgbButtons[nCntMouse]) & zdiMouseState.rgbButtons[nCntMouse];
			m_KeyState.rgbButtons[nCntMouse] = zdiMouseState.rgbButtons[nCntMouse]; //�L�[�{�[�h�̃v���X����ۑ�
		}
		else
		{
			m_pDevice->Acquire(); //�L�[�{�[�h�̃A�N�Z�X�����l��
		}
	}

	//ZeroMemory(&pMouseMove, sizeof(POINT));

	D3DXVECTOR3 OldMousePos = m_MousePos;

	POINT pMouseMove;

	GetCursorPos(&pMouseMove);

	m_MousePos.x = (float)pMouseMove.x;
	m_MousePos.y = (float)pMouseMove.y;

	m_MouseMove.x = m_MousePos.x - OldMousePos.x;
	m_MouseMove.y = m_MousePos.y - OldMousePos.y;
	m_MouseMove.z = m_MousePos.z - OldMousePos.z;
}

//=============================================
//�}�E�X�̏����擾
//=============================================
bool CInputMouse::GetPress(int nKey)
{
	return(m_KeyState.rgbButtons[nKey] & 0x80) != 0;
}
bool CInputMouse::GetTrigger(int nKey)
{
	return(m_KeyStateTrigger.rgbButtons[nKey] & 0x80) != 0;
}
D3DXVECTOR3 CInputMouse::GetMouseMove(void)
{
	return(m_MouseMove);
}