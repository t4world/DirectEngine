#ifndef _LIGHTSHADERCLASS_H_
#define _LIGHTSHADERCLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

class LightShaderClass
{
public:
	LightShaderClass();
	LightShaderClass(const LightShaderClass &other);
	~LightShaderClass();
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
		float specularPower;
		D3DXVECTOR4 specularColor;
	};

	struct CameraBufferType
	{
		D3DXVECTOR3 cameraPosition;
		float padding;
	};

public:
	bool Initialize(ID3D11Device *device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR3 lightDirection,D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor,
		D3DXVECTOR3 cameraPosition,D3DXVECTOR4 specularColor,float specularPower);
private:
	bool InitializeShader(ID3D11Device *device, HWND hwnd, WCHAR *vsFile, WCHAR *psFile);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob *errorMesage, HWND hwnd, WCHAR *shaderFileName);
	bool SetShaderParamters(ID3D11DeviceContext *deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor,
		D3DXVECTOR3 cameraPosition,D3DXVECTOR4 specularColor,float specularPower);
	void RenderShader(ID3D11DeviceContext *deviceContext, int indexCount);
private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader  *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11SamplerState *m_sampleState;
	ID3D11Buffer *m_matrixBuffer;
	ID3D11Buffer *m_lightBuffer;
	ID3D11Buffer *m_cameraBuffer;
};
#endif // !_LIGHTSHADERCLASS_H_

