#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_

#include <d3dx10math.h>

class LightClass
{
public:
	LightClass();
	LightClass(const LightClass &ther);
	~LightClass();
	void SetDiffuseColor(float red, float green, float blue,float alpha);
	void SetDirection(float x, float y, float z); 
	void SetAmbientColor(float red, float green, float blue,float alpha);
	void SetSpecularColor(float red, float green, float blue, float alpha);
	void SetSpecularPower(float specularPower);

	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR3 GetDirection();
	D3DXVECTOR4 GetAmbientColor();
	D3DXVECTOR4 GetSpecularColor();
	float GetSpecularPower();
private: 
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR3 m_direction;
	D3DXVECTOR4 m_ambientColor;
	D3DXVECTOR4 m_specularColor;
	float m_specularPower;
};
#endif // !_LIGHTCLASS_H_

