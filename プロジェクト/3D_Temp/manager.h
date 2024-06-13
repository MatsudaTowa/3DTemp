//=============================================
//
//3DTemplate[maneger.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MANAGER_H_ //これが定義されてないとき

#define _MANAGER_H_
#include "main.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "texture.h"

class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();

	//レンダラー取得
	static CRenderer*GetRenderer();
	//キーボード情報取得
	static CInputKeyboard* GetKeyboard();
	//マウス情報取得
	static CInputMouse* GetMouse();
	//カメラ取得
	static CCamera* GetCamera();
	//ライト取得
	static CLight* GetLight();
	//テクスチャ取得
	static CTexture* GetTexture();
private:
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pKeyboard;
	static CInputMouse* m_pMouse;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
	static CTexture* m_pTexture;
};

#endif