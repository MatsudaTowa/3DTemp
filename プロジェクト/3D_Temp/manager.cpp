//=============================================
//
//3DTemplate[manager.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "bg.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "enemy.h"
#include "block.h"
#include "field.h"

//�����_���[�ݒ�
CRenderer*CManager::m_pRenderer = nullptr;

//�L�[�{�[�h�ݒ�
CInputKeyboard*CManager::m_pKeyboard = nullptr;

//�J�����ݒ�
CCamera*CManager::m_pCamera = nullptr;

//���C�g�ݒ�
CLight*CManager::m_pLight = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CManager::CManager()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CManager::~CManager()
{
}

//=============================================
//������
//=============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{

	//������������
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer();
		m_pRenderer->Init(hWnd,bWindow);
	}
	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CInputKeyboard();

		//�L�[�{�[�h�̏���������
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//�J��������
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera();
		m_pCamera->Init();
	}

	//���C�g����
	if (m_pLight == nullptr)
	{
		m_pLight = new CLight();
		m_pLight->Init();
	}
	
	//�ǂݍ���
	CBullet::Load();

	CExplosion::Load();

	CEffect::Load();

	CEnemy::Load();

	CBlock::Load();

	CField::Load();

	CPlayer::Load();

	////�w�i����
	//CBg* pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0));

	////�v���C���[����
	//CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f, 0.0f),D3DXVECTOR2(50.0f, 100.0f));

	//CEnemy* pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f, 0.0f), 
	//								D3DXVECTOR3(2.0f, 2.0f, 0.0f),D3DXVECTOR2(70.0f, 100.0f),1);

	CBlock* pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT,D3DXVECTOR3(0.0,0.0f,0.0f),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f),3,false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(10.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);
	
	CField*pField = CField::Create(D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(100.0f,0.0f,100.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(50.0f,0.5f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	return S_OK;
}

//=============================================
//�I������
//=============================================
void CManager::Uninit()
{
	//�j��
	CBullet::UnLoad();

	CExplosion::UnLoad();

	CEffect::UnLoad();

	CEnemy::UnLoad();

	CBlock::UnLoad();

	CField::UnLoad();

	CPlayer::UnLoad();

	CObject::ReleaseAll();
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	
	//�L�[�{�[�h�̏I������
	m_pKeyboard->Uninit();
}

//=============================================
//�X�V����
//=============================================
void CManager::Update()
{
	//�X�V����
	m_pRenderer->Update();
	m_pCamera->Update();
	m_pKeyboard->Update();
	CObject::UpdateAll();
}

//=============================================
//�`�揈��
//=============================================
void CManager::Draw()
{
	//�`�揈��
	m_pRenderer->Draw();

	//g_pRenderer->DrawFPS(nCntFPS);
}

//=============================================
//�����_���[�擾
//=============================================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

//=============================================
//�L�[�{�[�h���擾
//=============================================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//=============================================
//�J�����擾
//=============================================
CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

//=============================================
//���C�g�擾
//=============================================
CLight* CManager::GetLight()
{
	return m_pLight;
}
