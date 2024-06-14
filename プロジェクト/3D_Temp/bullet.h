//=============================================
//
//3DTemplate[bullet.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

class CBullet : public CBillboard
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int BULLET_PRIORITY = 4; //�`�揇
	CBullet(int nPriority = BULLET_PRIORITY);
	~CBullet()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�e�쐬
	static CBullet* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXVECTOR3 size,int nLife);
private:
	void HitBullet();
	D3DXVECTOR3 m_move;
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};