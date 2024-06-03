//=============================================
//
//2DTemplate[explosion.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "explosion.h"
#include "manager.h"

//�摜������
const int CExplosion::TEX_SPLIT_X = 4;
//�摜������
const int CExplosion::TEX_SPLIT_Y = 1;
//�摜�؂�ւ��J�E���g
const int CExplosion::ANIMATION_FRAME = 5;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CExplosion::m_pTextureTemp = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CExplosion::CExplosion(int nPriority):CMove_Texture(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CExplosion::~CExplosion()
{
}

//=============================================
//������
//=============================================
HRESULT CExplosion::Init()
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
	tex_pos.x = 0.0f;
	tex_pos.y = 0.0f;
	//�e�N�X�`�����W���
	SetTexPos(tex_pos);

	//�A�j���[�V�����t���[�����
	SetAnimFrame(ANIMATION_FRAME);

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_fAngle, m_fLength);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CExplosion::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CExplosion::Update()
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
		Release();
	}
}

//=============================================  
//�`��
//=============================================
void CExplosion::Draw()
{
	CObject2D::Draw();
}

//=============================================
//�����쐬
//=============================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CExplosion* pExplosion = new CExplosion;
	if (pExplosion != nullptr)
	{
		pExplosion->SetPos(pos); //pos�ݒ�
		pExplosion->SetSize(size); //�T�C�Y�ݒ�
		pExplosion->BindTexture(m_pTextureTemp);
		pExplosion->SetType(OBJECT_TYPE_EFFECT); //�^�C�v�ݒ�
		pExplosion->Init();
	}

	return pExplosion;
}

//=============================================
//�e�N�X�`�����[�h
//=============================================
HRESULT CExplosion::Load()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\explosion.png",
			&m_pTextureTemp);
	}
	return S_OK;
}

//=============================================
//�e�N�X�`���A�����[�h
//=============================================
HRESULT CExplosion::UnLoad()
{
	if (m_pTextureTemp != nullptr)
	{

		m_pTextureTemp->Release();
		m_pTextureTemp = nullptr;
	}

	return S_OK;
}
