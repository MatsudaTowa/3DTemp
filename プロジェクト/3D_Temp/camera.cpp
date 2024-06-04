//=============================================
//
//3DTemplate[camera.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"

//通常の移動速度
const float CCamera::DEFAULT_MOVE = 1.0f;

//通常の移動速度
const float CCamera::DAMPING_COEFFICIENT = 0.2f;

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
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f); //視点
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

	CameraMove();

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
		//		g_Camera.rot.y -= D3DX_PI* 2.0f;
	}

	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
		//		g_Camera.rot.y -= D3DX_PI* 2.0f;
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
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_I))
	{
		vecDirection.z += 1.0f;
	}
	if (pKeyboard->GetPress(DIK_K))
	{
		vecDirection.z -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_J))
	{
		vecDirection.x -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_L))
	{
		vecDirection.x += 1.0f;
	}
	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		m_moveV.x = 0.0f;
		m_moveV.z = 0.0f;
		m_moveR.x = 0.0f;
		m_moveR.z = 0.0f;
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		m_moveV.x += sinf(rotMoveY) * DEFAULT_MOVE;
		m_moveV.z += cosf(rotMoveY) * DEFAULT_MOVE;

		m_moveR.x += sinf(rotMoveY) * DEFAULT_MOVE;
		m_moveR.z += cosf(rotMoveY) * DEFAULT_MOVE;

		m_rot.y = rotMoveY + D3DX_PI;

		//if (g_Player.rot.y <= -D3DX_PI)
		//{
		//	g_Player.rot.y = D3DX_PI;
		//}

	}
	//if (GetKeyboardPress(DIK_J) == true)
	//{
	//	g_Camera.moveV.x -= sinf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;
	//	g_Camera.moveR.x -= sinf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;

	//	g_Camera.moveV.z -= cosf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;
	//	g_Camera.moveR.z -= cosf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;

	//}

	//if (GetKeyboardPress(DIK_L) == true)
	//{
	//	g_Camera.moveV.x += sinf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;
	//	g_Camera.moveR.x += sinf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;

	//	g_Camera.moveV.z += cosf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;
	//	g_Camera.moveR.z += cosf(D3DX_PI / 2 + g_Camera.rot.y) * CAMERA_MOVE;

	//}


	//if (GetKeyboardPress(DIK_I) == true)
	//{
	//	g_Camera.moveV.x -= sinf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;
	//	g_Camera.moveR.x -= sinf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;

	//	g_Camera.moveV.z -= cosf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;
	//	g_Camera.moveR.z -= cosf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;

	//}

	//if (GetKeyboardPress(DIK_K) == true)
	//{
	//	g_Camera.moveV.x += sinf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;
	//	g_Camera.moveR.x += sinf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;

	//	g_Camera.moveV.z += cosf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;
	//	g_Camera.moveR.z += cosf(D3DX_PI + g_Camera.rot.y) * CAMERA_MOVE;
	//}
}

//=============================================
//カメラ回転量
//=============================================
void CCamera::CameraTurn()
{
}
