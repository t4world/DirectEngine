#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_
#include <d3dx10math.h>
class PointLight
{
public:
	PointLight();
	PointLight(const PointLight &ther);
	~PointLight();
	void SetDiffuseColor(float red, float green, float blue, float alpha);
	void SetPosition(float x, float y, float z);

	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR4 GetPosition();
private:
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR4 m_position;
};
#endif // !_LIGHTCLASS_H_