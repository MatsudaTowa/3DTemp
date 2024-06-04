//=============================================
//
//3DTemplate[block.h]
//Auther Matsuda Towa
//
//=============================================
#include "block.h"
#include "manager.h"
#include "explosion.h"
#include "player.h"

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CBlock::m_pTextureTemp = nullptr;


LPD3DXBUFFER CBlock::m_pBuffMat = nullptr;

LPD3DXMESH CBlock::m_pMesh = nullptr;

DWORD CBlock::m_dwNumMat = 0;

//=============================================
//�R���X�g���N�^
//=============================================
CBlock::CBlock(int nPriority):CObjectX(nPriority)
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
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CBlock::Uninit()
{
	CObjectX::Uninit();
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
	CObjectX::Draw();
}

//=============================================
//�u���b�N����
//=============================================
CBlock* CBlock::Create(BLOCKTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, bool bBreak)
{
	CBlock* pBlock = new CBlock;
	if (pBlock != nullptr)
	{
		pBlock->m_type = type;
		pBlock->SetPos(pos); //pos�ݒ�
		pBlock->SetRot(rot); //pos�ݒ�
		pBlock->m_nLife = nLife; //�������
		pBlock->m_bBreak = bBreak; //�󂹂邩�ǂ���
		pBlock->BindTexture(m_pTextureTemp);
		pBlock->BindXFile(m_pBuffMat, m_dwNumMat, m_pMesh);
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
	//if (m_pTextureTemp == nullptr)
	//{
	//	//�e�N�X�`���̓ǂݍ���
	//	D3DXCreateTextureFromFile(pDevice,
	//		"data\\TEXTURE\\ground000.png",
	//		&m_pTextureTemp);
	//}
	if (m_pBuffMat == nullptr && m_pMesh == nullptr)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\box.x",
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
//�e�N�X�`���A�����[�h
//=============================================
HRESULT CBlock::UnLoad()
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



