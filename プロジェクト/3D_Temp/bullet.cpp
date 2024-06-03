//=============================================
//
//3DTemplate[bullet.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "bullet.h"
#include "manager.h"
#include "explosion.h"
#include "effect.h"
#include "enemy.h"

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CBullet::m_pTextureTemp = nullptr;

//=============================================
//コンストラクタ
//=============================================
CBullet::CBullet(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CBullet::~CBullet()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBullet::Init()
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
void CBullet::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CBullet::Update()
{
	D3DXVECTOR3 pos = GetPos();
	CEffect*pEffect = CEffect::Create(pos, D3DXVECTOR2(20.0f, 20.0f),D3DXCOLOR(1.0f,0.0f,0.0f,0.5f),30);
	pos += m_move;
	//座標を更新
	SetPos(pos);
	//頂点座標
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	HitBullet();

	if (m_nLife > 0)
	{
		m_nLife--;
	}
	else
	{
		Release();
		CExplosion*pExplosion = CExplosion::Create(pos,D3DXVECTOR2(20.0f,20.0f));
	}
}

//=============================================  
//描画
//=============================================
void CBullet::Draw()
{
	CObject2D::Draw();
}

//=============================================
//弾作成
//=============================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size,int nLife)
{
	CBullet* pBullet = new CBullet;
	if (pBullet != nullptr)
	{
		pBullet->SetPos(pos); //pos設定
		pBullet->SetSize(size); //サイズ設定
		pBullet->m_move = move; //移動量代入
		pBullet->m_nLife = nLife; //寿命代入
     	pBullet->BindTexture(m_pTextureTemp);
		pBullet->SetType(OBJECT_TYPE_BULLET); //タイプ設定
		pBullet->Init();
	}

	return pBullet;
}

//=============================================
//テクスチャロード
//=============================================
HRESULT CBullet::Load()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\download_image_1714032366975.png",
			&m_pTextureTemp);
	}
	return S_OK;
}

//=============================================
//テクスチャアンロード
//=============================================
HRESULT CBullet::UnLoad()
{
	if (m_pTextureTemp != nullptr)
	{

   		m_pTextureTemp->Release();
		m_pTextureTemp = nullptr;
	}

	return S_OK;
}

void CBullet::HitBullet()
{
	D3DXVECTOR3 Bulletpos = GetPos();
	//サイズ取得
	D3DXVECTOR2 Bulletsize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject*pObj =CObject::Getobject(4,nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
			{
				CEnemy* pEnemy = (CEnemy*)pObj;
				pEnemy->GetPos(); //位置取得
				pEnemy->GetSize(); //サイズ取得
				if (Bulletpos.x - Bulletsize.x >= pEnemy->GetPos().x - pEnemy->GetSize().x
					&& Bulletpos.x + Bulletsize.x <= pEnemy->GetPos().x + pEnemy->GetSize().x
					&& Bulletpos.y - Bulletsize.y >= pEnemy->GetPos().y - pEnemy->GetSize().y
					&& Bulletpos.y + Bulletsize.y <= pEnemy->GetPos().y + pEnemy->GetSize().y)
				{//敵と弾が当たった時
					pEnemy->HitBullet();
					//弾の削除
					Release();
					CExplosion* pExplosion = CExplosion::Create(Bulletpos, D3DXVECTOR2(20.0f, 20.0f));
				}
			}
		}
	}
}
