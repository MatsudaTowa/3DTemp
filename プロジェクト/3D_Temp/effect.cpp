//=============================================
//
//3DTemplate[effect.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "effect.h"
#include "manager.h"

//�摜������
const int CEffect::TEX_SPLIT_X = 1;
//�摜������
const int CEffect::TEX_SPLIT_Y = 1;
//�摜�؂�ւ��J�E���g
const int CEffect::ANIMATION_FRAME = 5;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CEffect::m_pTextureTemp = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CEffect::CEffect(int nPriority):CMove_Texture(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEffect::~CEffect()
{
}

//=============================================
//������
//=============================================
HRESULT CEffect::Init()
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
	SetVtx(1.0f, m_col, m_fAngle, m_fLength);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEffect::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CEffect::Update()
{
	//�e�N�X�`�����擾
	D3DXVECTOR2 tex_pos = GetTexPos();
	D3DXVECTOR2 tex_move = GetTexMove();
	AnimationTex(tex_pos, tex_move);

	D3DXVECTOR2 size = GetSize();
	if (m_nLife > 0)
	{
		m_nLife--;
		size.x -= 0.4f;
		size.y -= 0.4f;
	}
	else
	{
		Release();
	}
	SetSize(size);
	//�Ίp��
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//�p�x
	m_fAngle = atan2f(size.x, size.y);
	//���_�ݒ�
	SetVtx(1.0f, m_col, m_fAngle, m_fLength);
}

//=============================================  
//�`��
//=============================================
void CEffect::Draw()
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject2D::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================
//�G�t�F�N�g����
//=============================================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, int nLife)
{
	CEffect* pEffect = new CEffect;
	if (pEffect != nullptr)
	{
		pEffect->SetPos(pos); //pos�ݒ�
		pEffect->SetSize(size); //�T�C�Y�ݒ�
		pEffect->BindTexture(m_pTextureTemp);
		pEffect->m_col = col;
		pEffect->m_nLife = nLife;
		pEffect->SetType(OBJECT_TYPE_EFFECT);
		pEffect->Init();
	}

	return pEffect;
}

//=============================================
//�e�N�X�`�����[�h
//=============================================
HRESULT CEffect::Load()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\effect000.jpg",
			&m_pTextureTemp);
	}
	return S_OK;
}

//=============================================
//�e�N�X�`���A�����[�h
//=============================================
HRESULT CEffect::UnLoad()
{
	if (m_pTextureTemp != nullptr)
	{

		m_pTextureTemp->Release();
		m_pTextureTemp = nullptr;
	}

	return S_OK;
}
