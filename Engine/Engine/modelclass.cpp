////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"


ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	//m_Texture = 0;
	m_model = 0;
	m_TextureArray = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device, char *modelFileName, WCHAR *textureFileName0, WCHAR *textureFileName1)
{
	bool result;
	//Load in the model data;
	result = LoadModel(modelFileName);
	if (!result)
	{
		return false;
	}
	//
	CalculateModelVectors();

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	result = LoadTextures(device, textureFileName0, textureFileName1);
	if (!result)
	{
		return false;
	}
	return true;
}


void ModelClass::Shutdown()
{
	ReleaseTexture();
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();
	//Release the model data
	ReleaseModel();
	return;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;


	// Set the number of vertices in the vertex array.
	//m_vertexCount = 4;

	// Set the number of indices in the index array.
	//m_indexCount = 6;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

// 	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
// 	vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);
// 	vertices[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
// 
// 	vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // Top middle.
// 	vertices[1].texture = D3DXVECTOR2(0.5f, 0.0f);
// 	vertices[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
// 
// 	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
// 	vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);
// 	vertices[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
// 
// 
// 	// Load the index array with data.
// 	indices[0] = 0;  // Bottom left.
// 	indices[1] = 1;  // Top middle.
// 	indices[2] = 2;  // Bottom right.
	//Load the vertex array and index array with data;
	for (i = 0; i < m_vertexCount;i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
		vertices[i].tangent = D3DXVECTOR3(m_model[i].tx,m_model[i].ty,m_model[i].tz);
		vertices[i].binormal = D3DXVECTOR3(m_model[i].bx, m_model[i].by, m_model[i].bz);
		indices[i] = i;
	}


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
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

ID3D11ShaderResourceView** ModelClass::GetTexture()
{
	return m_TextureArray->GetTextureArray();
}

bool ModelClass::LoadTextures(ID3D11Device *device, WCHAR *fileName0, WCHAR *fileName1)
{
	bool result;
	//Create the texture object;
	m_TextureArray = new Texturearrayclass;
	if (!m_TextureArray)
	{
		return false;
	}
	result = m_TextureArray->Initialize(device, fileName0, fileName1);
	if (!result)
	{
		return false;
	}
	return true;
}

void ModelClass::ReleaseTexture()
{
	//Release the texture object;
	if (m_TextureArray)
	{
		m_TextureArray->Shutdown();
		delete m_TextureArray;
		m_TextureArray = 0;
	}
	return;
}

bool ModelClass::LoadModel(char *modelFile)
{
	ifstream fin;
	char input;
	int i;
	//Open the model file
	fin.open(modelFile);
	if (fin.fail())
	{
		return false;
	}
	//Read up to the value of vertex count;
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	//Read in the vertex count;
	fin >> m_vertexCount;
	//Set the numbero of indeices to be the same as the vertex count;
	m_indexCount = m_vertexCount;
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}
	//Read up to the begining of the data
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;

}

void ModelClass::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return;
}

