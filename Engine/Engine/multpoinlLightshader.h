#ifndef _MULTPOINTLIGHTSSHADER_H_
#define _MULTPOINTLIGHTSSHADER_H_

const int NUM_LIGHTS = 4;

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;
class MultPointLightsShader
{
public:
	MultPointLightsShader();
	MultPointLightsShader(const MultPointLightsShader &other);
	~MultPointLightsShader();
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct LightColorBufferType
	{
		D3DXVECTOR4 diffuseColor[NUM_LIGHTS];
	};

	struct LightPositionBufferType
	{
		D3DXVECTOR4 lightPosition[NUM_LIGHTS];
	};

public:
	bool Initialize(ID3D11Device *device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR4 diffuseColor[], D3DXVECTOR4 lightPostions[]);
private:
	bool InitializeShader(ID3D11Device *device, HWND hwnd, WCHAR *vsFile, WCHAR *psFile);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob *errorMesage, HWND hwnd, WCHAR *shaderFileName);
	bool SetShaderParamters(ID3D11DeviceContext *deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture,D3DXVECTOR4 diffuseColor[], D3DXVECTOR4 lightPostions[]);
	void RenderShader(ID3D11DeviceContext *deviceContext, int indexCount);
private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader  *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11SamplerState *m_sampleState;
	ID3D11Buffer *m_matrixBuffer;
	ID3D11Buffer *m_lightColorBuffer;
	ID3D11Buffer *m_lightPositionBuffer;
};

#endif

