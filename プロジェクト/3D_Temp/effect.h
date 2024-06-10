//=============================================
//
//3DTemplate[effect.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _EFFECT_H_
#include "main.h"
#include "billboard.h"
#include "move_texture.h"

class CEffect : public CBillboard
{
public:
	static const int EFFECT_PRIORITY = 3; //�`�揇
	static const int TEX_SPLIT_X; //�e�N�X�`���̕�����
	static const int TEX_SPLIT_Y; //�e�N�X�`���̕�����
	static const int ANIMATION_FRAME; //�A�j���[�V�����t���[����
	CEffect(int nPriority = EFFECT_PRIORITY);
	~CEffect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�G�t�F�N�g�쐬
	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR col,int nLife);
	static HRESULT Load(); //�e�N�X�`���̃��[�h
	static HRESULT UnLoad(); //�e�N�X�`���̃A�����[�h
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	D3DXCOLOR m_col;
	float m_fLength; //�Ίp��
	float m_fAngle; //�p�x
	int m_nLife; //����
};
#endif