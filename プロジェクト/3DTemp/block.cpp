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

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CBlock::m_pTextureTemp = nullptr;

//=============================================
//コンストラクタ
//=============================================
CBlock::CBlock(int nPriority):CObject2D(nPriority)
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
	//サイズ取得
	D3DXVECTOR2 size = GetSize();

	//頂点設定
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================
//終了
//=============================================
void CBlock::Uninit()
{
	CObject2D::Uninit();
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
	CObject2D::Draw();
}

//=============================================
//ブロック生成
//=============================================
CBlock* CBlock::Create(BLOCKTYPE type, D3DXVECTOR3 pos, D3DXVECTOR2 size, int nLife, bool bBreak)
{
	CBlock* pBlock = new CBlock;
	if (pBlock != nullptr)
	{
		pBlock->m_type = type;
		pBlock->SetPos(pos); //pos設定
		pBlock->SetSize(size); //サイズ設定
		pBlock->m_nLife = nLife; //寿命代入
		pBlock->m_bBreak = bBreak; //壊せるかどうか
		pBlock->BindTexture(m_pTextureTemp);
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
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\ground000.png",
			&m_pTextureTemp);
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



