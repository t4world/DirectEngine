#include "rendertextureclass.h"



RenderTextureClass::RenderTextureClass()
{
	m_renderTargetTexture = 0;
	m_renderTargetView = 0;
	m_shaderResourceView = 0;
}

RenderTextureClass::RenderTextureClass(const RenderTextureClass & other)
{
}


RenderTextureClass::~RenderTextureClass()
{
}

bool RenderTextureClass::Initialize(ID3D11Device * device, int textureWith, int textureHeight)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT result;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = textureWith;
	textureDesc.Height = textureHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	//Create the render target texture;
	result = device->CreateTexture2D(&textureDesc, NULL, &m_renderTargetTexture);
	if (FAILED(result))
	{
		return false;
	}
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;
	result = device->CreateRenderTargetView(m_renderTargetTexture, &renderTargetViewDesc, &m_renderTargetView);
	if (FAILED(result))
	{
		return false;
	}
	shaderResourceViewDesc.Format = textureDesc.Format;
	return true;
}

void RenderTextureClass::Shutdown()
{
}

void RenderTextureClass::SetRenderTarget(ID3D11DeviceContext * deviceContext, ID3D11DepthStencilView * stencilView)
{
}

void RenderTextureClass::ClearRenderTarget(ID3D11DeviceContext * deviceContext, ID3D11DepthStencilView * stencilView, float red, float green, float blue, float alpha)
{
}

ID3D11ShaderResourceView * RenderTextureClass::GetShaderResourceView()
{
	return m_shaderResourceView;
}
