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

//���f���p�X
const std::string CBlock::MODEL_NAME = "data\\MODEL\\box.x";

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
	CModel* pModel = CManager::GetModel();

	CBlock* pBlock = new CBlock;
	if (pBlock != nullptr)
	{
		pBlock->m_type = type;
		pBlock->SetPos(pos); //pos�ݒ�
		pBlock->SetRot(rot); //pos�ݒ�
		pBlock->m_nLife = nLife; //�������
		pBlock->m_bBreak = bBreak; //�󂹂邩�ǂ���
		//pBlock->BindTexture(m_pTextureTemp);
		pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat,
			pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat,
			pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh);
		pBlock->SetType(OBJECT_TYPE_BLOCK); //�^�C�v�ݒ�
		pBlock->Init();
	}

	return pBlock;
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



