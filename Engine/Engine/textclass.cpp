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
}

bool TextClass::UpdateSentence(SentenceType *sentence, char *text, int positionX, int positionY, float red, float green, float blue, ID3D11DeviceContext *deviceContext)
{

}

void TextClass::ReleaseSentence(SentenceType **sentence)
{

}

bool TextClass::RenderSentence(ID3D11DeviceContext *deviceContext, SentenceType *sentence, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix)
{

}
