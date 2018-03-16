#ifndef _TEXTCLASS_H_
#define _TEXTCLASS_H_
#include "fontclass.h"
#include "fontshaderClass.h"

class TextClass
{
private:
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer;
		ID3D11Buffer *indexBuffer;
		int vertexCount;
		int indexCount;
		int maxLength;
		float red;
		float green;
		float blue;
	};
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 texture;
	};
	FontClass *m_Font;
	FontShaderClass *m_FontShader;
	int m_screenWidth;
	int m_screenHeight;
	D3DXMATRIX m_baseViewMatrix;
	SentenceType *m_sentence1;
	SentenceType *m_sentence2;
public:
	TextClass();
	TextClass(const TextClass &other);
	~TextClass();

	bool Initialize(ID3D11Device *device, ID3D11DeviceContext *deviceContext, HWND hwnd, int screenWidth, int screenHeight, D3DXMATRIX baseViewMatrix);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix);
private: 
	bool InitializeSentence(SentenceType **sentence, int maxLength, ID3D11Device *device);
	bool UpdateSentence(SentenceType *sentence, char *text, int positionX, int positionY, float red, float green, float blue, ID3D11DeviceContext *deviceContext);
	void ReleaseSentence(SentenceType **sentence);
	bool RenderSentence(ID3D11DeviceContext *deviceContext, SentenceType *sentence, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix);
};
#endif // !_TEXTCLASS_H_

