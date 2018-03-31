////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "modelclass1.h"

//#include "colorshaderclass.h"
#include "textureshaderclass.h"

#include "lightshaderclass.h"
#include "lightclass.h"
//#include "bitmapclass.h"
#include "textclass.h"
#include "frustumclass.h"
#include "modellistclass.h"
#include "multitextureshaderclass.h"
#include "bumpmapshaderclass.h"
#include "specmapshaderclass.h"
#include "rendertextureclass.h"
#include "debugwindowclass.h"
#include "fogshaderclass.h"
#include "clipplaneshaderclass.h"
#include "transparentshaderClass.h"
#include "reflectionshaderclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(float rotationY);

private:
	bool Render();
	bool RenderToTexture();
	bool RenderScene();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	//ModelClass* m_Model;
	//ColorShaderClass* m_ColorShader;
	TextureShaderClass *m_TextureShader;
	//LightShaderClass *m_LightShader;
	//LightClass *m_Light;
	//BitmapClass *m_Bitmap;
	//TextClass *m_Text;
	//ModelListClass *m_ModelList;
	//FrustumClass *m_Frustum;
	//MultiTextureShaderClass *m_MultiTextureShader;
	//BumpMapShaderClass *m_BumpMapShader;
	//SpecMapShaderClass* m_SpecMapShader;
	RenderTextureClass *m_RenderTexture;
	//DebugWindowClass *m_DebuWindow;
	ModelClass1 *m_Model1;
	ModelClass1 *m_FloorModel;
	//ModelClass1 *m_Model2;
	//FogShaderClass *m_FogShader;
	//ClipPlaneShaderClass *m_clipShader;
	//TransparentShaderClass *m_transparentShader;
	ReflectionShaderClass *m_ReflectionShader;
};

#endif