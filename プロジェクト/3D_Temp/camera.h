//=============================================
//
//3DTemplate[camera.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CAMERA_H_ //これが定義されてないとき

#define _CAMERA_H_
#include "main.h"
#include "input.h"
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();
private:
	static const float DEFAULT_MOVE; //通常時の移動
	static const float DAMPING_COEFFICIENT; //移動抵抗
	static const float DEFAULT_LENGTH_Y; //通常状態のYの距離
	static const float DEFAULT_LENGTH_Z; //通常状態のZの距離

	void CameraMove(); //カメラ移動処理

	void CameraTurn(); //カメラ回転処理

	D3DXVECTOR3 m_posV; //視点
	D3DXVECTOR3 m_posR; //注視点

	D3DXVECTOR3 m_moveV; //視点移動量
	D3DXVECTOR3 m_moveR; //注視点移動量

	D3DXVECTOR3 m_vecU; //上方向ベクトル

	D3DXVECTOR3 m_rot; //方向
	D3DXVECTOR3 m_rotmove; //回転量

	float m_fLength; //対象との距離
	float m_fAngle; //対象との対角線の角度

	D3DXMATRIX m_mtxProjection; //プロジェクション
	D3DXMATRIX m_mtxView; //ビュー行列
};
#endif
