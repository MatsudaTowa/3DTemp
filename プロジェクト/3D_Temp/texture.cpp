//=============================================
//
//3DTemplate[texture.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "texture.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		m_apTexture[nCnt] = nullptr;
	}

	m_nNumAll = 0;
}

//=============================================
//�f�X�g���N�^
//=============================================
CTexture::~CTexture()
{
}

//=============================================
//�e�N�X�`���j��
//=============================================
void CTexture::Unload()
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (m_apTexture[nCnt] != nullptr)
		{

			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
			m_texName[nCnt] = nullptr;

		}
	}
	m_nNumAll = 0;

}

//=============================================
//�e�N�X�`���o�^
//=============================================
int CTexture::Regist(const std::string* pTex)
{
	int nIdx;
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (m_apTexture[nCnt] == nullptr)
		{
			LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pTex->c_str(),
				&m_apTexture[nCnt]);

			nIdx = nCnt;
			m_nNumAll++;
			break;
		}
		else if (m_texName[m_nNumAll] == pTex)
		{
			nIdx = nCnt;
			break;
		}
	}
	return nIdx;
}

//=============================================
//�e�N�X�`���A�h���X�擾
//=============================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	return m_apTexture[nIdx];
}
