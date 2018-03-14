#ifndef _FONTCLASS_H_
#define _FONTCLASS_H_
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;
#include "textureclass.h"

class FontClass
{
private:
	//The font type structure is used to hold the indexing data read in from the font index file.
	//The left and right are the TU texture coordinate.The size is the width of the character in pixels.
	struct FontType
	{
		float left;
		float right;
		float size;
	};
	//The VertexType structure is for the actual vertex data used to build the square to render the text character on.
	//The individual character will  require two triangle to make a square.Those triangle will have position and texture data only.
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};
public:
	FontClass();
	FontClass(const FontClass &other);
	~FontClass();
	bool Initialize(ID3D11Device *device, char *fontFileName, WCHAR *textureFileName);
	void Shutdown();
	ID3D11ShaderResourceView *GetTexture();
	void BuildVertexArray(void* vertices, char *sentence, float drawnX, float drawnY);
private:
	bool LoadFontData(char *fileName);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device *device, WCHAR *textureFileName);
	void ReleaseTexture();
private:
	FontType *m_Font;
	TextureClass *m_Texture;
};
#endif // !_FONTCLASS_H_

