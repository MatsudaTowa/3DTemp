//=============================================
//
//3DTemplate[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "block.h"

//画像分割数
const int CPlayer::TEX_SPLIT_X = 4;
//画像分割数
const int CPlayer::TEX_SPLIT_Y = 2;
//画像切り替わりカウント
const int CPlayer::ANIMATION_FRAME = 5;
//通常の移動速度
const float CPlayer::DEFAULT_MOVE = 3.0f;
//通常の移動速度
const float CPlayer::DAMPING_COEFFICIENT = 0.2f;
//=============================================
//コンストラクタ
//=============================================
CPlayer::CPlayer(int nPriority):CMove_Texture(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CPlayer::~CPlayer()
{
}

//=============================================
//初期化
//=============================================
HRESULT CPlayer::Init()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	LPDIRECT3DTEXTURE9 pTex;
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PlayerAnimation.png",
		&pTex);

	CObject2D::BindTexture(pTex);

	m_bSize = false;

	//移動量初期化
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	
	//サイズ取得
	D3DXVECTOR2 size = GetSize();

	//対角線
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//角度
	m_fAngle = atan2f(size.x, size.y);

	//テクスチャ移動量取得
	D3DXVECTOR2 tex_move = GetTexMove();
	tex_move.x = 1.0f / (float)TEX_SPLIT_X;
	tex_move.y = 1.0f / (float)TEX_SPLIT_Y;
	//テクスチャ移動量代入
	SetTexMove(tex_move);

	//テクスチャ座標取得
	D3DXVECTOR2 tex_pos = GetTexPos();
	tex_pos.x = 0.0f;
	tex_pos.y = 0.0f;
	//テクスチャ座標代入
	SetTexPos(tex_pos);

	//アニメーションフレーム代入
	SetAnimFrame(ANIMATION_FRAME);

	//頂点設定
	SetVtx_FootPos(1.0f,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),m_fAngle,m_fLength);

	return S_OK;
}


//=============================================
//終了
//=============================================
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CPlayer::Update()
{
	//テクスチャ情報取得
	D3DXVECTOR2 tex_pos = GetTexPos();	
	D3DXVECTOR2 tex_move = GetTexMove();

	AnimationTex(tex_pos, tex_move);
	//アニメーション後のテクスチャ座標取得
	tex_pos = GetTexPos();
	//アニメーションを繰り返す
	if (tex_pos.x >= 1.0f)
	{
		tex_pos.x = 0.0f;
	}
	SetTexPos(tex_pos);

	PlayerMove();

	D3DXVECTOR3 pos = GetPos();

	//移動量を更新(減速）
	m_move *= 1.0f - DAMPING_COEFFICIENT;

	m_oldpos = pos;

	pos += m_move;

	//座標を更新
	SetPos(pos);

	D3DXVECTOR2 size = GetSize();

	m_fLength = sqrtf(size.x * size.x + size.y * size.y);
	m_fAngle = atan2f(size.x, size.y);

	//座標を更新
	SetSize(size);

	//頂点座標
	SetVtx_FootPos(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_fAngle, m_fLength);
	
	HitBlock(m_oldpos);

	if (pos.x > SCREEN_WIDTH)
	{
		pos.x = 0.0f;
	}
	if (pos.y > SCREEN_HEIGHT)
	{
		pos.y = 0.0f;
	}
	
	//Turn(); //回転処理
	//SizeChange(); //拡縮

	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		//弾生成
		CBullet* CBullet = CBullet::Create(pos,D3DXVECTOR3(10.0f,0.0f,0.0f),D3DXVECTOR2(15.0f,15.0f),60);
	}

}

//=============================================
//描画
//=============================================
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR2 size)
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(pos); //pos設定
	pPlayer->SetSize(size); //サイズ設定
	pPlayer->SetType(OBJECT_TYPE_PLAYER); //タイプ設定
	pPlayer->Init();
	
	return pPlayer;
}

