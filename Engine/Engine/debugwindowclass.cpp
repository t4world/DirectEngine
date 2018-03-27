#include "debugwindowclass.h"


DebugWindowClass::DebugWindowClass()
{
	m_indexCount = 0;
	m_vertexBuffer = 0;
}

DebugWindowClass::DebugWindowClass(const DebugWindowClass &other)
{

}

DebugWindowClass::~DebugWindowClass()
{
}

bool DebugWindowClass::Initialize(ID3D11Device *device, int screenWidth, int screenHeight, int bitmapWidth, int bitmapHeight)
{
	bool result;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_bitmapWidth = bitmapWidth;
	m_bitmapHeight = bitmapHeight;
	m_prePositionX = -1;
	m_prePositionY = -1;
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}
	return true;
}

void DebugWindowClass::Shutdown()
{
	ShutdownBuffers();
}

bool DebugWindowClass::Render(ID3D11DeviceContext *deviceContext,int positionX, int positionY)
{
	bool result;
	result = UpdateBuffers(deviceContext, positionX, positionY);
	if (!result)
	{
		return false;
	}
	RenderBuffers(deviceContext);
	return true;
}

int DebugWindowClass::GetIndexCount()
{
	return m_indexCount;
}

bool DebugWindowClass::InitializeBuffers(ID3D11Device *device)
{
	VertexType *vertices;
	unsigned long *indices;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT result;
	int i;
	m_vertexCount = 6;
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}
	m_indexCount = m_vertexCount;
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	memset(vertices, 0, sizeof(VertexType) * m_vertexCount);
	for (i = 0; i < m_indexCount;i++)
	{
		indices[i] = i;
	}
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffers);
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

void DebugWindowClass::ShutdownBuffers()
{
	if (m_indexBuffers)
	{
		m_indexBuffers->Release();
		m_indexBuffers = 0;
	}
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

bool DebugWindowClass::UpdateBuffers(ID3D11DeviceContext *deviceContext, int positionX, int positionY)
{
	float left;
	float right;
	float top;
	float down;
	VertexType *vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType *verticesPtr;
	HRESULT result;

	if (m_prePositionX == positionX && m_prePositionY == positionY)
	{
		return true;
	}
	m_prePositionX = positionX;
	m_prePositionY = positionY;
	left = (float)((m_screenWidth / 2) * -1) + (float)m_prePositionX;
	top = (float)(m_screenHeight / 2) - (float)m_prePositionY;
	right = left + (float)m_bitmapWidth;
	down = top - m_bitmapHeight;
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}
	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);
	
	vertices[1].position = D3DXVECTOR3(right, down, 0.0f);
	vertices[1].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(left, down, 0.0f);
	vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[3].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[4].position = D3DXVECTOR3(right, top, 0.0f);
	vertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[5].position = D3DXVECTOR3(right, down, 0.0f);
	vertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);

	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}
	verticesPtr = (VertexType*)mappedResource.pData;
	memcpy(verticesPtr, (void*)vertices, sizeof(VertexType) * m_vertexCount);
	deviceContext->Unmap(m_vertexBuffer, 0);
	delete[] vertices;
	vertices = 0;
	return true;
}

void DebugWindowClass::RenderBuffers(ID3D11DeviceContext *deviceContext)
{
	unsigned int stride;
	unsigned int offset;
	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffers, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
