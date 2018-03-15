#ifndef _FONTSHADERCLASS_H_
#define _FONTSHADERCLASS_H_
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;
class FontShaderClass
{
private:
	struct ConstantBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct PixelBufferType
	{
		D3DXVECTOR4 pixelColor;
	};
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11Buffer *m_constantBuffer;
	ID3D11SamplerState *m_sampleState;
	ID3D11Buffer *m_pixelBuffer;
public:
	FontShaderClass();
	FontShaderClass(const FontShaderClass &other);
	~FontShaderClass();
	bool Initialize(ID3D11Device *device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR4 pixelColor);
private:
	bool InitializeShader(ID3D11Device *device, HWND hwnd, WCHAR *vsShaderFile, WCHAR *psShaderFile);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob *errrorMessage, HWND hwnd, WCHAR *shaderFileName);
	bool SetShaderParameters(ID3D11DeviceContext *deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR4 pixelColor);
	void RenderShader(ID3D11DeviceContext *deviceContext, int indexCount);
};
#endif

