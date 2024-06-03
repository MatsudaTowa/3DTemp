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
	CBg(int nPriority = 1);
	~CBg()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBg* Create(D3DXVECTOR3 pos);
};
#endif