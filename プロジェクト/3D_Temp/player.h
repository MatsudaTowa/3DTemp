//=============================================
//
//3DTemplate[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //これが定義されてないとき

#define _PLAYER_H_
#include "main.h"
#include "objectX.h"
//プレイヤークラス
class CPlayer : public CObjectX
{
public:
	CPlayer(int nPriority = 8);
	~CPlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//プレイヤー作成
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static HRESULT Load(); //テクスチャのロード
	static HRESULT UnLoad(); //テクスチャのアンロード
private:
	static const float DEFAULT_MOVE; //通常時の移動
	static const float DAMPING_COEFFICIENT; //移動抵抗

	void PlayerMove(); //プレイヤー移動処理
	void Turn();	//回転処理
	void SizeChange();	//サイズ変更処理
	void HitBlock(D3DXVECTOR3 oldpos); //ブロック当たり判定

	D3DXVECTOR3 m_move; //速度
	D3DXVECTOR3 m_oldpos; //過去の位置
	bool m_bSize; //サイズ変更するかどうか

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //マテリアル情報
	static	DWORD m_dwNumMat; //マテリアル数;
};
#endif