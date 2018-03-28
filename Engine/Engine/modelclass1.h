////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS1_H_
#define _MODELCLASS1_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include "textureclass.h"
#include <fstream>
using namespace std;



////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass1
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		//D3DXVECTOR4 color;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
		//D3DXVECTOR3 tangent;
		//D3DXVECTOR3 binormal;
	};

	struct ModelType
	{
		float x;
		float y;
		float z;
		float tu;
		float tv;
		float nx;
		float ny;
		float nz;
	};



public:
	ModelClass1();
	ModelClass1(const ModelClass1&);
	~ModelClass1();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTextures(ID3D11Device *device, WCHAR *fileName0);
	void ReleaseTexture();

	bool LoadModel(char *modelFile);
	void ReleaseModel();


private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass *m_Texture;
	ModelType *m_model;
};

#endif