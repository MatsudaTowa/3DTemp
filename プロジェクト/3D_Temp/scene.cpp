//=============================================
//
//3DTemplate[scene.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "manager.h"
//=============================================
//コンストラクタ
//=============================================
CScene::CScene()
{
}

//=============================================
//デストラクタ
//=============================================
CScene::~CScene()
{
}

//=============================================
//初期化
//=============================================
HRESULT CScene::Init()
{

    return E_NOTIMPL;
}

//=============================================
//終了
//=============================================
void CScene::Uninit()
{
}

//=============================================
//更新
//=============================================
void CScene::Update()
{
}

//=============================================
//描画
//=============================================
void CScene::Draw()
{
}

//=============================================
//生成
//=============================================
CScene* CScene::Create(MODE mode)
{
    CScene* pScene = new CScene;

    if (pScene != nullptr)
    {
       pScene->m_Mode = mode;

       switch (mode)
       {
       case MODE_TITLE:
            delete pScene;
            pScene = new CTitle;
             break;
       case MODE_GAME:
           delete pScene;
           pScene = new CGame;
           break;
       case MODE_RESULT:
           delete pScene;
           pScene = new CResult;
           break;
       default:
           break;
       }
       
       //今のシーンの初期化
       pScene->Init();
    }

    return pScene;
}

