#ifndef _RENDERTTEXTURECLASS_H_
#define _RENDERTTEXTURECLASS_H_
#include <d3d11.h>
class RenderTextureClass
{
public:
	RenderTextureClass();
	RenderTextureClass(const RenderTextureClass &other);
	~RenderTextureClass();

	bool Initialize(ID3D11Device *device, int textureWith, int textureHeight);
	void Shutdown();
	void SetRenderTarget(ID3D11DeviceContext *deviceContext, ID3D11DepthStencilView *stencilView);
	void ClearRenderTarget(ID3D11DeviceContext *deviceContext, ID3D11DepthStencilView *stencilView, float red, float green, float blue, float alpha);
	ID3D11ShaderResourceView *GetShaderResourceView();
private:
	ID3D11Texture2D * m_renderTargetTexture;
	ID3D11RenderTargetView *m_renderTargetView;
	ID3D11ShaderResourceView *m_shaderResourceView;
};
#endif

