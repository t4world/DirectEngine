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

void BitmapClass::ReleaseTexture()
{
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
}

bool BitmapClass::LoadTexture(ID3D11Device *device, WCHAR *textFileName)
{
	bool result;
	//Create the texture object
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}
	result = m_Texture->Initialize(device, textFileName);
	if (!result)
	{
		return false;
	}
	return true;
}

void BitmapClass::RenderBuffers(ID3D11DeviceContext *deviceContext)
{
	unsigned int stride;
	unsigned int offset;
	//Set the vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool BitmapClass::UpdateBuffers(ID3D11DeviceContext *deviceContext, int positionX, int positionY)
{
	float left;
	float right;
	float top;
	float bottom;
	VertexType *vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType *verticesPtr;
	HRESULT result;
	if (positionX == m_previousPosX && positionY == m_previousPosY)
	{
		return true;
	}
	m_previousPosX = positionX;
	m_previousPosY = positionY;
	left = ((float)(m_screenWidth / 2) * -1) + (float)positionX;
	right = left + m_bitmapWidth;
	top = (float)(m_screenHeight / 2) - (float)positionY;
	bottom = top - (float)m_bitmapHeight;
	//Create the vertex array
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}
	//Load the vertex array with data;
	//First triangle
	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);//Top left
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);
	vertices[1].position = D3DXVECTOR3(right, bottom, 0.0f);//Bottom right;
	vertices[1].texture = D3DXVECTOR2(1.0f, 1.0f);
	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);//Bottom Left;
	vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);
	//Second triangle
	vertices[3].position = D3DXVECTOR3(left, top, 0.0f);//Top left
	vertices[3].texture = D3DXVECTOR2(0.0f, 0.0f);
	vertices[4].position = D3DXVECTOR3(right, top, 0.0f);//Top right;
	vertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);
	vertices[2].position = D3DXVECTOR3(right, bottom, 0.0f);//Bottom right;
	vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);
	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}
	verticesPtr = (VertexType *)mappedResource.pData;
	//Copy the data into the vertex buffer;
	memcpy(verticesPtr, (void*)vertices, sizeof(VertexType) * m_vertexCount);
	//Unlock the vertex Buffer;
	deviceContext->Unmap(m_vertexBuffer, 0);
	//Release the vertex array as it is no longer needed.
	delete[]vertices;
	vertices = 0;
	return true;
}

void BitmapClass::ShutdownBuffers()
{
	//Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}
	//Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
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
	memset(vertices, 0, sizeof(VertexType) * m_vertexCount);
	//Load the index array with data
	for ( i = 0; i < m_indexCount; i++)
	{
		indices[i] = i;
	}
	//Set up the desciption of the dynamic index buffer.
	vetexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vetexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vetexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vetexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vetexBufferDesc.MiscFlags = 0;
	vetexBufferDesc.StructureByteStride = 0;

	//Give the subresouce structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	//Now create the vertex buffer.
	result = device->CreateBuffer(&vetexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}
	//Set up the desciption of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	//Give the subresource structure a pointer to the index data;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	//Create the index buffer
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;
	return true;
}
