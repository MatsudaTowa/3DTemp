//=============================================
//
//3DTemplate[title_screen.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _TITLE_SCREEN_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TITLE_SCREEN_H_
#include "main.h"
#include "object2D.h"

//�����_���[�N���X
class CTitle_Screen : public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int TITLE_SCREEN_PRIORITY = 90;  //�`�揇
	CTitle_Screen(int nPriority = TITLE_SCREEN_PRIORITY);
	~CTitle_Screen()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CTitle_Screen* Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif