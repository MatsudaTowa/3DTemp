//=============================================
//
//2DTemplate[block.h]
//Auther Matsuda Towa
//
//=============================================
#include "block.h"
#include "manager.h"
#include "explosion.h"
#include "player.h"

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CBlock::m_pTextureTemp = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CBlock::CBlock(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBlock::~CBlock()
{
}

//=============================================
//������
//=============================================
HRESULT CBlock::Init()
{
	//�T�C�Y�擾
	D3DXVECTOR2 size = GetSize();

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CBlock::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBlock::Update()
{
}

//=============================================
//�`��
//=============================================
void CBlock::Draw()
{
	CObject2D::Draw();
}

//=============================================
//�u���b�N����
//=============================================
CBlock* CBlock::Create(BLOCKTYPE type, D3DXVECTOR3 pos, D3DXVECTOR2 size, int nLife, bool bBreak)
{
	CBlock* pBlock = new CBlock;
	if (pBlock != nullptr)
	{
		pBlock->m_type = type;
		pBlock->SetPos(pos); //pos�ݒ�
		pBlock->SetSize(size); //�T�C�Y�ݒ�
		pBlock->m_nLife = nLife; //�������
		pBlock->m_bBreak = bBreak; //�󂹂邩�ǂ���
		pBlock->BindTexture(m_pTextureTemp);
		pBlock->SetType(OBJECT_TYPE_BLOCK); //�^�C�v�ݒ�
		pBlock->Init();
	}

	return pBlock;
}

//=============================================
//�e�N�X�`�����[�h
//=============================================
HRESULT CBlock::Load()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pTextureTemp == nullptr)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\ground000.png",
			&m_pTextureTemp);
	}
	return S_OK;
}

//=============================================
//�e�N�X�`���A�����[�h
//=============================================
HRESULT CBlock::UnLoad()
{
	if (m_pTextureTemp != nullptr)
	{

		m_pTextureTemp->Release();
		m_pTextureTemp = nullptr;
	}

	return S_OK;
}

//=============================================
//�����蔻��
//=============================================
void CBlock::HitBullet()
{
	D3DXVECTOR3 pos = GetPos();
	m_nLife--;
	if (m_nLife <= 0)
	{
		CExplosion* pExplosion = CExplosion::Create(pos, D3DXVECTOR2(50.0f, 50.0f));
		Release();
	}
}



