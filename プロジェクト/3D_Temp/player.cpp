//=============================================
//
//3DTemplate[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "block.h"

//�ʏ�̈ړ����x
const float CPlayer::DEFAULT_MOVE = 0.5f;
//�ʏ�̈ړ����x
const float CPlayer::DAMPING_COEFFICIENT = 0.3f;
//�����蔻��␳�l
const float CPlayer::COLISION_CORRECTION = 15.0f;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CPlayer::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer::m_pMesh = nullptr;

DWORD CPlayer::m_dwNumMat = 0;
//=============================================
//�R���X�g���N�^
//=============================================
CPlayer::CPlayer(int nPriority):CObjectX(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CPlayer::~CPlayer()
{
}

//=============================================
//������
//=============================================
HRESULT CPlayer::Init()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	LPDIRECT3DTEXTURE9 pTex;
	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\PlayerAnimation.png",
	//	&pTex);

	//CObjectX::BindTexture(pTex);

	CObjectX::BindXFile(m_pBuffMat, m_dwNumMat, m_pMesh);


	m_bSize = false;

	//�ړ��ʏ�����
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	return S_OK;
}


//=============================================
//�I��
//=============================================
void CPlayer::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//�X�V
//=============================================
void CPlayer::Update()
{
	PlayerMove();

	D3DXVECTOR3 pos = GetPos();

	//�ړ��ʂ��X�V(�����j
	m_move *= 1.0f - DAMPING_COEFFICIENT;

	m_oldpos = pos;

	pos += m_move;

	//���W���X�V
	SetPos(pos);

	D3DXVECTOR3 minpos = GetMinPos();
	D3DXVECTOR3 maxpos = GetMaxPos();

	
	HitBlock(m_oldpos);

	if (pos.x > SCREEN_WIDTH)
	{
		pos.x = 0.0f;
	}
	if (pos.y > SCREEN_HEIGHT)
	{
		pos.y = 0.0f;
	}
	
	//Turn(); //��]����
	//SizeChange(); //�g�k

	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	//if (pKeyboard->GetTrigger(DIK_SPACE))
	//{
	//	//�e����
	//	CBullet* CBullet = CBullet::Create(pos,D3DXVECTOR3(10.0f,0.0f,0.0f),D3DXVECTOR2(15.0f,15.0f),60);
	//}

}

//=============================================
//�`��
//=============================================
void CPlayer::Draw()
{
	CObjectX::Draw();
}

//=============================================
//����
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(pos); //pos�ݒ�
	pPlayer->SetRot(rot); //pos�ݒ�
	pPlayer->SetType(OBJECT_TYPE_PLAYER); //�^�C�v�ݒ�
	pPlayer->Init();
	
	return pPlayer;
}

//=============================================
//���[�h
//=============================================
HRESULT CPlayer::Load()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//if (m_pTextureTemp == nullptr)
	//{
	//	//�e�N�X�`���̓ǂݍ���
	//	D3DXCreateTextureFromFile(pDevice,
	//		"data\\TEXTURE\\download_image_1714032505054.png",
	//		&m_pTextureTemp);
	//}
	if (m_pBuffMat == nullptr && m_pMesh == nullptr)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\sphere.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);
	}
	return S_OK;
}

//=============================================
//an���[�h
//=============================================
HRESULT CPlayer::UnLoad()
{
	if (m_pTextureTemp != nullptr)
	{

		m_pTextureTemp->Release();
		m_pTextureTemp = nullptr;
	}
	if (m_pBuffMat != nullptr)
	{

		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
	if (m_pMesh != nullptr)
	{

		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	return S_OK;
}

//=============================================
//�ړ�����
//=============================================
void CPlayer::PlayerMove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_W))
	{
		vecDirection.z += 1.0f;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		vecDirection.z -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		vecDirection.x -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += 1.0f;
	}

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // �����ĂȂ��B
		m_move.x = 0.0f;
		m_move.y = 0.0f;
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		//�I�u�W�F�N�g2D����rot���擾
		D3DXVECTOR3 rot = GetRot();

		m_move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		m_move.z += cosf(rotMoveY) * DEFAULT_MOVE;
		//rot.x = rotMoveY + D3DX_PI;
		//rot����
		SetRot(rot);
		//if (g_Player.rot.y <= -D3DX_PI)
		//{
		//	g_Player.rot.y = D3DX_PI;
		//}

	}
}

