//=============================================
//
//3DTemplate[bg.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BG_H_ //これが定義されてないとき

#define _BG_H_
#include "main.h"
#include "object2D.h"

//レンダラークラス
class CBg : public CObject2D
{
public:
	CBg(int nPriority = 1);
	~CBg()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBg* Create(D3DXVECTOR3 pos);
};
#endif