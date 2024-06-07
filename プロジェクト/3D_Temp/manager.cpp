//=============================================
//
//3DTemplate[manager.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "bg.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "enemy.h"
#include "block.h"
#include "field.h"

//レンダラー設定
CRenderer*CManager::m_pRenderer = nullptr;

//キーボード設定
CInputKeyboard*CManager::m_pKeyboard = nullptr;

//カメラ設定
CCamera*CManager::m_pCamera = nullptr;

//ライト設定
CLight*CManager::m_pLight = nullptr;

//=============================================
//コンストラクタ
//=============================================
CManager::CManager()
{
}

//=============================================
//デストラクタ
//=============================================
CManager::~CManager()
{
}

//=============================================
//初期化
//=============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{

	//生成＆初期化
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer();
		m_pRenderer->Init(hWnd,bWindow);
	}
	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CInputKeyboard();

		//キーボードの初期化処理
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//カメラ生成
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera();
		m_pCamera->Init();
	}

	//ライト生成
	if (m_pLight == nullptr)
	{
		m_pLight = new CLight();
		m_pLight->Init();
	}
	
	//読み込み
	CBullet::Load();

	CExplosion::Load();

	CEffect::Load();

	CEnemy::Load();

	CBlock::Load();

	CField::Load();

	CPlayer::Load();

	////背景生成
	//CBg* pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0));

	////プレイヤー生成
	//CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f, 0.0f),D3DXVECTOR2(50.0f, 100.0f));

	//CEnemy* pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f, 0.0f), 
	//								D3DXVECTOR3(2.0f, 2.0f, 0.0f),D3DXVECTOR2(70.0f, 100.0f),1);

	CBlock* pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT,D3DXVECTOR3(0.0,0.0f,0.0f),
									D3DXVECTOR3(0.0f, 0.0f, 0.0f),3,false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(10.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);
	
	CField*pField = CField::Create(D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(100.0f,0.0f,100.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(50.0f,0.5f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CManager::Uninit()
{
	//破棄
	CBullet::UnLoad();

	CExplosion::UnLoad();

	CEffect::UnLoad();

	CEnemy::UnLoad();

	CBlock::UnLoad();

	CField::UnLoad();

	CPlayer::UnLoad();

	CObject::ReleaseAll();
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	
	//キーボードの終了処理
	m_pKeyboard->Uninit();
}

//=============================================
//更新処理
//=============================================
void CManager::Update()
{
	//更新処理
	m_pRenderer->Update();
	m_pCamera->Update();
	m_pKeyboard->Update();
	CObject::UpdateAll();
}

//=============================================
//描画処理
//=============================================
void CManager::Draw()
{
	//描画処理
	m_pRenderer->Draw();

	//g_pRenderer->DrawFPS(nCntFPS);
}

//=============================================
//レンダラー取得
//=============================================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

//=============================================
//キーボード情報取得
//=============================================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//=============================================
//カメラ取得
//=============================================
CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

//=============================================
//ライト取得
//=============================================
CLight* CManager::GetLight()
{
	return m_pLight;
}
