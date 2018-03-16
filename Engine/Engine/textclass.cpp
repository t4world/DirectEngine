#include "textclass.h"


TextClass::TextClass()
{
	m_Font = 0;
	m_FontShader = 0;
	m_sentence1 = 0;
	m_sentence2 = 0;
}

TextClass::TextClass(const TextClass &other)
{

}


TextClass::~TextClass()
{
}

bool TextClass::Initialize(ID3D11Device *device, ID3D11DeviceContext *deviceContext, HWND hwnd, int screenWidth, int screenHeight, D3DXMATRIX baseViewMatrix)
{
	bool result;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_baseViewMatrix = baseViewMatrix;
	m_Font = new FontClass;
	if (!m_Font)
	{
		return false;
	}
	result = m_Font->Initialize(device, "../Engine/data/fontdata.txt", L"../Engine/data/font.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font object", L"Error", MB_OK);
		return false;
	}
	//Create the font shader object;
	m_FontShader = new FontShaderClass;
	if (!m_FontShader)
	{
		return false;
	}
	result = m_FontShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object", L"Error", MB_OK);
		return false;
	}
	result = InitializeSentence(&m_sentence1, 16, device);
	if (!result)
	{
		return false;
	}
	result = UpdateSentence(m_sentence1, "Hello", 100, 100, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}
	result = InitializeSentence(&m_sentence2, 16, device);
	if (!result)
	{
		return false;
	}
	result = UpdateSentence(m_sentence2, "GoodsBye", 100, 200, 1.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}
	return true;
}

bool TextClass::Shutdown()
{
	//Release the first sentence
	ReleaseSentence(&m_sentence1);
	ReleaseSentence(&m_sentence2);
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}
	if (m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}
}

bool TextClass::Render(ID3D11DeviceContext *deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix)
{
	bool result;
	result = RenderSentence(deviceContext, m_sentence1, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	result = RenderSentence(deviceContext, m_sentence2, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	return true;
}

bool TextClass::InitializeSentence(SentenceType** sentence, int maxLength, ID3D11Device *device)
{
	VertexType *vertices;
	unsigned long *indices;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT result;
	int i;
	(*sentence) = new SentenceType;
	if (!*sentence)
	{
		return false;
	}
	(*sentence)->vertexBuffer = 0;
	(*sentence)->indexBuffer = 0;
	(*sentence)->maxLength = maxLength;
	(*sentence)->vertexCount = 6 * maxLength;
	(*sentence)->indexCount = (*sentence)->vertexCount;
	//Create the vertex array.
	vertices = new VertexType[(*sentence)->vertexCount];
	if (!vertices)
	{
		return false;
	}
	indices = new unsigned long[(*sentence)->indexCount];
	if (!indices)
	{
		return false;
	}
	//Initialize vertex array to zero at first.
	memset(vertices, 0, sizeof(VertexType) * (*sentence)->vertexCount);
	//Initialize the index array
	for (i = 0;i < (*sentence)->indexCount;i++)
	{
		indices[i] = i;
	}

	//Set up the description of the dynamic vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*sentence)->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	//Give the subresource structure a pointer to the vertex data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	//Create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(*sentence)->vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * (*sentence)->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	//Create the index buffer
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(*sentence)->indexBuffer);
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

//UpdateSentence changes the contents of the vertex buffer for the input sentence. It uses the Map and Unmap functions along with memcpy to update the contents of the vertex buffer.
bool TextClass::UpdateSentence(SentenceType *sentence, char *text, int positionX, int positionY, float red, float green, float blue, ID3D11DeviceContext *deviceContext)
{
	int numLetters;
	VertexType *verices;
	float drawX;
	float drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType *verticesPtr;
	//Store the color of the sentence;
	sentence->red = red;
	sentence->green = green;
	sentence->blue = blue;

	//Get the number of letters in the sentence.
	numLetters = (int)(strlen(text));
	//Check for possible buffer overflow
	if (numLetters > sentence->maxLength)
	{
		return false;
	}
	verices = new VertexType[sentence->vertexCount];
	if (!verices)
	{
		return false;
	}
	//Initialzie vertex array to zero at first;
	memset(verices, 0, sizeof(VertexType) * sentence->vertexCount);
	drawX = (float)((m_screenWidth / 2.0f * -1.0f) +positionX);
	drawY = (float)((m_screenHeight / 2.0f) - positionX);
	//Use the font class to build the vertex array from the sentence text and sentence draw location
	m_Font->BuildVertexArray((void*)verices, text, drawX, drawY);
	//Lock the vertex buffer so it can be written to
	result = deviceContext->Map(sentence->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}
	verticesPtr = (VertexType *)mappedResource.pData;
	memcpy(verticesPtr, (void*)verices, sizeof(VertexType) * sentence->vertexCount);
	//Unlock the vertex buffer;
	deviceContext->Unmap(sentence->vertexBuffer, 0);
	delete[] verices;
	verices = 0;
	return true;
}

void TextClass::ReleaseSentence(SentenceType **sentence)
{
	if (*sentence)
	{
		//Release the sentence vertex buffer.
		if ((*sentence)->vertexBuffer)
		{
			(*sentence)->vertexBuffer->Release();
			(*sentence)->vertexBuffer = 0;
		}
		//Release the sentence index buffer;
		if ((*sentence)->indexBuffer)
		{
			(*sentence)->indexBuffer->Release();
			(*sentence)->indexBuffer = 0;
		}
		//Release the sentence.
		delete *sentence;
		*sentence = 0;
	}
}

bool TextClass::RenderSentence(ID3D11DeviceContext *deviceContext, SentenceType *sentence, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix)
{
	unsigned int stride;
	unsigned int offset;
	D3DXVECTOR4 pixelColor;
	bool result;
	stride = sizeof(VertexType);
	offset = 0;

	//Set the vertex buffer to active in the input assembler so it can be rendered
	deviceContext->IASetVertexBuffers(0, 1, &(sentence->vertexBuffer), &stride, &offset);
	deviceContext->IASetIndexBuffer(sentence->indexBuffer,DXGI_FORMAT_R32_UINT,0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//Create a pixel color vector with the input sentence color
	pixelColor = D3DXVECTOR4(sentence->red, sentence->green, sentence->blue, 1.0f);
	result = m_FontShader->Render(deviceContext, sentence->indexCount, worldMatrix, m_baseViewMatrix, orthoMatrix, m_Font->GetTexture(), pixelColor);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}
