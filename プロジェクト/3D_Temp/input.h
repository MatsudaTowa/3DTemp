//=============================================
//
//3DTemplate[input.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _INPUT_H_ //��`����ĂȂ�������
#define _INPUT_H_ //�Q��C���N���[�h�h�~
#include "main.h"

//�C���v�b�g�N���X
class CInput
{
public:
	CInput();
	~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;//�[�����Ƃ�
protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//�L�[�{�[�h�N���X
class CInputKeyboard:public CInput
{
public:
	static const int NUM_KEY_MAX = 256; //�L�[�{�[�h�̃L�[��
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;//�[�����Ƃ�
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
private:
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //�L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyState[NUM_KEY_MAX]; //�L�[�{�[�h�̃v���X���
};

//�}�E�X�N���X
class CInputMouse :public CInput
{
public:
	static const int NUM_MOUSE_MAX = 3; //�}�E�X�̃L�[��
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;//�[�����Ƃ�
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	D3DXVECTOR3 GetMouseMove(void);
private:
	DIMOUSESTATE m_KeyStateTrigger; //�}�E�X�̃g���K�[���
	DIMOUSESTATE m_KeyState; //�}�E�X�̃v���X���
	DIMOUSESTATE m_zdiMouseMove; //�}�E�X���[�u
	D3DXVECTOR3 m_MousePos;
	D3DXVECTOR3 m_MouseMove;
};
#endif // _INPUT_H_ //��`����ĂȂ�������