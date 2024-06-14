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
#include "effect.h"
#include "field.h"

//���f���p�X
const std::string CPlayer::MODEL_NAME = "data\\MODEL\\sphere.x";

//�ʏ�̈ړ����x
const float CPlayer::DEFAULT_MOVE = 0.5f;
//�ʏ�̈ړ����x
const float CPlayer::DAMPING_COEFFICIENT = 0.3f;

//�ʏ�̃W�����v��
const float CPlayer::DEFAULT_JUMP = 22.0f;

//�W�����v��
const int CPlayer::MAX_JUMPCNT = 2;

//�����蔻��␳�l
const float CPlayer::COLISION_CORRECTION = 15.5f;

//�d�͒l
const float CPlayer::GRAVITY_MOVE = 0.8f;
//�d�͍ő�l
const float CPlayer::GRAVITY_MAX = 32.0f;

//�v���C���[�����X�|�[���������W
const float CPlayer::DEADZONE_Y = -100.0f;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CPlayer::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer::m_pMesh = nullptr;

DWORD CPlayer::m_dwNumMat = 0;
//=============================================
//�R���X�g���N�^
//=============================================
CPlayer::CPlayer(int nPriority):CObjectX(nPriority),m_nJumpCnt(0)
{//�C�j�V�����C�U�[�ŃW�����v�J�E���g������
	m_bLanding = false; //���n
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
	//if (m_bLanding != true)
	//{//���n���ĂȂ�������d�͏������s
		Gravity();
	//}

	PlayerMove();

	D3DXVECTOR3 pos = GetPos();

	//�ړ��ʂ��X�V(�����j
	m_move *= 1.0f - DAMPING_COEFFICIENT;

	m_oldpos = pos;

	CEffect* pEffect = CEffect::Create(D3DXVECTOR3(pos.x,pos.y + 8.0f,pos.z), D3DXVECTOR3(10.0f, 10.0f ,0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), 30);

	pos += m_move;

	//���W���X�V
	SetPos(pos);

	D3DXVECTOR3 minpos = GetMinPos();
	D3DXVECTOR3 maxpos = GetMaxPos();
	
	HitBlock(m_oldpos);

	if (pos.y < DEADZONE_Y)
	{//���X�|�[������
		ReSpawn();
	}
	
	//Turn(); //��]����
	//SizeChange(); //�g�k

	CInputMouse* pMouse = CManager::GetMouse();

	if (pMouse->GetTrigger(0))
	{
		CBullet*pBullet = CBullet::Create(pos, D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * 7.0f, 0.0f, cosf(GetRot().y + D3DX_PI) * 7.0f),
										D3DXVECTOR3(10.0f,10.0f,0.0f),30);
	}

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
	CModel* pModel = CManager::GetModel();

	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(pos); //pos�ݒ�
	pPlayer->SetRot(rot); //pos�ݒ�
	pPlayer->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat,
					pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat,
					pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh);
	pPlayer->SetType(OBJECT_TYPE_PLAYER); //�^�C�v�ݒ�
	pPlayer->Init();
	
	return pPlayer;
}

//=============================================
//���X�|�[��
//=============================================
void CPlayer::ReSpawn()
{
	D3DXVECTOR3 PlayerPos = GetPos();
	PlayerPos = D3DXVECTOR3(50.0f, 0.5f, 0.0f);
	SetPos(PlayerPos);
}

