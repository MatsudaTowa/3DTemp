//=============================================
//
//3DTemplate[game.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAME_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GAME_H_
#include "main.h"
#include "scene.h"
class CGame:public CScene
{
public:
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};
#endif