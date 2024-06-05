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
	int nNumVtx; //���_��
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff; //���_�o�b�t�@�̃|�C���^

		//���_���̎擾
	nNumVtx = m_pMesh->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	D3DXVECTOR3 minpos = GetMinPos();
	D3DXVECTOR3 maxpos = GetMaxPos();

	//���_���̎擾
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//x���W�̍ő�l�ŏ��l�`�F�b�N
		if (vtx.x > maxpos.x)
		{
			maxpos.x = vtx.x;
		}
		if (vtx.x < minpos.x)
		{
			minpos.x = vtx.x;
		}

		//y���W�̍ő�l�ŏ��l�`�F�b�N
		if (vtx.y > maxpos.y)
		{
			maxpos.y = vtx.y;
		}
		if (vtx.y < minpos.y)
		{
			minpos.y = vtx.y;
		}

		//z���W�̍ő�l�ŏ��l�`�F�b�N
		if (vtx.z > maxpos.z)
		{
			maxpos.z = vtx.z;
		}
		if (vtx.z < minpos.z)
		{
			minpos.z = vtx.z;
		}
	}
	m_pMesh->UnlockVertexBuffer();

	SetMinPos(minpos);
	SetMaxPos(maxpos);
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
void CBlock::HitBlock()
{
	//D3DXVECTOR3 pos = GetPos();

	////�T�C�Y�擾
	//D3DXVECTOR3 minpos = GetMinPos();
	//D3DXVECTOR3 maxpos = GetMaxPos();

	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	//�I�u�W�F�N�g�擾
	//	CObject* pObj = CObject::Getobject(4, nCnt);
	//	if (pObj != nullptr)
	//	{//�k���|�C���^����Ȃ����
	//		//�^�C�v�擾
	//		CObject::OBJECT_TYPE type = pObj->GetType();
	//		if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
	//		{
	//			CPlayer* pPlayer = (CPlayer*)pObj;
	//			pPlayer->GetPos(); //�ʒu�擾

	//			//�T�C�Y�擾
	//			pPlayer->GetMinPos();
	//			pPlayer->GetMaxPos();
	//			if (Bulletpos.x - Bulletsize.x >= pPlayer->GetPos().x - pPlayer->GetMinPos().x
	//				&& Bulletpos.x + Bulletsize.x <= pPlayer->GetPos().x + pPlayer->GetMaxPos().x
	//				&& Bulletpos.y - Bulletsize.y >= pPlayer->GetPos().z - pEnemy->GetSize().y
	//				&& Bulletpos.y + Bulletsize.y <= pPlayer->GetPos().z + pEnemy->GetSize().y)
	//			{//�G�ƒe������������
	//				pEnemy->HitBullet();
	//				//�e�̍폜
	//				Release();
	//				CExplosion* pExplosion = CExplosion::Create(Bulletpos, D3DXVECTOR2(20.0f, 20.0f));
	//			}
	//		}
	//	}
	//}
}



