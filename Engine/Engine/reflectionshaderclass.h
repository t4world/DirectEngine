#ifndef _REFLECTIONSHADERCLASS_H_
#define _REFLECTIONSHADERCLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;
class ReflectionShaderClass
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct ReflectionBufferType
	{
		D3DXMATRIX reflectionMatrix;
	};
public:
	ReflectionShaderClass();
	ReflectionShaderClass(const ReflectionShaderClass &other);
	~ReflectionShaderClass();

	bool Initialize(ID3D11Device *device, HWND hWnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView *reflectTexture, D3DXMATRIX reflectMatrix);
private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);
	bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView *reflectTexture, D3DXMATRIX reflectMatrix);
	void RenderShader(ID3D11DeviceContext*, int);
private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11Buffer *m_matrixBuffer;
	ID3D11SamplerState *m_sampleState;
	ID3D11Buffer *m_reflectionBuffer;
};
#endif