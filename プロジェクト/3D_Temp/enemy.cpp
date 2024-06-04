//=============================================
//
//3DTemplate[enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy.h"
#include "manager.h"
#include "explosion.h"
#include "bullet.h"

//�摜������
const int CEnemy::TEX_SPLIT_X = 1;
//�摜������
const int CEnemy::TEX_SPLIT_Y = 1;
//�摜�؂�ւ��J�E���g
const int CEnemy::ANIMATION_FRAME = 5;
//�ʏ�̈ړ����x
const float CEnemy::DEFAULT_MOVE = 3.0f;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CEnemy::m_pTextureTemp = nullptr;



//=============================================
//�R���X�g���N�^
//=============================================
CEnemy::CEnemy(int nPriority):CMove_Texture(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemy::~CEnemy()
{
}

//=============================================
//������
//=============================================
HRESULT CEnemy::Init()
{
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
	tex_pos.x = 1.0f;
	tex_pos.y = 1.0f;
	//�e�N�X�`�����W���
	SetTexPos(tex_pos);

	//�A�j���[�V�����t���[�����
	SetAnimFrame(ANIMATION_FRAME);

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), m_fAngle, m_fLength);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEnemy::Uninit()
{
	CObject2D::Uninit();
}


//=============================================
//�X�V
//=============================================
void CEnemy::Update()
{

	D3DXVECTOR2 size = GetSize();

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

	//�G�l�~�[�ړ�����
	EnemyMove();

	SetSize(size);
	//�Ίp��
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//�p�x
	m_fAngle = atan2f(size.x, size.y);

	//���_���W
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_fAngle, m_fLength);
}

//=============================================  
//�`��
//=============================================
void CEnemy::Draw()
{
	CObject2D::Draw();
}

//=============================================
//�G�l�~�[����
//=============================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int nLife)
{
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy != nullptr)
	{
		pEnemy->SetPos(pos); //pos�ݒ�
		pEnemy->SetSize(size); //�T�C�Y�ݒ�
		pEnemy->BindTexture(m_pTextureTemp);
		pEnemy->m_nLife = nLife;
		pEnemy->m_move = move;
		pEnemy->SetType(OBJECT_TYPE_ENEMY); //�^�C�v�ݒ�
		pEnemy->Init();
	}

	return pEnemy;
}

//=============================================
//�G�l�~�[�ړ�����
//=============================================
void CEnemy::EnemyMove()
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR2 size = GetSize();

	pos += m_move;
	if (pos.x + size.x >= SCREEN_WIDTH || pos.x - size.x <= 0)
	{
		m_move.x *= -1.0f;
	}
	if (pos.y + size.y >= SCREEN_HEIGHT || pos.y - size.y <= 0)
	{
		m_move.y *= -1.0f;
	}
	//���W���X�V
	SetPos(pos);
}

//=============================================
//�����蔻��
//=============================================
void CEnemy::HitBullet()
{
	D3DXVECTOR3 pos = GetPos();
	m_nLife--;
	if (m_nLife <= 0)
	{
		CExplosion* pExplosion = CExplosion::Create(pos, D3DXVECTOR2(50.0f, 50.0f));
		Release();
	}

}

//=============================================
//�e�N�X�`�����[�h
//=============================================
HRESULT CEnemy::Load()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\download_image_1714032505054.png",
			&m_pTextureTemp);
	}
	return S_OK;
}

//=============================================
//�e�N�X�`���A�����[�h
//=============================================
HRESULT CEnemy::UnLoad()
{
	if (m_pTextureTemp != nullptr)
	{

		m_pTextureTemp->Release();
		m_pTextureTemp = nullptr;
	}

	return S_OK;
}
