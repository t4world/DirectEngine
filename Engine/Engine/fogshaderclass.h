#ifndef _FOGSHADERCLASS_H_
#define _FOGSHADERCLASS_H_
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;
class FogShaderClass
{
private:
	struct ConstantBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
		D3DXVECTOR4 fogColor;
	};

	struct FogBufferType
	{
		float fogStart;
		float fogEnd;
		float padding0;
		float padding1;
	};
public:
	FogShaderClass();
	FogShaderClass(const FogShaderClass &other);
	~FogShaderClass();

	bool Initialize(ID3D11Device *device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR4 fogColor, float fogStart, float fogEnd);
private:
	bool InitializeShader(ID3D11Device *device, HWND hwnd, WCHAR *vsShaderFile, WCHAR *psShaderFile);
	void ShutdownShader();
	bool RenderShader(ID3D11DeviceContext *deviceContext, int indexCount);
	bool SetShaderParameter(ID3D11DeviceContext *deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR4 fogColor, float fogStart, float fogEnd);
	void OutputShaderErrorMessage(ID3D10Blob *errorMessage, HWND hwnd, WCHAR *shaderFileName);
private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11Buffer *m_ConstantBuffer;
	ID3D11Buffer *m_FogBuffer;
	ID3D11SamplerState *m_SamplerState;
};
#endif

