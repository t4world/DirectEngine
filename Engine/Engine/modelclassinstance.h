#ifndef _MODELCLASSINSTANCE_H_
#define _MODELCLASSINSTANCE_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include "textureclass.h"
#include <fstream>
class ModelClassInstance
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};
	struct InstanceType
	{
		D3DXVECTOR3 position;
	};
public:
	ModelClassInstance();
	ModelClassInstance(const ModelClassInstance&);
	~ModelClassInstance();

	bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetVertexCount();
	int GetInstanceCount();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTextures(ID3D11Device *device, WCHAR *fileName0);
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer;
	ID3D11Buffer *m_instanceBuffer;
	int m_vertexCount;
	int m_instanceCount;
	TextureClass *m_Texture;
};
#endif

