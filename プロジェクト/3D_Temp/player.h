//=============================================
//
//3DTemplate[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_H_
#include "main.h"
#include "objectX.h"
//�v���C���[�N���X
class CPlayer : public CObjectX
{
public:
	CPlayer(int nPriority = 8);
	~CPlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�v���C���[�쐬
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static HRESULT Load(); //�e�N�X�`���̃��[�h
	static HRESULT UnLoad(); //�e�N�X�`���̃A�����[�h
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

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	static	DWORD m_dwNumMat; //�}�e���A����;
};
#endif