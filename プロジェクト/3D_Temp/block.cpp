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
	int nNumVtx; //頂点数
	DWORD sizeFVF; //頂点フォーマットのサイズ
	BYTE* pVtxBuff; //頂点バッファのポインタ

		//頂点数の取得
	nNumVtx = m_pMesh->GetNumVertices();
	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	D3DXVECTOR3 minpos = GetMinPos();
	D3DXVECTOR3 maxpos = GetMaxPos();

	//頂点数の取得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//x座標の最大値最小値チェック
		if (vtx.x > maxpos.x)
		{
			maxpos.x = vtx.x;
		}
		if (vtx.x < minpos.x)
		{
			minpos.x = vtx.x;
		}

		//y座標の最大値最小値チェック
		if (vtx.y > maxpos.y)
		{
			maxpos.y = vtx.y;
		}
		if (vtx.y < minpos.y)
		{
			minpos.y = vtx.y;
		}

		//z座標の最大値最小値チェック
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
void CBlock::HitBlock()
{
	//D3DXVECTOR3 pos = GetPos();

	////サイズ取得
	//D3DXVECTOR3 minpos = GetMinPos();
	//D3DXVECTOR3 maxpos = GetMaxPos();

	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	//オブジェクト取得
	//	CObject* pObj = CObject::Getobject(4, nCnt);
	//	if (pObj != nullptr)
	//	{//ヌルポインタじゃなければ
	//		//タイプ取得
	//		CObject::OBJECT_TYPE type = pObj->GetType();
	//		if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
	//		{
	//			CPlayer* pPlayer = (CPlayer*)pObj;
	//			pPlayer->GetPos(); //位置取得

	//			//サイズ取得
	//			pPlayer->GetMinPos();
	//			pPlayer->GetMaxPos();
	//			if (Bulletpos.x - Bulletsize.x >= pPlayer->GetPos().x - pPlayer->GetMinPos().x
	//				&& Bulletpos.x + Bulletsize.x <= pPlayer->GetPos().x + pPlayer->GetMaxPos().x
	//				&& Bulletpos.y - Bulletsize.y >= pPlayer->GetPos().z - pEnemy->GetSize().y
	//				&& Bulletpos.y + Bulletsize.y <= pPlayer->GetPos().z + pEnemy->GetSize().y)
	//			{//敵と弾が当たった時
	//				pEnemy->HitBullet();
	//				//弾の削除
	//				Release();
	//				CExplosion* pExplosion = CExplosion::Create(Bulletpos, D3DXVECTOR2(20.0f, 20.0f));
	//			}
	//		}
	//	}
	//}
}