//=============================================
//�d�͏���
//=============================================
void CPlayer::Gravity()
{
	if (m_move.y < GRAVITY_MAX)
	{
		m_move.y -= GRAVITY_MOVE;
	}
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
		m_move.z = 0.0f;
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
	if (m_nJumpCnt < MAX_JUMPCNT)
	{//�W�����v���ȉ���������
		if (pKeyboard->GetTrigger(DIK_SPACE))
		{
			m_move.y = DEFAULT_JUMP;
			m_bLanding = false; //��
			m_nJumpCnt++; //�W�����v�����Z
		}
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
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�u���b�N�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{
				CBlock* pBlock = (CBlock*)pObj;
				if (oldpos.x + PlayerMax.x <= pBlock->GetPos().x + pBlock->GetMinPos().x 
					&&PlayerPos.x + PlayerMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x)
				{
					if (oldpos.z + PlayerMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& oldpos.z + PlayerMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z
						&& oldpos.y + PlayerMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& oldpos.y + PlayerMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y)
					{//�����蔻��(X)
						PlayerPos.x = oldpos.x;
						m_move.x = 0.0f;
					}
				}

				if (oldpos.x + PlayerMin.x >= pBlock->GetPos().x + pBlock->GetMaxPos().x
					&& PlayerPos.x + PlayerMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x)
				{
					 if (oldpos.z + PlayerMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z 
					&& oldpos.z + PlayerMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z 
					&& oldpos.y + PlayerMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y 
					&& oldpos.y + PlayerMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y )
					{//�����蔻��(X)
						PlayerPos.x = oldpos.x;
						m_move.x = 0.0f;
					}
				}

				if (oldpos.z + PlayerMax.z <= pBlock->GetPos().z + pBlock->GetMinPos().z
					&& PlayerPos.z + PlayerMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z)
				{
					if (oldpos.x + PlayerMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& oldpos.x + PlayerMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& oldpos.y + PlayerMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& oldpos.y + PlayerMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y
						)
					{//�����蔻��(Z)
						PlayerPos.z = oldpos.z;
						m_move.z = 0.0f;
					}
				}

				if (oldpos.z + PlayerMin.z >= pBlock->GetPos().z + pBlock->GetMaxPos().z
					&& PlayerPos.z + PlayerMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z)
				{
					if ( oldpos.x + PlayerMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& oldpos.x + PlayerMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& oldpos.y + PlayerMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& oldpos.y + PlayerMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y
						)
					{//�����蔻��(Z)
						PlayerPos.z = oldpos.z;
						m_move.z = 0.0f;
					}
				}
				if (oldpos.y + PlayerMin.y >= pBlock->GetPos().y + pBlock->GetMaxPos().y
					&& PlayerPos.y + PlayerMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y)
				{//�����蔻��(Y)��
					if (oldpos.x + PlayerMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& oldpos.x + PlayerMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& oldpos.z + PlayerMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& oldpos.z + PlayerMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z)
					{
						PlayerPos.y = oldpos.y;
						m_bLanding = true; //���n
						m_move.y = 0.0f;
						m_nJumpCnt = 0; //�W�����v�����Z�b�g
					}
				}
				if (oldpos.y + PlayerMax.y <= pBlock->GetPos().y + pBlock->GetMinPos().y
					&& PlayerPos.y + PlayerMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y)
				{//�����蔻��(Y)��
					if (oldpos.x + PlayerMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& oldpos.x + PlayerMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& oldpos.z + PlayerMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& oldpos.z + PlayerMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z)
					{
						PlayerPos.y = oldpos.y;
					}
				}
			}

			//���Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
			{
				CField* pField = (CField*)pObj;
				if (oldpos.y + PlayerMin.y >= pField->GetPos().y
					&& PlayerPos.y + PlayerMin.y <= pField->GetPos().y)
				{
					if (oldpos.x + PlayerMin.x < pField->GetPos().x + pField->GetSize().x
						&& oldpos.x + PlayerMax.x > pField->GetPos().x - pField->GetSize().x
						&& oldpos.z + PlayerMin.z < pField->GetPos().z + pField->GetSize().z
						&& oldpos.z + PlayerMax.z > pField->GetPos().z - pField->GetSize().z)
					{//�����蔻��(Y)
						PlayerPos.y = oldpos.y;
						m_move.y = 0.0f;
						m_bLanding = true; //���n
						m_nJumpCnt = 0; //�W�����v�����Z�b�g
					}
				}


				
			}
		}
	}
	SetPos(PlayerPos);
}
