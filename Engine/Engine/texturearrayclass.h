#ifndef _TEXTUREARRAYCLASS_H_
#define _TEXTUREARRAYCLASS_H_

#include <d3d11.h>
#include <d3dx11tex.h>
class Texturearrayclass
{
public:
	Texturearrayclass();
	Texturearrayclass(const Texturearrayclass &other);
	~Texturearrayclass();

	bool Initialize(ID3D11Device *device, WCHAR *textureFileName_0, WCHAR *textureFileName_1, WCHAR *textureFileName_2);
	void Shutdown();
	ID3D11ShaderResourceView** GetTextureArray();
private:
	ID3D11ShaderResourceView* m_texture[3];
};
#endif

