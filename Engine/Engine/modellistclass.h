#ifndef _MODELLISTCLASS_H_
#define _FRUSTUMCLASS_H_

#include <d3dx10math.h>
#include <stdlib.h>
#include <time.h>

class ModelListClass
{
private:
	struct ModelInfoType
	{
		D3DXVECTOR4 color;
		float positionX;
		float positionY;
		float positionZ;

	};
public:
	ModelListClass();
	ModelListClass(const ModelListClass &other);
	~ModelListClass();

	bool Initialize(int modelCount);
	void Shutdown();
	int GetModelCount();
	void GetData(int index, float &positionX, float &positionY, float &positionZ, D3DXVECTOR4 &color);
private:
	int m_modelCount;
	ModelInfoType *m_ModelInfoList;
};
#endif // !_MODELLISTCLASS_H_

