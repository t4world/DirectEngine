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
public:
	bool Initialize(ID3D11Device *device, int screenWidth, int screenHeight, WCHAR *textureFileName, int bitmapWidth, int bitmapHeight);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int posX, int posY);
	int GetIndexCount();
	ID3D11ShaderResourceView *GetTexture();
private:
	bool InitializeBuffers(ID3D11Device *device);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext *deviceContext,int positionX,int positionY);
	void RenderBuffers(ID3D11DeviceContext *deviceContext);
	bool LoadTexture(ID3D11Device *device, WCHAR *textFileName);
	void ReleaseTexture();
private:
	ID3D11Buffer *m_vertexBuffer;
	ID3D11Buffer *m_indexBuffer;
	int m_vertexCount;
	int m_indexCount;
	TextureClass *m_Texture;
	int m_screenWidth;
	int m_screenHeight;
	int m_bitmapWidth;
	int m_bitmapHeight;
	int m_previousPosX;
	int m_previousPosY;
};
#endif // !_BITMAPCLASS_H_
