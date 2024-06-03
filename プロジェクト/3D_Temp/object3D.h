//=============================================
//
//3DTemplate[object3D.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _OBJECT3D_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _OBJECT3D_H_
#include "main.h"
#include "object.h"

//2D�I�u�W�F�N�g�N���X
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObject3D* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size); //�I�u�W�F�N�g�쐬
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

	//pos�̑��
	void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	//rot�̑��
	void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}

	//�T�C�Y�̑��
	void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	//�e�N�X�`�����W�̑��
	void SetTexPos(D3DXVECTOR2 tex)
	{
		m_tex_pos = tex;
	}

	//���_���W�̑��
	void SetVtx(D3DXVECTOR3 nor, D3DCOLOR col);

	//pos�̎擾
	D3DXVECTOR3& GetPos();

	//rot�̎擾
	D3DXVECTOR3& GetRot();

	//�T�C�Y�̎擾
	D3DXVECTOR2& GetSize();

	//�e�N�X�`�����W�̎擾
	D3DXVECTOR2& GetTexPos();

	//���_���擾
	LPDIRECT3DVERTEXBUFFER9& GetVtxBuff();

private:

	LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^


	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR2 m_size;
	D3DXVECTOR2 m_tex_pos; //tex���W

	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
};
#endif