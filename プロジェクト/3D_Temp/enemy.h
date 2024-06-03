//=============================================
//
//2DTemplate[enemy.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ENEMY_H_
#include "main.h"
#include "object2D.h"
#include "move_texture.h"
//�����_���[�N���X
class CEnemy : public CMove_Texture
{
public:
	static const int TEX_SPLIT_X; //�e�N�X�`���̕�����
	static const int TEX_SPLIT_Y; //�e�N�X�`���̕�����
	static const int ANIMATION_FRAME; //�A�j���[�V�����t���[����
	CEnemy(int nPriority = 4);
	~CEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�G�l�~�[�쐬
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 size,int nLife);

	static HRESULT Load(); //�e�N�X�`���̃��[�h
	static HRESULT UnLoad(); //�e�N�X�`���̃A�����[�h
	void HitBullet(); //�����蔻��

private:
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	void EnemyMove(); //�G�l�~�[�ړ�����

	D3DXVECTOR3 m_move; //���x
	float m_fLength; //�Ίp��
	float m_fAngle; //�p�x
	int m_nLife;
};
#endif