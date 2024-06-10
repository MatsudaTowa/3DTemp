//=============================================
//
//3DTemplate[texture.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "texture.h"

//=============================================
//コンストラクタ
//=============================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_apTexture[nCnt] = nullptr;
	}
	m_texName = nullptr;

	m_nNumAll = 0;
}

//=============================================
//デストラクタ
//=============================================
CTexture::~CTexture()
{
}

//=============================================
//テクスチャ破棄
//=============================================
void CTexture::Unload()
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (m_apTexture[nCnt] != nullptr)
		{

			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
	}
	m_texName = nullptr;
	m_nNumAll = 0;

}

//=============================================
//テクスチャ登録
//=============================================
int CTexture::Regist(const std::string* pTex)
{
	int nIdx;
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (m_apTexture[nCnt] == nullptr)
		{
			nIdx = nCnt;
			m_nNumAll++;
			break;
		}
		else if (m_texName == pTex)
		{
			nIdx = nCnt;
			break;
		}
	}
	return nIdx;
}

//=============================================
//テクスチャアドレス取得
//=============================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	return m_apTexture[nIdx];
}
