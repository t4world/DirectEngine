#ifndef _DEBUGWINDOWCLASS_H_
#define  _DEBUGWINDOWCLASS_H_
#include <d3d11.h>
#include <d3dx10math.h>
class DebugWindowClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};
public:
	DebugWindowClass();
	DebugWindowClass(const DebugWindowClass &other);
	~DebugWindowClass();

	bool Initialize(ID3D11Device *device, int screenWidth, int screenHeight, int bitmapWidth, int bitmapHeight);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext,int positionX, int positionY);
	int GetIndexCount();
private:
	bool InitializeBuffers(ID3D11Device *device);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext *deviceContext, int positionX, int positionY);
	void RenderBuffers(ID3D11DeviceContext *deviceContext);
private:
	ID3D11Buffer *m_vertexBuffer;
	ID3D11Buffer *m_indexBuffers;
	int m_vertexCount;
	int m_indexCount;
	int m_screenWidth;
	int m_screenHeight;
	int m_bitmapWidth;
	int m_bitmapHeight;
	int m_prePositionX;
	int m_prePositionY;
};
#endif

