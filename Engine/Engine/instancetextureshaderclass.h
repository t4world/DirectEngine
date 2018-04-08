#ifndef _INSTANCETEXTURESHADERCLASS_H_
#define _INSTANCETEXTURESHADERCLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

class InstanceTextureShaderClass
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};
public:
	InstanceTextureShaderClass();
	InstanceTextureShaderClass(const InstanceTextureShaderClass &other);
	~InstanceTextureShaderClass();

	bool Initialize(ID3D11Device *device, HWND hWnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int vertexCount, int instanceCount, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection, ID3D11ShaderResourceView* texture);
private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);
	bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);
	void RenderShader(ID3D11DeviceContext* deviceContext, int vertexCount, int instanceCount);
private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11Buffer *m_matrixBuffer;
	ID3D11SamplerState *m_sampleState;
};
#endif // !_InstanceTextureShaderClass_H_

