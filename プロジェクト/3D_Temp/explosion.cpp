//=============================================
//
//3DTemplate[explosion.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "explosion.h"
#include "manager.h"

//texパス
const std::string CExplosion::TEXTURE_NAME = "data\\TEXTURE\\explosion.png";
//画像分割数
const int CExplosion::TEX_SPLIT_X = 4;
//画像分割数
const int CExplosion::TEX_SPLIT_Y = 1;
//画像切り替わりカウント
const int CExplosion::ANIMATION_FRAME = 5;

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CExplosion::m_pTextureTemp = nullptr;

//=============================================
//コンストラクタ
//=============================================
CExplosion::CExplosion(int nPriority):CMove_Texture(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CExplosion::~CExplosion()
{
}

//=============================================
//初期化
//=============================================
HRESULT CExplosion::Init()
{
	//サイズ取得
	D3DXVECTOR2 size = GetSize();

	//対角線
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//角度
	m_fAngle = atan2f(size.x, size.y);

	//テクスチャ移動量取得
	D3DXVECTOR2 tex_move = GetTexMove();
	tex_move.x = 1.0f / (float)TEX_SPLIT_X;
	tex_move.y = 1.0f / (float)TEX_SPLIT_Y;
	//テクスチャ移動量代入
	SetTexMove(tex_move);

	//テクスチャ座標取得
	D3DXVECTOR2 tex_pos = GetTexPos();
	tex_pos.x = 0.0f;
	tex_pos.y = 0.0f;
	//テクスチャ座標代入
	SetTexPos(tex_pos);

	//アニメーションフレーム代入
	SetAnimFrame(ANIMATION_FRAME);

	//頂点設定
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_fAngle, m_fLength);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CExplosion::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CExplosion::Update()
{
	//テクスチャ情報取得
	D3DXVECTOR2 tex_pos = GetTexPos();
	D3DXVECTOR2 tex_move = GetTexMove();
	AnimationTex(tex_pos, tex_move);
	//アニメーション後のテクスチャ座標取得
	tex_pos = GetTexPos();
	//アニメーションを繰り返す
	if (tex_pos.x >= 1.0f)
	{
		Release();
	}
}

//=============================================  
//描画
//=============================================
void CExplosion::Draw()
{
	CObject2D::Draw();
}

//=============================================
//爆発作成
//=============================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CTexture* pTexture = CManager::GetTexture();

	CExplosion* pExplosion = new CExplosion;
	if (pExplosion != nullptr)
	{
		pExplosion->SetPos(pos); //pos設定
		pExplosion->SetSize(size); //サイズ設定
		pExplosion->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
		pExplosion->SetType(OBJECT_TYPE_EFFECT); //タイプ設定
		pExplosion->Init();
	}

	return pExplosion;
}
