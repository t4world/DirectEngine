#include "modelclassinstance.h"

ModelClassInstance::ModelClassInstance()
{
	m_vertexBuffer = 0;
	m_instanceBuffer = 0;
	m_Texture = 0;
}


ModelClassInstance::ModelClassInstance(const ModelClassInstance& other)
{
}


ModelClassInstance::~ModelClassInstance()
{
}


bool ModelClassInstance::Initialize(ID3D11Device* device, WCHAR *textureFileName0)
{
	bool result;
	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	result = LoadTextures(device, textureFileName0);
	if (!result)
	{
		return false;
	}
	return true;
}


void ModelClassInstance::Shutdown()
{
	ReleaseTexture();
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();
	//Release the model data
	return;
}


void ModelClassInstance::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}




bool ModelClassInstance::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	InstanceType *instances;
	D3D11_BUFFER_DESC vertexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, instanceData;
	HRESULT result;
	m_vertexCount = 3;
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].texture = D3DXVECTOR2(0.5f, 0.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	m_instanceCount = 4;

	instances = new InstanceType[m_instanceCount];
	if (!instances)
	{
		return false;
	}
	instances[0].position = D3DXVECTOR3(-1.5f, -1.5f, 5.0f);
	instances[1].position = D3DXVECTOR3(-1.5f, 1.5f, 5.0f);
	instances[2].position = D3DXVECTOR3(1.5f, 1.5f, 5.0f);
	instances[3].position = D3DXVECTOR3(1.5f, -1.5f, 5.0f);


	// Set up the description of the static index buffer.
	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * m_instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] instances;
	instances = 0;

	return true;
}


void ModelClassInstance::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClassInstance::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride[2];
	unsigned int offset[2];
	ID3D11Buffer* bufferPointer[2];


	// Set vertex buffer stride and offset.
	stride[0] = sizeof(VertexType);
	stride[1] = sizeof(InstanceType);
	offset[0] = 0;
	offset[1] = 0;

	bufferPointer[0] = m_vertexBuffer;
	bufferPointer[1] = m_instanceBuffer;


	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 2, bufferPointer, stride, offset);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

ID3D11ShaderResourceView* ModelClassInstance::GetTexture()
{
	return m_Texture->GetTexture();
}

bool ModelClassInstance::LoadTextures(ID3D11Device *device, WCHAR *fileName0)
{
	bool result;
	//Create the texture object;
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}
	result = m_Texture->Initialize(device, fileName0);
	if (!result)
	{
		return false;
	}
	return true;
}

void ModelClassInstance::ReleaseTexture()
{
	//Release the texture object;
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
	return;
}

int ModelClassInstance::GetInstanceCount()
{
	return m_instanceCount;
}

int ModelClassInstance::GetVertexCount()
{
	return m_vertexCount;
}
