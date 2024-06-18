//=============================================
//
//3DTemplate[result_Screen.h]
//Auther Matsuda Towa
//
//=============================================
#include "result_screen.h"
#include "manager.h"

//tex�p�X
const std::string CResult_Screen::TEXTURE_NAME = "data\\TEXTURE\\result_test.png";

//=============================================
//�R���X�g���N�^
//=============================================
CResult_Screen::CResult_Screen(int nPriority) :CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CResult_Screen::~CResult_Screen()
{
}

//=============================================
//������
//=============================================
HRESULT CResult_Screen::Init()
{
	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	//�T�C�Y����
	SetSize(size);

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CResult_Screen::Uninit()
{
	CObject2D::Uninit();

}

//=============================================
//�X�V
//=============================================
void CResult_Screen::Update()
{
}

//=============================================
//�`��
//=============================================
void CResult_Screen::Draw()
{
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CResult_Screen* CResult_Screen::Create(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetTexture();
	CResult_Screen* pResult_Screen = new CResult_Screen;
	//CObject *pObject = Getobject();
	if (pResult_Screen != nullptr)
	{
		pResult_Screen->SetPos(pos); //pos�ݒ�

		pResult_Screen->SetType(OBJECT_TYPE_RESULT); //�^�C�v�ݒ�

		pResult_Screen->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

		pResult_Screen->Init();

	}
	return pResult_Screen;
}
