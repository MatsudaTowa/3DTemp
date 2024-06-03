//=============================================
//
//3DTemplate[maneger.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MANAGER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MANAGER_H_
#include "main.h"
#include "input.h"
#include "camera.h"
#include "light.h"

class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();

	//�����_���[�擾
	static CRenderer*GetRenderer();
	//�L�[�{�[�h���擾
	static CInputKeyboard* GetKeyboard();
	//�J�����擾
	static CCamera* GetCamera();
	//���C�g�擾
	static CLight* GetLight();
private:
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pKeyboard;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
};

#endif