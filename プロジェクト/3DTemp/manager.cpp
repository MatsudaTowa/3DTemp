//=============================================
//
//2DTemplate[manager.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "player.h"
#include "bg.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "enemy.h"
#include "block.h"
//レンダラー設定
CRenderer*CManager::m_pRenderer = nullptr;
CInputKeyboard*CManager::m_pKeyboard = nullptr;

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
	
	//読み込み
	CBullet::Load();

	CExplosion::Load();

	CEffect::Load();

	CEnemy::Load();

	CBlock::Load();

	//背景生成
	CBg* pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0));

	//プレイヤー生成
	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f, 0.0f),D3DXVECTOR2(50.0f, 100.0f));

	CEnemy* pEnemy = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f, 0.0f), 
									D3DXVECTOR3(2.0f, 2.0f, 0.0f),D3DXVECTOR2(70.0f, 100.0f),1);

	CBlock* pBlock = CBlock::Create(CBlock::BLOCKTYPE_FIELD,D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT,0.0f),
									D3DXVECTOR2(SCREEN_WIDTH * 0.5f,100.0f),3,false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_BREAK, D3DXVECTOR3(300.0f, 300.0f, 0.0f),
							D3DXVECTOR2(100.0f, 100.0f), 1, true);

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

CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}
