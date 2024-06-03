//=============================================
//
//3DTemplate[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_H_
#include "main.h"
#include "object2D.h"
#include "move_texture.h"
//�����_���[�N���X
class CPlayer : public CMove_Texture
{
public:
	static const int TEX_SPLIT_X; //�e�N�X�`���̕�����
	static const int TEX_SPLIT_Y; //�e�N�X�`���̕�����
	static const int ANIMATION_FRAME; //�A�j���[�V�����t���[����
	CPlayer(int nPriority = 4);
	~CPlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�v���C���[�쐬
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
private:
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�
	static const float DAMPING_COEFFICIENT; //�ړ���R

	void PlayerMove(); //�v���C���[�ړ�����
	void Turn();	//��]����
	void SizeChange();	//�T�C�Y�ύX����
	void HitBlock(D3DXVECTOR3 oldpos); //�u���b�N�����蔻��

	D3DXVECTOR3 m_move; //���x
	D3DXVECTOR3 m_oldpos; //�ߋ��̈ʒu
	bool m_bSize; //�T�C�Y�ύX���邩�ǂ���
	float m_fLength; //�Ίp��
	float m_fAngle; //�p�x
};
#endif