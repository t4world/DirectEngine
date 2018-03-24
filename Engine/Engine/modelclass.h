////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
//#include "textureclass.h"
#include "texturearrayclass.h"
#include <fstream>
using namespace std;



////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    //D3DXVECTOR4 color;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
		D3DXVECTOR3 tangent;
		D3DXVECTOR3 binormal;
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
		float tx;
		float ty;
		float tz;
		float bx;
		float by;
		float bz;
	};

	struct TempVertexType
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

	struct VectorType
	{
		float x;
		float y;
		float z;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView** GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTextures(ID3D11Device *device, WCHAR *fileName0, WCHAR *fileName1);
	void ReleaseTexture();

	bool LoadModel(char *modelFile);
	void ReleaseModel();

	void CalculateModelVectors();
	void CalculateTangentBinormal(TempVertexType vertex_0, TempVertexType vertex_1, TempVertexType vertex_2, VectorType &tangent,VectorType &binormal);
	void CalculateNormal(VectorType tangent, VectorType binormal, VectorType &normal);

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	//TextureClass *m_Texture;
	ModelType *m_model;
	Texturearrayclass *m_TextureArray;
};

#endif