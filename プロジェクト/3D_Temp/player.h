//=============================================
//
//3DTemplate[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //これが定義されてないとき

#define _PLAYER_H_
#include "main.h"
#include "object2D.h"
#include "move_texture.h"
//レンダラークラス
class CPlayer : public CMove_Texture
{
public:
	static const int TEX_SPLIT_X; //テクスチャの分割数
	static const int TEX_SPLIT_Y; //テクスチャの分割数
	static const int ANIMATION_FRAME; //アニメーションフレーム数
	CPlayer(int nPriority = 4);
	~CPlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//プレイヤー作成
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
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
	float m_fLength; //対角線
	float m_fAngle; //角度
};
#endif