//=============================================
//移動処理
//=============================================
void CPlayer::PlayerMove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_W))
	{
		vecDirection.y -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		vecDirection.y += 1.0f;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		vecDirection.x -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += 1.0f;
	}

	if (vecDirection.x == 0.0f && vecDirection.y == 0.0f)
	{ // 動いてない。
		m_move.x = 0.0f;
		m_move.y = 0.0f;
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.y);

		//オブジェクト2Dからrotを取得
		D3DXVECTOR3 rot = GetRot();

		m_move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		m_move.y += cosf(rotMoveY) * DEFAULT_MOVE;
		rot.x = rotMoveY + D3DX_PI;
		//rotを代入
		SetRot(rot);
		//if (g_Player.rot.y <= -D3DX_PI)
		//{
		//	g_Player.rot.y = D3DX_PI;
		//}

	}
}

//=============================================
//回転
//=============================================
void CPlayer::Turn()
{
	//オブジェクト2Dからrotを取得
	D3DXVECTOR3 rot = GetRot();

	rot.z += 0.05f;

	if (rot.z >= D3DX_PI)
	{
		rot.z = -D3DX_PI;
	}
	
	//rotを代入
	SetRot(rot);
}

//=============================================
//拡縮
//=============================================
void CPlayer::SizeChange()
{
	//オブジェクト2Dからsizeを取得
	D3DXVECTOR2 size = GetSize();
	if (m_bSize == false)
	{
		size.x += 3.0f;
		size.y += 3.0f;


	}
	else if (m_bSize == true)
	{
		size.x -= 3.0f;
		size.y -= 3.0f;

	}
	if (size.y >= 250.0f)
	{
		m_bSize = true;
	}
	else if (size.x <= 90.0f)
	{
		m_bSize = false;
	}

	//sizeを代入
	SetSize(size);
}

//=============================================
//当たり判定
//=============================================
void CPlayer::HitBlock(D3DXVECTOR3 oldpos)
{
	D3DXVECTOR3 PlayerPos = GetPos();
	//サイズ取得

	D3DXVECTOR2 PlayerSize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(1, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{
				CBlock* pBlock = (CBlock*)pObj;
				pBlock->GetPos(); //位置取得
				pBlock->GetSize(); //サイズ取得

				if (oldpos.x + PlayerSize.x <= pBlock->GetPos().x - pBlock->GetSize().x
					&& PlayerPos.x + PlayerSize.x >= pBlock->GetPos().x - pBlock->GetSize().x
					&& oldpos.y - PlayerSize.y < pBlock->GetPos().y + pBlock->GetSize().y
					&& oldpos.y > pBlock->GetPos().y - pBlock->GetSize().y)
				{//横との当たり判定(プレイヤーから見て右)
					PlayerPos.x = pBlock->GetPos().x - pBlock->GetSize().x - PlayerSize.x;
					m_move.x = 0.0f;
				}
				else if (oldpos.x - PlayerSize.x >= pBlock->GetPos().x + pBlock->GetSize().x
					&& PlayerPos.x - PlayerSize.x <= pBlock->GetPos().x + pBlock->GetSize().x
					&& oldpos.y - PlayerSize.y < pBlock->GetPos().y + pBlock->GetSize().y
					&& oldpos.y > pBlock->GetPos().y - pBlock->GetSize().y)
				{//横との当たり判定(プレイヤーから見て左)
					PlayerPos.x = pBlock->GetPos().x + pBlock->GetSize().x + PlayerSize.x;
					m_move.x = 0.0f;

				}

				if (oldpos.y <= pBlock->GetPos().y - pBlock->GetSize().y
					&& PlayerPos.y >= pBlock->GetPos().y - pBlock->GetSize().y
					&& oldpos.x + PlayerSize.x > pBlock->GetPos().x - pBlock->GetSize().x
					&& oldpos.x - PlayerSize.x < pBlock->GetPos().x + pBlock->GetSize().x)
				{//床
					PlayerPos.y = pBlock->GetPos().y - pBlock->GetSize().y;
					m_move.y = 0.0f;
				}
				else if (oldpos.y - PlayerSize.y >= pBlock->GetPos().y + pBlock->GetSize().y
					&& PlayerPos.y - PlayerSize.y <= pBlock->GetPos().y + pBlock->GetSize().y
					&& oldpos.x + PlayerSize.x > pBlock->GetPos().x - pBlock->GetSize().x
					&& oldpos.x - PlayerSize.x < pBlock->GetPos().x + pBlock->GetSize().x)
				{//頭との当たり判定
					PlayerPos.y = pBlock->GetPos().y + pBlock->GetSize().y + PlayerSize.y;
					m_move.y = 0.0f;
				}
			}

		}
	}
	SetPos(PlayerPos);
}
