//=============================================
//
//3DTemplate[title_Screen.h]
//Auther Matsuda Towa
//
//=============================================
#include "title_screen.h"
#include "manager.h"
#include "object.h"


//texパス
const std::string CTitle_Screen::TEXTURE_NAME = "data\\TEXTURE\\title_test.png";

//=============================================
//コンストラクタ
//=============================================
CTitle_Screen::CTitle_Screen(int nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CTitle_Screen::~CTitle_Screen()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTitle_Screen::Init()
{
	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	//サイズを代入
	SetSize(size);

	//頂点設定
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CTitle_Screen::Uninit()
{
	CObject2D::Uninit();

}

//=============================================
//更新
//=============================================
void CTitle_Screen::Update()
{
}

//=============================================
//描画
//=============================================
void CTitle_Screen::Draw()
{
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CTitle_Screen* CTitle_Screen::Create(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetTexture();
	CTitle_Screen* pTitle_Screen = new CTitle_Screen;
	//CObject *pObject = Getobject();
	if (pTitle_Screen != nullptr)
	{
		pTitle_Screen->SetPos(pos); //pos設定

		pTitle_Screen->SetType(OBJECT_TYPE_TITLE); //タイプ設定

		pTitle_Screen->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

		pTitle_Screen->Init();

	}
	return pTitle_Screen;
}
