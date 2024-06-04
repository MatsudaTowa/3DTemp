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

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CBlock::m_pTextureTemp = nullptr;


LPD3DXBUFFER CBlock::m_pBuffMat = nullptr;

LPD3DXMESH CBlock::m_pMesh = nullptr;

DWORD CBlock::m_dwNumMat = 0;

//=============================================
//コンストラクタ
//=============================================
CBlock::CBlock(int nPriority):CObjectX(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CBlock::~CBlock()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBlock::Init()
{
	return S_OK;
}

//=============================================
//終了
//=============================================
void CBlock::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CBlock::Update()
{
}

//=============================================
//描画
//=============================================
void CBlock::Draw()
{
	CObjectX::Draw();
}

//=============================================
//ブロック生成
//=============================================
CBlock* CBlock::Create(BLOCKTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, bool bBreak)
{
	CBlock* pBlock = new CBlock;
	if (pBlock != nullptr)
	{
		pBlock->m_type = type;
		pBlock->SetPos(pos); //pos設定
		pBlock->SetRot(rot); //pos設定
		pBlock->m_nLife = nLife; //寿命代入
		pBlock->m_bBreak = bBreak; //壊せるかどうか
		pBlock->BindTexture(m_pTextureTemp);
		pBlock->BindXFile(m_pBuffMat, m_dwNumMat, m_pMesh);
		pBlock->SetType(OBJECT_TYPE_BLOCK); //タイプ設定
		pBlock->Init();
	}

	return pBlock;
}

//=============================================
//テクスチャロード
//=============================================
HRESULT CBlock::Load()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//if (m_pTextureTemp == nullptr)
	//{
	//	//テクスチャの読み込み
	//	D3DXCreateTextureFromFile(pDevice,
	//		"data\\TEXTURE\\ground000.png",
	//		&m_pTextureTemp);
	//}
	if (m_pBuffMat == nullptr && m_pMesh == nullptr)
	{
		//Xファイルの読み込み
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
//テクスチャアンロード
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
//当たり判定
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



