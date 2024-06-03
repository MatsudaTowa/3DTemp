//=============================================
//
//2DTemplate[maneger.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MANAGER_H_ //‚±‚ê‚ª’è‹`‚³‚ê‚Ä‚È‚¢‚Æ‚«

#define _MANAGER_H_
#include "main.h"
#include "input.h"

class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();

	static CRenderer*GetRenderer();
	static CInputKeyboard* GetKeyboard();

private:
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pKeyboard;

};

#endif