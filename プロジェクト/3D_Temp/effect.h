//=============================================
//
//2DTemplate[effect.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _EFFECT_H_ //これが定義されてないとき

#define _EFFECT_H_
#include "main.h"
#include "object2D.h"
#include "move_texture.h"

class CEffect : public CMove_Texture
{
public:
	static const int TEX_SPLIT_X; //テクスチャの分割数
	static const int TEX_SPLIT_Y; //テクスチャの分割数
	static const int ANIMATION_FRAME; //アニメーションフレーム数
	CEffect(int nPriority = 5);
	~CEffect()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//爆発作成
	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,D3DXCOLOR col,int nLife);
	static HRESULT Load(); //テクスチャのロード
	static HRESULT UnLoad(); //テクスチャのアンロード
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	D3DXCOLOR m_col;
	float m_fLength; //対角線
	float m_fAngle; //角度
	int m_nLife; //寿命
};
#endif