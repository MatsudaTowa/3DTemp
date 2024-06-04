//=============================================
//
//3DTemplate[block.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BLOCK_H_ //これが定義されてないとき

#define _BLOCK_H_
#include "main.h"
#include "objectX.h"

class CBlock : public CObjectX
{
public:
	typedef enum
	{
		BLOCKTYPE_NONE = 0,
		BLOCKTYPE_DEFAULT,
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
	static CBlock* Create(BLOCKTYPE type,D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,bool bBreak);
	static HRESULT Load(); //テクスチャのロード
	static HRESULT UnLoad(); //テクスチャのアンロード
private:

	BLOCKTYPE m_type;
	bool m_bBreak; //壊せるかどうか
	void HitBullet(); //弾との当たり判定
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh; //メッシュ情報
	static 	LPD3DXBUFFER m_pBuffMat; //マテリアル情報
	static	DWORD m_dwNumMat; //マテリアル数;
};
#endif