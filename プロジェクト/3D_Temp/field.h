//=============================================
//
//3DTemplate[field.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _FIELD_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _FIELD_H_
#include "main.h"
#include "object3D.h"

//�����_���[�N���X
class CField : public CObject3D
{
public:
	CField(int nPriority = 3);
	~CField()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CField* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,D3DXVECTOR3 rot);
	static HRESULT Load(); //�e�N�X�`���̃��[�h
	static HRESULT UnLoad(); //�e�N�X�`���̃A�����[�h
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif