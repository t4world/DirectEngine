#include "fontclass.h"


FontClass::FontClass()
{
	m_Font = 0;
	m_Texture = 0;
}

FontClass::FontClass(const FontClass &other)
{

}


FontClass::~FontClass()
{
}

bool FontClass::Initialize(ID3D11Device *device, char *fontFileName, WCHAR *textureFileName)
{
	bool result;
	//Load in the text file containing the font data.
	result = LoadFontData(fontFileName);
	if (!result)
	{
		return false;
	}
	//Load the texture that has the font character on it;
	result = LoadTexture(device, textureFileName);
	if (!result)
	{
		return false;
	}
	return true;
}

void FontClass::Shutdown()
{
	//Release the font texture
	ReleaseTexture();
	//Release the font data;
	ReleaseFontData();
}

ID3D11ShaderResourceView * FontClass::GetTexture()
{
	return m_Texture->GetTexture();
}

void FontClass::BuildVertexArray(void* vertices, char *sentence, float drawnX, float drawnY)
{
	VertexType *vertexPtr;
	int numLetters;
	int index;
	int i;
	int letter;
	//Coerce the input vertices into the VertexType structure.
	vertexPtr = (VertexType *)vertices;
	numLetters = (int)strlen(sentence);
	index = 0;
	for (i = 0 ;i < numLetters;++i)
	{
		letter = ((int)sentence[i]) - 32;
		if (letter == 0)
		{
			drawnX += 3.0f;
		}
		else
		{
			//First triangle in quad;
			vertexPtr[index].position = D3DXVECTOR3(drawnX, drawnY, 0.0f);//top left;
			vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].left, 0.0f);
			++index;
			vertexPtr[index].position = D3DXVECTOR3(drawnX + m_Font[letter].size, drawnY - 16, 0.0f);//bottom right;
			vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].right, 1.0f);
			++index;
			vertexPtr[index].position = D3DXVECTOR3(drawnX , drawnY - 16, 0.0f);//bottom left;
			vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].left, 1.0f);
			++index;
			vertexPtr[index].position = D3DXVECTOR3(drawnX, drawnY, 0.0f);//top left;
			vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].left, 0.0f);
			++index;
			vertexPtr[index].position = D3DXVECTOR3(drawnX +m_Font[letter].size, drawnY, 0.0f);//top right;
			vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].right, 0.0f);
			++index;
			vertexPtr[index].position = D3DXVECTOR3(drawnX + m_Font[letter].size, drawnY - 16, 0.0f);//bottom right;
			vertexPtr[index].texture = D3DXVECTOR2(m_Font[letter].right, 1.0f);
			++index;
			//Update the x location for drawing by the size of the letter and one pixel
			drawnX = drawnX + m_Font[letter].size + 1.0f;
		}
	}
}

bool FontClass::LoadFontData(char *fileName)
{
	ifstream fin;
	int i;
	char temp;
	//Create the font spacing buffer.
	m_Font = new FontType[95];
	if (!m_Font)
	{
		return false;
	}
	fin.open(fileName);
	if (fin.fail())
	{
		return false;
	}
	for (i = 0; i < 95;i++)
	{
		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}
		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}
		fin >> m_Font[i].left;
		fin >> m_Font[i].right;
		fin >> m_Font[i].size;
	}
	fin.close();
	return true;
}

void FontClass::ReleaseFontData()
{
	//Release the font data array;
	if (m_Font)
	{
		delete[] m_Font;
		m_Font = 0;
	}
}

bool FontClass::LoadTexture(ID3D11Device *device, WCHAR *textureFileName)
{
	bool result;
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}
	result = m_Texture->Initialize(device, textureFileName);
	if (!result)
	{
		return false;
	}
	return true;
}

void FontClass::ReleaseTexture()
{
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
}
