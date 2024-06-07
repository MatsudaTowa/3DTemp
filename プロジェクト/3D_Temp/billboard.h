//=============================================
//
//3DTemplate[billboard.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BILLBOARD_H_ //‚±‚ê‚ª’è‹`‚³‚ê‚Ä‚È‚¢‚Æ‚«

#define _BILLBOARD_H_
#include "main.h"
#include "object3D.h"

class CBillboard : public CObject3D
{
public:
	CBillboard(int nPriority = 5);
	~CBillboard()override;
	void Draw()override;
};


#endif