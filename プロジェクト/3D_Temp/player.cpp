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

//�摜������
const int CPlayer::TEX_SPLIT_X = 4;
//�摜������
const int CPlayer::TEX_SPLIT_Y = 2;
//�摜�؂�ւ��J�E���g
const int CPlayer::ANIMATION_FRAME = 5;
//�ʏ�̈ړ����x
const float CPlayer::DEFAULT_MOVE = 3.0f;
//�ʏ�̈ړ����x
const float CPlayer::DAMPING_COEFFICIENT = 0.2f;
//=============================================
//�R���X�g���N�^
//=============================================
CPlayer::CPlayer(int nPriority):CMove_Texture(nPriority)
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
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PlayerAnimation.png",
		&pTex);

	CObject2D::BindTexture(pTex);

	m_bSize = false;

	//�ړ��ʏ�����
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	
	//�T�C�Y�擾
	D3DXVECTOR2 size = GetSize();

	//�Ίp��
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//�p�x
	m_fAngle = atan2f(size.x, size.y);

	//�e�N�X�`���ړ��ʎ擾
	D3DXVECTOR2 tex_move = GetTexMove();
	tex_move.x = 1.0f / (float)TEX_SPLIT_X;
	tex_move.y = 1.0f / (float)TEX_SPLIT_Y;
	//�e�N�X�`���ړ��ʑ��
	SetTexMove(tex_move);

	//�e�N�X�`�����W�擾
	D3DXVECTOR2 tex_pos = GetTexPos();
	tex_pos.x = 0.0f;
	tex_pos.y = 0.0f;
	//�e�N�X�`�����W���
	SetTexPos(tex_pos);

	//�A�j���[�V�����t���[�����
	SetAnimFrame(ANIMATION_FRAME);

	//���_�ݒ�
	SetVtx_FootPos(1.0f,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),m_fAngle,m_fLength);

	return S_OK;
}


//=============================================
//�I��
//=============================================
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CPlayer::Update()
{
	//�e�N�X�`�����擾
	D3DXVECTOR2 tex_pos = GetTexPos();	
	D3DXVECTOR2 tex_move = GetTexMove();

	AnimationTex(tex_pos, tex_move);
	//�A�j���[�V������̃e�N�X�`�����W�擾
	tex_pos = GetTexPos();
	//�A�j���[�V�������J��Ԃ�
	if (tex_pos.x >= 1.0f)
	{
		tex_pos.x = 0.0f;
	}
	SetTexPos(tex_pos);

	PlayerMove();

	D3DXVECTOR3 pos = GetPos();

	//�ړ��ʂ��X�V(�����j
	m_move *= 1.0f - DAMPING_COEFFICIENT;

	m_oldpos = pos;

	pos += m_move;

	//���W���X�V
	SetPos(pos);

	D3DXVECTOR2 size = GetSize();

	m_fLength = sqrtf(size.x * size.x + size.y * size.y);
	m_fAngle = atan2f(size.x, size.y);

	//���W���X�V
	SetSize(size);

	//���_���W
	SetVtx_FootPos(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_fAngle, m_fLength);
	
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
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		//�e����
		CBullet* CBullet = CBullet::Create(pos,D3DXVECTOR3(10.0f,0.0f,0.0f),D3DXVECTOR2(15.0f,15.0f),60);
	}

}

//=============================================
//�`��
//=============================================
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR2 size)
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(pos); //pos�ݒ�
	pPlayer->SetSize(size); //�T�C�Y�ݒ�
	pPlayer->SetType(OBJECT_TYPE_PLAYER); //�^�C�v�ݒ�
	pPlayer->Init();
	
	return pPlayer;
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
		vecDirection.y -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		vecDirection.y += 1.0f;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		vecDirection.x -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += 1.0f;
	}

	if (vecDirection.x == 0.0f && vecDirection.y == 0.0f)
	{ // �����ĂȂ��B
		m_move.x = 0.0f;
		m_move.y = 0.0f;
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.y);

		//�I�u�W�F�N�g2D����rot���擾
		D3DXVECTOR3 rot = GetRot();

		m_move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		m_move.y += cosf(rotMoveY) * DEFAULT_MOVE;
		rot.x = rotMoveY + D3DX_PI;
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
	D3DXVECTOR2 size = GetSize();
	if (m_bSize == false)
	{
		size.x += 3.0f;
		size.y += 3.0f;


	}
	else if (m_bSize == true)
	{
		size.x -= 3.0f;
		size.y -= 3.0f;

	}
	if (size.y >= 250.0f)
	{
		m_bSize = true;
	}
	else if (size.x <= 90.0f)
	{
		m_bSize = false;
	}

	//size����
	SetSize(size);
}

//=============================================
//�����蔻��
//=============================================
void CPlayer::HitBlock(D3DXVECTOR3 oldpos)
{
	D3DXVECTOR3 PlayerPos = GetPos();
	//�T�C�Y�擾

	D3DXVECTOR2 PlayerSize = GetSize();

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
				pBlock->GetPos(); //�ʒu�擾
				pBlock->GetSize(); //�T�C�Y�擾

				if (oldpos.x + PlayerSize.x <= pBlock->GetPos().x - pBlock->GetSize().x
					&& PlayerPos.x + PlayerSize.x >= pBlock->GetPos().x - pBlock->GetSize().x
					&& oldpos.y - PlayerSize.y < pBlock->GetPos().y + pBlock->GetSize().y
					&& oldpos.y > pBlock->GetPos().y - pBlock->GetSize().y)
				{//���Ƃ̓����蔻��(�v���C���[���猩�ĉE)
					PlayerPos.x = pBlock->GetPos().x - pBlock->GetSize().x - PlayerSize.x;
					m_move.x = 0.0f;
				}
				else if (oldpos.x - PlayerSize.x >= pBlock->GetPos().x + pBlock->GetSize().x
					&& PlayerPos.x - PlayerSize.x <= pBlock->GetPos().x + pBlock->GetSize().x
					&& oldpos.y - PlayerSize.y < pBlock->GetPos().y + pBlock->GetSize().y
					&& oldpos.y > pBlock->GetPos().y - pBlock->GetSize().y)
				{//���Ƃ̓����蔻��(�v���C���[���猩�č�)
					PlayerPos.x = pBlock->GetPos().x + pBlock->GetSize().x + PlayerSize.x;
					m_move.x = 0.0f;

				}

				if (oldpos.y <= pBlock->GetPos().y - pBlock->GetSize().y
					&& PlayerPos.y >= pBlock->GetPos().y - pBlock->GetSize().y
					&& oldpos.x + PlayerSize.x > pBlock->GetPos().x - pBlock->GetSize().x
					&& oldpos.x - PlayerSize.x < pBlock->GetPos().x + pBlock->GetSize().x)
				{//��
					PlayerPos.y = pBlock->GetPos().y - pBlock->GetSize().y;
					m_move.y = 0.0f;
				}
				else if (oldpos.y - PlayerSize.y >= pBlock->GetPos().y + pBlock->GetSize().y
					&& PlayerPos.y - PlayerSize.y <= pBlock->GetPos().y + pBlock->GetSize().y
					&& oldpos.x + PlayerSize.x > pBlock->GetPos().x - pBlock->GetSize().x
					&& oldpos.x - PlayerSize.x < pBlock->GetPos().x + pBlock->GetSize().x)
				{//���Ƃ̓����蔻��
					PlayerPos.y = pBlock->GetPos().y + pBlock->GetSize().y + PlayerSize.y;
					m_move.y = 0.0f;
				}
			}

		}
	}
	SetPos(PlayerPos);
}
