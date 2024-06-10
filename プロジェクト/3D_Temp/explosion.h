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
	static const int EXPLOSION_PRIORITY = 5; //描画順

	static const int TEX_SPLIT_X; //テクスチャの分割数
	static const int TEX_SPLIT_Y; //テクスチャの分割数
	static const int ANIMATION_FRAME; //アニメーションフレーム数
	CExplosion(int nPriority = EXPLOSION_PRIORITY);
	~CExplosion()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//爆発作成
	static CExplosion* Create(D3DXVECTOR3 pos,D3DXVECTOR2 size);
	static HRESULT Load(); //テクスチャのロード
	static HRESULT UnLoad(); //テクスチャのアンロード
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	float m_fLength; //対角線
	float m_fAngle; //角度
};