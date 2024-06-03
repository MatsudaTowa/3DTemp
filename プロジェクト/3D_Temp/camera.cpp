//=============================================
//
//3DTemplate[camera.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"

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
	m_posV = D3DXVECTOR3(0.0f, 100.0f, 200.0f); //���_
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