//=============================================
//��]
//=============================================
void CPlayer::Turn()
{
	//�I�u�W�F�N�g2D����rot���擾
	D3DXVECTOR3 rot = GetRot();

	rot.z += 0.05f;

	if (rot.z >= D3DX_PI)
	{
		rot.z = -D3DX_PI;
	}
	
	//rot����
	SetRot(rot);
}

//=============================================
//�g�k
//=============================================
void CPlayer::SizeChange()
{
	//�I�u�W�F�N�g2D����size���擾

}

//=============================================
//�����蔻��
//=============================================
void CPlayer::HitBlock(D3DXVECTOR3 oldpos)
{
	D3DXVECTOR3 PlayerPos = GetPos();

	//�T�C�Y�擾
	D3DXVECTOR3 PlayerMin = GetMinPos();
	D3DXVECTOR3 PlayerMax = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(1, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{
				CBlock* pBlock = (CBlock*)pObj;

				if (oldpos.x + PlayerMax.x <= pBlock->GetPos().x + pBlock->GetMinPos().x
					&& PlayerPos.x + PlayerMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
					&& PlayerPos.z + PlayerMax.z < pBlock->GetPos().z + pBlock->GetMaxPos().z + COLISION_CORRECTION
					&& PlayerPos.z + PlayerMin.z > pBlock->GetPos().z + pBlock->GetMinPos().z - COLISION_CORRECTION)
				{//�����蔻��(X)
					PlayerPos.x = oldpos.x;
					m_move.x = 0.0f;
				}
				else if (oldpos.x + PlayerMin.x >= pBlock->GetPos().x + pBlock->GetMaxPos().x
					&& PlayerPos.x + PlayerMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
					&& PlayerPos.z + PlayerMax.z < pBlock->GetPos().z + pBlock->GetMaxPos().z + COLISION_CORRECTION
					&& PlayerPos.z + PlayerMin.z > pBlock->GetPos().z + pBlock->GetMinPos().z - COLISION_CORRECTION)
				{//�����蔻��(X)
					PlayerPos.x = oldpos.x;
					m_move.x = 0.0f;
				}

				if(oldpos.z + PlayerMax.z <= pBlock->GetPos().z + pBlock->GetMinPos().z
					&& PlayerPos.z + PlayerMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z
					&& oldpos.x + PlayerMax.x < pBlock->GetPos().x + pBlock->GetMaxPos().x + COLISION_CORRECTION
					&& oldpos.x + PlayerMin.x > pBlock->GetPos().x + pBlock->GetMinPos().x - COLISION_CORRECTION
					)
				{//�����蔻��(Z)
					PlayerPos.z = oldpos.z;
					m_move.z = 0.0f;
				}
				else if (oldpos.z + PlayerMin.z >= pBlock->GetPos().z + pBlock->GetMaxPos().z
					&& PlayerPos.z + PlayerMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
					&& oldpos.x + PlayerMax.x < pBlock->GetPos().x + pBlock->GetMaxPos().x + COLISION_CORRECTION
					&& oldpos.x + PlayerMin.x > pBlock->GetPos().x + pBlock->GetMinPos().x - COLISION_CORRECTION
					)
				{//�����蔻��(Z)
					PlayerPos.z = oldpos.z;
					m_move.z = 0.0f;
				}
			}

		}
	}
	SetPos(PlayerPos);
}
