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
//�R���X�g���N�^
//=============================================
CScene::CScene()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CScene::~CScene()
{
}

//=============================================
//������
//=============================================
HRESULT CScene::Init()
{

    return E_NOTIMPL;
}

//=============================================
//�I��
//=============================================
void CScene::Uninit()
{
}

//=============================================
//�X�V
//=============================================
void CScene::Update()
{
}

//=============================================
//�`��
//=============================================
void CScene::Draw()
{
}

//=============================================
//����
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
       
       //���̃V�[���̏�����
       pScene->Init();
    }

    return pScene;
}

