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
	static const int BG_PRIORITY = 1;  //描画順
	CBg(int nPriority = BG_PRIORITY);
	~CBg()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBg* Create(D3DXVECTOR3 pos);
};
#endif