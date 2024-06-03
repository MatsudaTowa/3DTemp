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
//�R���X�g���N�^
//=============================================
CBg::CBg(int nPriority) :CObject2D(nPriority)
{

}

//=============================================
//�f�X�g���N�^
//=============================================
CBg::~CBg()
{
}

//=============================================
//������
//=============================================
HRESULT CBg::Init()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	LPDIRECT3DTEXTURE9 pTex;
	LPDIRECT3DVERTEXBUFFER9 pBuff;
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\dog.png",
		&pTex);

	CObject2D::BindTexture(pTex);

	D3DXVECTOR2 size = GetSize();

	D3DXVECTOR2 tex_pos = GetTexPos();

	size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//�T�C�Y����
	SetSize(size);

	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CBg::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBg::Update()
{

}

//=============================================
//�`��
//=============================================
void CBg::Draw()
{
	CObject2D::Draw();

}

//=============================================
//����
//=============================================
CBg* CBg::Create(D3DXVECTOR3 pos)
{
	CBg* pBg = new CBg;
	//CObject *pObject = Getobject();
	if (pBg != nullptr)
	{
		pBg->SetPos(pos); //pos�ݒ�

		pBg->SetType(OBJECT_TYPE_BG); //�^�C�v�ݒ�

		pBg->Init();

	}
	return pBg;

}
