//=============================================
//
//3DTemplate[camera.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "player.h"

//通常の移動速度
const float CCamera::DEFAULT_MOVE = 1.0f;

//通常の移動速度
const float CCamera::DAMPING_COEFFICIENT = 0.2f;

//通常状態のYの距離
const float CCamera::DEFAULT_LENGTH_Y = 200.0f;

//通常状態のZの距離
const float CCamera::DEFAULT_LENGTH_Z = 500.0f;

//バードビュー時のYの距離
const float CCamera::BIRDVIEW_LENGTH_Y = 300.0f;

//サイドビュー時のXの距離
const float CCamera::SIDEVIEW_LENGTH_X = 200.0f;

//サイドビュー時のYの距離
const float CCamera::SIDEVIEW_LENGTH_Y = 50.0f;

//サイドビュー時のZの距離
const float CCamera::SIDEVIEW_LENGTH_Z = 200.0f;

//=============================================
//コンストラクタ
//=============================================
CCamera::CCamera()
{
}

//=============================================
//デストラクタ
//=============================================
CCamera::~CCamera()
{
}

//=============================================
//初期化
//=============================================
HRESULT CCamera::Init()
{

	m_type = TYPE_BIRDVIEW;
	
	m_posV = D3DXVECTOR3(0.0f, 200.0f, -180.0f); //視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //注視

	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //上方向ベクトル

	m_moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //視点移動量
	m_moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //注視点移動量

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //角度
	m_rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //回転量

	D3DXVECTOR3 vecCamera = m_posR - m_posV;
	m_fLength = sqrtf(vecCamera.y * vecCamera.y + vecCamera.z * vecCamera.z);

	//対角線の角度を算出する
	m_fAngle = atan2f(vecCamera.y, vecCamera.z);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CCamera::Uninit()
{
}

//=============================================
//更新
//=============================================
void CCamera::Update()
{
	//キーボード情報取得
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_F1))
	{
		m_type = TYPE_BIRDVIEW;
	}
	else if (pKeyboard->GetTrigger(DIK_F2))
	{
		m_type = TYPE_SIDEVIEW;
	}
	else if (pKeyboard->GetTrigger(DIK_F3))
	{
		m_type = TYPE_DEBUG;
	}


	switch (m_type)
	{
	case TYPE_BIRDVIEW:
		BirdViewCamera();
		break;
	case TYPE_SIDEVIEW:
		SideViewCamera();
		break;
	case TYPE_DEBUG:
		CameraTurn();
		CameraMove();
		break;
	default:
		break;
	}


	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
		//		m_rot.y -= D3DX_PI* 2.0f;
	}

	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
		//		m_rot.y -= D3DX_PI* 2.0f;
	}

	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	m_posV += m_moveV;
	m_posR += m_moveR;

	//移動量を更新(減速）
	m_moveV.x += (0.0f - m_moveV.x) * DAMPING_COEFFICIENT;
	m_moveV.y += (0.0f - m_moveV.y) * DAMPING_COEFFICIENT;
	m_moveV.z += (0.0f - m_moveV.z) * DAMPING_COEFFICIENT;

	m_moveR.x += (0.0f - m_moveR.x) * DAMPING_COEFFICIENT;
	m_moveR.y += (0.0f - m_moveR.y) * DAMPING_COEFFICIENT;
	m_moveR.z += (0.0f - m_moveR.z) * DAMPING_COEFFICIENT;
}

//=============================================
//カメラ設定
//=============================================
void CCamera::SetCamera()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1800.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 posV = m_posV;
	D3DXVECTOR3 posR = m_posR;

	posV.y += -15.0f;
	posR.y += 0.0f;

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,
		&posR,
		&m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=============================================
//カメラ移動量
//=============================================
void CCamera::CameraMove()
{
	//キーボード情報取得
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_J) == true)
	{
		m_moveV.x -= sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x -= sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z -= cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z -= cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

	}

	if (pKeyboard->GetPress(DIK_L) == true)
	{
		m_moveV.x += sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x += sinf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z += cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z += cosf(D3DX_PI / 2 + m_rot.y) * DEFAULT_MOVE;

	}


	if (pKeyboard->GetPress(DIK_I) == true)
	{
		m_moveV.x -= sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x -= sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z -= cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z -= cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

	}

	if (pKeyboard->GetPress(DIK_K) == true)
	{
		m_moveV.x += sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.x += sinf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

		m_moveV.z += cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;
		m_moveR.z += cosf(D3DX_PI + m_rot.y) * DEFAULT_MOVE;

	}

}

//=============================================
//カメラ回転量
//=============================================
void CCamera::CameraTurn()
{
	//キーボード情報取得
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	if (pKeyboard->GetPress(DIK_Q) == true)
	{
		m_rot.y -= 0.02f;

		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;

	}

	if (pKeyboard->GetPress(DIK_E) == true)
	{
		m_rot.y += 0.02f;
		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fLength;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fLength;
	}

	if (pKeyboard->GetPress(DIK_U) == true)
	{
		m_rot.y -= 0.02f;

		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;

		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
	}

	if (pKeyboard->GetPress(DIK_O) == true)
	{
		m_rot.y += 0.02f;

		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;

		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
	}
}

//=============================================
//バードビュー処理
//=============================================
void CCamera::BirdViewCamera()
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)pObj;
				m_posR =pPlayer->GetPos();
				m_posV.x = m_posR.x - sinf(m_rot.y);
				m_posV.y = BIRDVIEW_LENGTH_Y;
				m_posV.z = m_posR.z - cosf(m_rot.y);
			}
		}

	}
}



//=============================================
//サイドビュー処理
//=============================================
void CCamera::SideViewCamera()
{
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)pObj;
				m_posR.x = pPlayer->GetPos().x;
				m_posR.y = 20.0f;
				m_posR.z = pPlayer->GetPos().z;
				m_posV.x = m_posR.x - sinf(m_rot.y)* SIDEVIEW_LENGTH_X;
				m_posV.y = SIDEVIEW_LENGTH_Y;
				m_posV.z = m_posR.z - cosf(m_rot.y) * SIDEVIEW_LENGTH_Z;
			}
		}

	}
}
