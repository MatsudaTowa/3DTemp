//=============================================
//
//3DTemplate[block.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BLOCK_H_ //これが定義されてないとき

#define _BLOCK_H_
#include "main.h"
#include "object2D.h"

class CBlock : public CObject2D
{
public:
	typedef enum
	{
		BLOCKTYPE_NONE = 0,
		BLOCKTYPE_FIELD,
		BLOCKTYPE_BREAK,
		BLOCKTYPE_MAX,
	}BLOCKTYPE;

	CBlock(int nPriority = 1);
	~CBlock()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//ブロック作成
	static CBlock* Create(BLOCKTYPE type,D3DXVECTOR3 pos, D3DXVECTOR2 size, int nLife,bool bBreak);
	static HRESULT Load(); //テクスチャのロード
	static HRESULT UnLoad(); //テクスチャのアンロード
private:

	BLOCKTYPE m_type;
	bool m_bBreak; //壊せるかどうか
	void HitBullet(); //弾との当たり判定
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif