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
