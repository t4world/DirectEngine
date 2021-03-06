#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;
class Refractionshaderclass
{
public:
	Refractionshaderclass();
	Refractionshaderclass(const Refractionshaderclass &other);
	~Refractionshaderclass();
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct LightBufferType
	{
		D3DXVECTOR4 ambientColor;
		D3DXVECTOR4 diffuseColor;
		D3DXVECTOR3 lightDirection;
		float padding;
	};

	struct ClipPlaneBufferType
	{
		D3DXVECTOR4 clipPlane;
	};

public:
	bool Initialize(ID3D11Device *device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor,
		 D3DXVECTOR4 clipPlane);
private:
	bool InitializeShader(ID3D11Device *device, HWND hwnd, WCHAR *vsFile, WCHAR *psFile);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob *errorMesage, HWND hwnd, WCHAR *shaderFileName);
	bool SetShaderParamters(ID3D11DeviceContext *deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor,
		D3DXVECTOR4 clipPlane);
	void RenderShader(ID3D11DeviceContext *deviceContext, int indexCount);
private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader  *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11SamplerState *m_sampleState;
	ID3D11Buffer *m_matrixBuffer;
	ID3D11Buffer *m_lightBuffer;
	ID3D11Buffer *m_clipPlaneBuffer;

};

