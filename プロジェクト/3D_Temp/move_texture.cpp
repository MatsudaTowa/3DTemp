//=============================================
//
//2DTemplate[move_texture.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "move_texture.h"
#include "manager.h"


//=============================================
//コンストラクタ
//=============================================
CMove_Texture::CMove_Texture(int nPriority):CObject2D(nPriority)
{
	//アニメーションカウント初期化
	m_nAnimCnt = 0;
}

//=============================================
//デストラクタ
//=============================================
CMove_Texture::~CMove_Texture()
{
}

//=============================================
//初期化
//=============================================
HRESULT CMove_Texture::Init()
{

	return S_OK;
}

//=============================================
//終了
//=============================================
void CMove_Texture::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CMove_Texture::Update()
{
	//テクスチャ座標取得
	D3DXVECTOR2 tex_pos = GetTexPos();
}

//=============================================
//描画
//=============================================
void CMove_Texture::Draw()
{
	CObject2D::Draw();
}

//=============================================
//アニメーション処理
//=============================================
void CMove_Texture::AnimationTex(D3DXVECTOR2 tex_pos, D3DXVECTOR2 tex_move)
{
	m_nAnimCnt++;

	if (m_nAnimCnt >= m_nAnimFrame)
	{//フレーム数が達したら
		//テクスチャをずらす
		tex_pos.x += tex_move.x;
		m_tex_move = tex_move;

		m_nAnimCnt = 0;
	}

	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 vtxBuff = GetVtxBuff();
	if (vtxBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &vtxBuff, NULL);
	}

	VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標指定
	pVtx[0].tex = D3DXVECTOR2(tex_pos.x
		, tex_pos.y);
	pVtx[1].tex = D3DXVECTOR2(tex_pos.x + tex_move.x
		, tex_pos.y);
	pVtx[2].tex = D3DXVECTOR2(tex_pos.x
		, tex_pos.y + tex_move.y);
	pVtx[3].tex = D3DXVECTOR2(tex_pos.x + tex_move.x
		, tex_pos.y + tex_move.y);

	//アンロック
	vtxBuff->Unlock();

	//tex設定
 	SetTexPos(tex_pos);
}

//=============================================
//アニメーションフレーム取得
//=============================================
int CMove_Texture::GetAnimFrame()
{
	return m_nAnimFrame;
}

//=============================================
//テクスチャ移動量取得
//=============================================
D3DXVECTOR2& CMove_Texture::GetTexMove()
{
	return m_tex_move;
}
