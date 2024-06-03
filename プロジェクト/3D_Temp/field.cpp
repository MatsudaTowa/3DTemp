//=============================================
//
//3DTemplate[field.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "field.h"
#include "manager.h"

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CField::m_pTextureTemp = nullptr;

//=============================================
//コンストラクタ
//=============================================
CField::CField(int nPriority):CObject3D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CField::~CField()
{
}

//=============================================
//初期化
//=============================================
HRESULT CField::Init()
{
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f,1.0f,0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================
//終了
//=============================================
void CField::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CField::Update()
{
}

//=============================================
//描画
//=============================================
void CField::Draw()
{
	CObject3D::Draw();

}

//=============================================
//生成
//=============================================
CField* CField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	CField* pField = new CField;
	if (pField != nullptr)
	{
		pField->SetPos(pos); //pos設定
		pField->SetSize(size); //サイズ設定
		pField->BindTexture(m_pTextureTemp);
		pField->Init();
	}

	return pField;
}

//=============================================
//テクスチャロード
//=============================================
HRESULT CField::Load()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pTextureTemp == nullptr)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\joji.png",
			&m_pTextureTemp);
	}
	return S_OK;
}

//=============================================
//テクスチャアンロード
//=============================================
HRESULT CField::UnLoad()
{
	if (m_pTextureTemp != nullptr)
	{

		m_pTextureTemp->Release();
		m_pTextureTemp = nullptr;
	}

	return S_OK;
}
