//=============================================
//
//3DTemplate[explosion.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "object2D.h"
#include "move_texture.h"

class CExplosion : public CMove_Texture
{
public:
	static const int EXPLOSION_PRIORITY = 5; //�`�揇

	static const int TEX_SPLIT_X; //�e�N�X�`���̕�����
	static const int TEX_SPLIT_Y; //�e�N�X�`���̕�����
	static const int ANIMATION_FRAME; //�A�j���[�V�����t���[����
	CExplosion(int nPriority = EXPLOSION_PRIORITY);
	~CExplosion()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�����쐬
	static CExplosion* Create(D3DXVECTOR3 pos,D3DXVECTOR2 size);
	static HRESULT Load(); //�e�N�X�`���̃��[�h
	static HRESULT UnLoad(); //�e�N�X�`���̃A�����[�h
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	float m_fLength; //�Ίp��
	float m_fAngle; //�p�x
};