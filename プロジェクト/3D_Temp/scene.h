//=============================================
//
//3DTemplate[scene.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _SCENE_H_ //‚±‚ê‚ª’è‹`‚³‚ê‚Ä‚È‚¢‚Æ‚«

#define _SCENE_H_
#include "main.h"
class CScene
{
public:
	//‰æ–Ê‚Ìí—Ş‚Ì—ñ‹“
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
	MODE m_Mode; //Œ»İ‚Ìƒ‚[ƒh
};
#endif