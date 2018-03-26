#include "texturearrayclass.h"


Texturearrayclass::Texturearrayclass()
{
	m_texture[0] = 0;
	m_texture[1] = 0;
}

Texturearrayclass::Texturearrayclass(const Texturearrayclass &other)
{

}


Texturearrayclass::~Texturearrayclass()
{
}

bool Texturearrayclass::Initialize(ID3D11Device *device, WCHAR *textureFileName_0, WCHAR *textureFileName_1,WCHAR *textureFileName_2)
{
	HRESULT result;
	result = D3DX11CreateShaderResourceViewFromFile(device, textureFileName_0, NULL, NULL, &m_texture[0], NULL);
	if (FAILED(result))
	{
		return false;
	}
	result = D3DX11CreateShaderResourceViewFromFile(device, textureFileName_1, NULL, NULL, &m_texture[1], NULL);
	if (FAILED(result))
	{
		return false;
	}
	result = D3DX11CreateShaderResourceViewFromFile(device, textureFileName_2, NULL, NULL, &m_texture[2], NULL);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void Texturearrayclass::Shutdown()
{
	if (m_texture[0])
	{
		m_texture[0]->Release();
		m_texture[0] = 0;
	}
	if (m_texture[1])
	{
		m_texture[1]->Release();
		m_texture[1] = 0;
	}
	if (m_texture[2])
	{
		m_texture[2]->Release();
		m_texture[2] = 0;
	}
}

ID3D11ShaderResourceView ** Texturearrayclass::GetTextureArray()
{
	return m_texture;
}
