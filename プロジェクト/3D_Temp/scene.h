//=============================================
//
//3DTemplate[scene.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _SCENE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SCENE_H_
#include "main.h"
class CScene
{
public:
	//��ʂ̎�ނ̗�
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	}MODE;
	CScene();
	virtual ~CScene();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CScene* Create(MODE mode);
private:
	MODE m_Mode; //���݂̃��[�h
};
#endif