//=============================================
//
//3DTemplate[bg.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BG_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BG_H_
#include "main.h"
#include "object2D.h"

//�����_���[�N���X
class CBg : public CObject2D
{
public:
	static const int BG_PRIORITY = 1;  //�`�揇
	CBg(int nPriority = BG_PRIORITY);
	~CBg()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBg* Create(D3DXVECTOR3 pos);
};
#endif