void ModelClass::CalculateModelVectors()
{
	int faceCount;
	int i;
	int index;
	TempVertexType vertex1;
	TempVertexType vertex2;
	TempVertexType vertex3;
	VectorType tangent;
	VectorType binormal;
	VectorType normal;
	faceCount = m_vertexCount / 3;
	index = 0;
	for (i = 0; i < faceCount;i++)
	{
		vertex1.x = m_model[index].x;
		vertex1.y = m_model[index].y;
		vertex1.z = m_model[index].z;
		vertex1.tx = m_model[index].tx;
		vertex1.ty = m_model[index].ty;
		vertex1.nx = m_model[index].nx;
		vertex1.ny = m_model[index].ny;
		vertex1.nz = m_model[index].nz;
		index++;

		vertex2.x = m_model[index].x;
		vertex2.y = m_model[index].y;
		vertex2.z = m_model[index].z;
		vertex2.tx = m_model[index].tx;
		vertex2.ty = m_model[index].ty;
		vertex2.nx = m_model[index].nx;
		vertex2.ny = m_model[index].ny;
		vertex2.nz = m_model[index].nz;
		index++;

		vertex3.x = m_model[index].x;
		vertex3.y = m_model[index].y;
		vertex3.z = m_model[index].z;
		vertex3.tx = m_model[index].tx;
		vertex3.ty = m_model[index].ty;
		vertex3.nx = m_model[index].nx;
		vertex3.ny = m_model[index].ny;
		vertex3.nz = m_model[index].nz;
		index++;

		CalculateTangentBinormal(vertex1, vertex2, vertex3, tangent, binormal);
		CalculateNormal(tangent, binormal, normal);
		m_model[index - 1].nx = normal.x;
		m_model[index - 1].ny = normal.y;
		m_model[index - 1].nz = normal.z;
		m_model[index - 1].tx = tangent.x;
		m_model[index - 1].ty = tangent.y;
		m_model[index - 1].tz = tangent.z;
		m_model[index - 1].bx = binormal.x;
		m_model[index - 1].by = binormal.y;
		m_model[index - 1].bz = binormal.z;

		m_model[index - 2].nx = normal.x;
		m_model[index - 2].ny = normal.y;
		m_model[index - 2].nz = normal.z;
		m_model[index - 2].tx = tangent.x;
		m_model[index - 2].ty = tangent.y;
		m_model[index - 2].tz = tangent.z;
		m_model[index - 2].bx = binormal.x;
		m_model[index - 2].by = binormal.y;
		m_model[index - 2].bz = binormal.z;

		m_model[index - 3].nx = normal.x;
		m_model[index - 3].ny = normal.y;
		m_model[index - 3].nz = normal.z;
		m_model[index - 3].tx = tangent.x;
		m_model[index - 3].ty = tangent.y;
		m_model[index - 3].tz = tangent.z;
		m_model[index - 3].bx = binormal.x;
		m_model[index - 3].by = binormal.y;
		m_model[index - 3].bz = binormal.z;
	}
}

void ModelClass::CalculateTangentBinormal(TempVertexType vertex_0, TempVertexType vertex_1, TempVertexType vertex_2, VectorType &tangent, VectorType &binormal)
{
	//http://www.terathon.com/code/tangent.html
	//http://www.opengl-tutorial.org/cn/intermediate-tutorials/tutorial-13-normal-mapping/
	float vertor1[3];
	float vertor2[3];
	float tuvVector1[2];
	float tuvVector2[2];
	vertor1[0] = vertex_1.x - vertex_0.x;
	vertor1[1] = vertex_1.y - vertex_0.y;
	vertor1[2] = vertex_1.z - vertex_0.z;

	vertor2[0] = vertex_2.x - vertex_0.x;
	vertor2[1] = vertex_2.y - vertex_0.y;
	vertor2[2] = vertex_2.z - vertex_0.z;

	tuvVector1[0] = vertex_1.tx - vertex_0.tx;
	tuvVector1[1] = vertex_1.ty - vertex_0.ty;

	tuvVector2[0] = vertex_2.tx - vertex_0.tx;
	tuvVector2[1] = vertex_2.ty - vertex_0.ty;

	float den = 1.0f / (tuvVector1[0] * tuvVector2[1] - tuvVector2[0] * tuvVector2[0]);
	tangent.x = (tuvVector2[0] * vertor1[0] - tuvVector1[0] * vertor2[0]) * den;
	tangent.y = (tuvVector2[0] * vertor1[1] - tuvVector1[0] * vertor2[1]) * den;
	tangent.z = (tuvVector2[0] * vertor1[2] - tuvVector1[0] * vertor2[2]) * den;
	float length = sqrt(tangent.x * tangent.x + tangent.y * tangent.y + tangent.z * tangent.z);
	tangent.x = tangent.x / length;
	tangent.y = tangent.y / length;
	tangent.z = tangent.z / length;

	binormal.x = (-tuvVector2[1] * vertor1[0] + tuvVector1[1] * vertor2[0]) * den;
	binormal.y = (-tuvVector2[1] * vertor1[1] + tuvVector1[1] * vertor2[1]) * den;
	binormal.z = (-tuvVector2[1] * vertor1[2] + tuvVector1[1] * vertor2[2]) * den;
	length = sqrt(binormal.x * binormal.x + binormal.y * binormal.y + binormal.z * binormal.z);
	binormal.x = binormal.x / length;
	binormal.y = binormal.y / length;
	binormal.z = binormal.z / length;
}

void ModelClass::CalculateNormal(VectorType tangent, VectorType binormal, VectorType &normal)
{
	float length;
	normal.x = tangent.y * binormal.z - tangent.z * binormal.y;
}
