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

//通常の移動速度
const float CPlayer::DEFAULT_MOVE = 1.0f;
//通常の移動速度
const float CPlayer::DAMPING_COEFFICIENT = 0.2f;

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CPlayer::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer::m_pMesh = nullptr;

DWORD CPlayer::m_dwNumMat = 0;
//=============================================
//コンストラクタ
//=============================================
CPlayer::CPlayer(int nPriority):CObjectX(nPriority)
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
	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\PlayerAnimation.png",
	//	&pTex);

	//CObjectX::BindTexture(pTex);

	CObjectX::BindXFile(m_pBuffMat, m_dwNumMat, m_pMesh);

	m_bSize = false;

	//移動量初期化
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	return S_OK;
}


//=============================================
//終了
//=============================================
void CPlayer::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CPlayer::Update()
{
	PlayerMove();

	D3DXVECTOR3 pos = GetPos();

	//移動量を更新(減速）
	m_move *= 1.0f - DAMPING_COEFFICIENT;

	m_oldpos = pos;

	pos += m_move;

	//座標を更新
	SetPos(pos);
	
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
	//if (pKeyboard->GetTrigger(DIK_SPACE))
	//{
	//	//弾生成
	//	CBullet* CBullet = CBullet::Create(pos,D3DXVECTOR3(10.0f,0.0f,0.0f),D3DXVECTOR2(15.0f,15.0f),60);
	//}

}

//=============================================
//描画
//=============================================
void CPlayer::Draw()
{
	CObjectX::Draw();
}

//=============================================
//生成
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(pos); //pos設定
	pPlayer->SetRot(rot); //pos設定
	pPlayer->SetType(OBJECT_TYPE_PLAYER); //タイプ設定
	pPlayer->Init();
	
	return pPlayer;
}

//=============================================
//ロード
//=============================================
HRESULT CPlayer::Load()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	//if (m_pTextureTemp == nullptr)
	//{
	//	//テクスチャの読み込み
	//	D3DXCreateTextureFromFile(pDevice,
	//		"data\\TEXTURE\\download_image_1714032505054.png",
	//		&m_pTextureTemp);
	//}
	if (m_pBuffMat == nullptr && m_pMesh == nullptr)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\face.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);
	}
	return S_OK;
}

//=============================================
//anロード
//=============================================
HRESULT CPlayer::UnLoad()
{
	if (m_pTextureTemp != nullptr)
	{

		m_pTextureTemp->Release();
		m_pTextureTemp = nullptr;
	}
	if (m_pBuffMat != nullptr)
	{

		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
	if (m_pMesh != nullptr)
	{

		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	return S_OK;
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
		vecDirection.z += 1.0f;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		vecDirection.z -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		vecDirection.x -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += 1.0f;
	}

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		m_move.x = 0.0f;
		m_move.y = 0.0f;
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		//オブジェクト2Dからrotを取得
		D3DXVECTOR3 rot = GetRot();

		m_move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		m_move.z += cosf(rotMoveY) * DEFAULT_MOVE;
		//rot.x = rotMoveY + D3DX_PI;
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

}

//=============================================
//当たり判定
//=============================================
void CPlayer::HitBlock(D3DXVECTOR3 oldpos)
{
	
}
