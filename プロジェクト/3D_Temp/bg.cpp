//=============================================
//
//3DTemplate[bg.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "bg.h"
#include "manager.h"
#include "object.h"

//=============================================
//コンストラクタ
//=============================================
CBg::CBg(int nPriority) :CObject2D(nPriority)
{

}

//=============================================
//デストラクタ
//=============================================
CBg::~CBg()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBg::Init()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	LPDIRECT3DTEXTURE9 pTex;
	LPDIRECT3DVERTEXBUFFER9 pBuff;
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\dog.png",
		&pTex);

	CObject2D::BindTexture(pTex);

	D3DXVECTOR2 size = GetSize();

	D3DXVECTOR2 tex_pos = GetTexPos();

	size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//サイズを代入
	SetSize(size);

	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CBg::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CBg::Update()
{

}

//=============================================
//描画
//=============================================
void CBg::Draw()
{
	CObject2D::Draw();

}

//=============================================
//生成
//=============================================
CBg* CBg::Create(D3DXVECTOR3 pos)
{
	CBg* pBg = new CBg;
	//CObject *pObject = Getobject();
	if (pBg != nullptr)
	{
		pBg->SetPos(pos); //pos設定

		pBg->SetType(OBJECT_TYPE_BG); //タイプ設定

		pBg->Init();

	}
	return pBg;

}
