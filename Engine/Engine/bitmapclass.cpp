#include "bitmapclass.h"



BitmapClass::BitmapClass()
{
}

BitmapClass::BitmapClass(const BitmapClass & other)
{
}


BitmapClass::~BitmapClass()
{
}

bool BitmapClass::Initialize(ID3D11Device * device, int screenWidth, int screenHeight, WCHAR * textureFileName, int bitmapWidth, int bitmapHeight)
{
	bool result;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_bitmapWidth = bitmapWidth;
	m_bitmapHeight = bitmapHeight;
	m_previousPosX = -1;
	m_previousPosY = -1;
	//Initialize the vertex and index buffers
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}
	//Load the texture for this model.
	result = LoadTexture(device, textureFileName);
	if (!result)
	{
		return false;
	}
	return true;
}

void BitmapClass::Shutdown()
{
	//Release the model texture.
	ReleaseTexture();
	//Shutdown the vetex and index buffers.
	ShutdownBuffers();
}

bool BitmapClass::Render(ID3D11DeviceContext * deviceContext, int posX, int posY)
{
	bool result;
	//Rebuild the dynamic vertex buffer for rendering to possibly a different location on the screen
	result = UpdateBuffers(deviceContext, posX, posY);
	if (!result)
	{
		return false;
	}
	//Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);
	return true;
}

int BitmapClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView * BitmapClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool BitmapClass::InitializeBuffers(ID3D11Device * device)
{
	VertexType *vertices;
	unsigned long *indices;
	D3D11_BUFFER_DESC vetexBufferDesc;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT result;
	int i;
	//Set the number of vertices in the vertex array.
	m_vertexCount = 6;
	//Set the number of the indices in the index array.
	m_indexCount = m_vertexCount;
	//Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}
	//Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}
	//Initialize the vertex array t zero at first.
	memset(vertices, 0, sizeof(VertexType) * m_vertexCount));
	//Load the index array with data
	for ( i = 0; i < m_indexCount; i++)
	{
		indices[i] = i;
	}
	//
	return true;
}
