//=============================================
//
//3DTemplate[camera.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"

//�ʏ�̈ړ����x
const float CCamera::DEFAULT_MOVE = 1.0f;

//�ʏ�̈ړ����x
const float CCamera::DAMPING_COEFFICIENT = 0.2f;

//�ʏ��Ԃ�Y�̋���
const float CCamera::DEFAULT_LENGTH_Y = 200.0f;

//�ʏ��Ԃ�Z�̋���
const float CCamera::DEFAULT_LENGTH_Z = 500.0f;

//=============================================
//�R���X�g���N�^
//=============================================
CCamera::CCamera()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CCamera::~CCamera()
{
}

//=============================================
//������
//=============================================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f); //���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //����

	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //������x�N�g��

	m_moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //���_�ړ���
	m_moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����_�ړ���

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�p�x
	m_rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //��]��

	D3DXVECTOR3 vecCamera = m_posR - m_posV;
	m_fLength = sqrtf(vecCamera.y * vecCamera.y + vecCamera.z * vecCamera.z);

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(vecCamera.y, vecCamera.z);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CCamera::Uninit()
{
}

//=============================================
//�X�V
//=============================================
void CCamera::Update()
{
	CameraTurn();
	CameraMove();

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
		//		m_rot.y -= D3DX_PI* 2.0f;
	}

	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
		//		m_rot.y -= D3DX_PI* 2.0f;
	}

	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	m_posV += m_moveV;
	m_posR += m_moveR;

	//�ړ��ʂ��X�V(�����j
	m_moveV.x += (0.0f - m_moveV.x) * DAMPING_COEFFICIENT;
	m_moveV.y += (0.0f - m_moveV.y) * DAMPING_COEFFICIENT;
	m_moveV.z += (0.0f - m_moveV.z) * DAMPING_COEFFICIENT;

	m_moveR.x += (0.0f - m_moveR.x) * DAMPING_COEFFICIENT;
	m_moveR.y += (0.0f - m_moveR.y) * DAMPING_COEFFICIENT;
	m_moveR.z += (0.0f - m_moveR.z) * DAMPING_COEFFICIENT;
}

//=============================================
//�J�����ݒ�
//=============================================
void CCamera::SetCamera()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1800.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 posV = m_posV;
	D3DXVECTOR3 posR = m_posR;

	posV.y += -15.0f;
	posR.y += 0.0f;

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,
		&posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=============================================
//�J�����ړ���
//=============================================
void CCamera::CameraMove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_J) == true)
	{
		m_moveV.x -= sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x -= sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z -= cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z -= cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

	}

	if (pKeyboard->GetPress(DIK_L) == true)
	{
		m_moveV.x += sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x += sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z += cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z += cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

	}


	if (pKeyboard->GetPress(DIK_I) == true)
	{
		m_moveV.x -= sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x -= sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z -= cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z -= cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

	}

	if (pKeyboard->GetPress(DIK_K) == true)
	{
		m_moveV.x += sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x += sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z += cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z += cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

	}
	//if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	//{ // �����ĂȂ��B
	//	m_moveV.x = 0.0f;
	//	m_moveV.z = 0.0f;
	//	m_moveR.x = 0.0f;
	//	m_moveR.z = 0.0f;
	//}
	//else
	//{
	//	float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

	//	m_moveV.x += sinf(rotMoveY) * DEFAULT_MOVE;
	//	m_moveV.z += cosf(rotMoveY) * DEFAULT_MOVE;

	//	m_moveR.x += sinf(rotMoveY) * DEFAULT_MOVE;
	//	m_moveR.z += cosf(rotMoveY) * DEFAULT_MOVE;

	//	m_rot.y = rotMoveY + D3DX_PI;

	//	//if (g_Player.rot.y <= -D3DX_PI)
	//	//{
	//	//	g_Player.rot.y = D3DX_PI;
	//	//}

	//}
	//if (GetKeyboardPress(DIK_J) == true)
	//{
	//	m_moveV.x -= sinf(D3DX_PI / 2 + m_rot.y) * CAMERA_MOVE;
	//	m_moveR.x -= sinf(D3DX_PI / 2 + m_rot.y) * CAMERA_MOVE;

	//	m_moveV.z -= cosf(D3DX_PI / 2 + m_rot.y) * CAMERA_MOVE;
	//	m_moveR.z -= cosf(D3DX_PI / 2 + m_rot.y) * CAMERA_MOVE;

	//}

	//if (GetKeyboardPress(DIK_L) == true)
	//{
	//	m_moveV.x += sinf(D3DX_PI / 2 + m_rot.y) * CAMERA_MOVE;
	//	m_moveR.x += sinf(D3DX_PI / 2 + m_rot.y) * CAMERA_MOVE;

	//	m_moveV.z += cosf(D3DX_PI / 2 + m_rot.y) * CAMERA_MOVE;
	//	m_moveR.z += cosf(D3DX_PI / 2 + m_rot.y) * CAMERA_MOVE;

	//}


	//if (GetKeyboardPress(DIK_I) == true)
	//{
	//	m_moveV.x -= sinf(D3DX_PI + m_rot.y) * CAMERA_MOVE;
	//	m_moveR.x -= sinf(D3DX_PI + m_rot.y) * CAMERA_MOVE;

	//	m_moveV.z -= cosf(D3DX_PI + m_rot.y) * CAMERA_MOVE;
	//	m_moveR.z -= cosf(D3DX_PI + m_rot.y) * CAMERA_MOVE;

	//}

	//if (GetKeyboardPress(DIK_K) == true)
	//{
	//	m_moveV.x += sinf(D3DX_PI + m_rot.y) * CAMERA_MOVE;
	//	m_moveR.x += sinf(D3DX_PI + m_rot.y) * CAMERA_MOVE;

	//	m_moveV.z += cosf(D3DX_PI + m_rot.y) * CAMERA_MOVE;
	//	m_moveR.z += cosf(D3DX_PI + m_rot.y) * CAMERA_MOVE;
	//}
}

//=============================================
//�J������]��
//=============================================
void CCamera::CameraTurn()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	if (pKeyboard->GetPress(DIK_Q) == true)
	{
		m_rot.y -= 0.02f;

		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;

	}

	if (pKeyboard->GetPress(DIK_E) == true)
	{
		m_rot.y += 0.02f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
	}

	if (pKeyboard->GetPress(DIK_U) == true)
	{
		m_rot.y -= 0.02f;

		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
		//if (m_bCameraAngle == true)
		//{
		//	m_posV.y = DEFAULT_LENGTH_Y;
		//}
		//else if (m_bCameraAngle == false)
		//{
		//	m_posV.y = EDIT_LENGTH_Y;
		//}
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
	}

	if (pKeyboard->GetPress(DIK_O) == true)
	{
		m_rot.y += 0.02f;

		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
		//if (m_bCameraAngle == true)
		//{
		//	m_posV.y = DEFAULT_LENGTH_Y;
		//}
		//else if (m_bCameraAngle == false)
		//{
		//	m_posV.y = EDIT_LENGTH_Y;
		//}
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
	}
}
