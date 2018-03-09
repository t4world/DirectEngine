#ifndef _BITMAPCLASS_H_
#define _BITMAPCLASS_H_

#include<d3d11.h>
#include<d3dx10math.h>
#include "textureclass.h"

class BitmapClass
{
public:
	BitmapClass();
	BitmapClass(const BitmapClass &other);
	~BitmapClass();
private:
	struct VertexType 
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};
};
#endif // !_BITMAPCLASS_H_
