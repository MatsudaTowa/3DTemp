//=============================================
//
//2DTemplate[bullet.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "object2D.h"

class CBullet : public CObject2D
{
public:
	CBullet(int nPriority = 1);
	~CBullet()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�e�쐬
	static CBullet* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXVECTOR2 size,int nLife);
	static HRESULT Load(); //�e�N�X�`���̃��[�h
	static HRESULT UnLoad(); //�e�N�X�`���̃A�����[�h
private:
	void HitBullet();
	D3DXVECTOR3 m_move;
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};