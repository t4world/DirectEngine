#ifndef _FRUSTUMCLASS_H_
#define  _FRUSTUMCLASS_H_

#include <d3dx10math.h>
class FrustumClass
{
public:
	FrustumClass();
	FrustumClass(const FrustumClass &other);
	~FrustumClass();

	void ConsturctFrustum(float screenDepth, D3DXMATRIX projectionMatrix, D3DXMATRIX viewMatrix);
	bool CheckPoint(float x, float y, float z);
	bool CheckCube(float centerX, float centerY, float centerZ, float radius);
	bool CheckSphere(float centerX, float centerY, float centerZ, float radius);
	bool CheckRectangle(float centerX, float centerY, float centerZ, float xSize, float ySize, float zSize);
private:
	D3DXPLANE m_planes[6];
};
#endif

